#include <exception>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include "auth.hpp"
#include "util.hpp"
#include "live.hpp"
#include "hardware.hpp"
#include "mongo_driver.hpp"
using namespace std;
/*
                  #http://192.168.1.65:8004/HLS/IRIB%20TV1/p.m3u8 ---->
                    #http://192.168.1.61:8004/RHLS/192.168.1.65:8004/HLS/IRIB%20TV1/p.m3u8
                    #https://tv.razavi.ir/hls/rozeh_1.m3u8?720
                    hls_proto = "https" if "https" in url else "http"
                    hls_cut = c['ip_url'][8:] if "https" in url else c['ip_url'][7:]
                    c['url_hls'] = "http://%s/HLS/RHLS/%s/%s"%(serverIP, hls_proto, hls_cut)




 *  live_tuners_info:
 *      in POST: add channels to 
 *         in input tuner:
 *           if not virtual:  live_inputs_dvb
 *           else             live_output_dvb
 *
 *      in DEL: del channels from 
 *         in input tuner:
 *              live_inputs_dvb
 *         else
 *              live_output_dvb by dvbId 
 *         func_del_from_processed
 *         func_del_from_outputs
 *      in PUT: 
 *          if change URL:
 *              do DEl
 *              do POST
 *  live_network_accounts:
 *      in POST: add channels to 
 *         *live_inputs_network
 *         *live_network_channels
 *         *live_output_archive: if it has timeShift
 *      in DEL: del channels from 
 *         *live_inputs_network and live_network_channels by accountId 
 *         func_del_from_processed
 *         func_del_from_outputs
 *      in PUT: 
 *          if change URL:
 *              do DEl
 *              do POST
 *
 *   live_inputs_network
 *   live_inputs_archive
 *   live_inputs_dvb
 *   live_inputs_transcode, 
 *   live_inputs_mix, 
 *   live_inputs_scramble
 *      in DEL: del from
 *          func_del_from_processed(channelId)
 *          func_del_from_outputs(channelId)
 *
 * */
void func_del_from_outputs_and_processed(int64_t id)
{
    LOG(trace) << "Delete from all processed and output this Channel id:" << id;
    auto filter = "{\"input\":" + to_string(id) + "}";
    Mongo::remove_mony("live_output_dvb", filter );
    Mongo::remove_mony("live_output_archive", filter );
    Mongo::remove_mony("live_output_network", filter );
    Mongo::remove_mony("live_inputs_mix", filter );
    Mongo::remove_mony("live_inputs_scramble", filter );
    Mongo::remove_mony("live_inputs_transcode", filter );
}
void func_del_from_outputs_and_processed(const vector<int64_t>& id_list)
{
    if(!id_list.size()) return;
    LOG(trace) << "Delete from all processed and output this Channel size:" << id_list.size();
    json filter;
    filter["input"] = json::object();
    filter["input"]["$in"] = json::array();
    for(auto id : id_list)
        filter["input"]["$in"].push_back(id);
    string filter_str = filter.dump();
    LOG(trace) << "Filter is " << filter_str;
        
    Mongo::remove_mony("live_output_dvb", filter_str );
    Mongo::remove_mony("live_output_archive", filter_str );
    Mongo::remove_mony("live_output_network", filter_str );
    Mongo::remove_mony("live_inputs_mix", filter_str );
    Mongo::remove_mony("live_inputs_scramble", filter_str );
    Mongo::remove_mony("live_inputs_transcode", filter_str );
}
void add_network_account_to_out_archive(json& account)
{
    string url = account["url"];
    LOG(trace) << "Try to add IPTV accounts channels to output archive by url :" << url;
    if(url.find("playlist=") == string::npos){
        LOG(warning) << "IPTV account is not MMK. Not add to live_output_archive";
        return;
    } 
    string archive_url = url + "&get_archive";
    string out = Util::get_url(archive_url);  
    if(out.size() < 50) return;
    json archive_chan_list;
    try{
        archive_chan_list = json::parse(out);
    }catch(std::exception& e){
        LOG(error) << "Invalid Json " << out;
        return;
    }
    if(archive_chan_list.is_null() || 
        !archive_chan_list.is_array() || 
        !archive_chan_list.size()){
        LOG(warning) << "The output of " << archive_url << " is not valid.";
        return;
    }
    json input_net_chans = json::parse(Mongo::find_mony("live_inputs_network",
        "{\"accountId\":" + to_string(account["_id"].get<int64_t>()) + "}"));
    for(auto& net_chan : input_net_chans){
        for(auto& archive_chan : archive_chan_list){
            if(net_chan["name"].is_null() || archive_chan["name"].is_null())
                continue;
            LOG(trace) << "Comp " << net_chan["name"] << ":" << archive_chan["name"];
            if(net_chan["name"] == archive_chan["name"]){
                json chan;
                chan["_id"] = Mongo::get_uniq_id(); 
                chan["active"] = net_chan["active"];
                chan["description"] = "From master " + 
                    (account["name"].is_string() ? account["name"].get<string>() : "");
                chan["input"] = net_chan["_id"];
                chan["inputType"] = LIVE_INPUT_TYPE_NETWORK;
                chan["category"] = json::array();
                chan["programName"] = "";
                chan["timeShift"] = archive_chan["timeShift"];
                chan["virtual"] = true;
                Mongo::insert("live_output_archive", chan.dump());
                break;
            }
        }
    }
}
void remove_or_disable_output_channels_if_needs(const std::string col)
{
    try{

        LOG(trace) << "Try to remove unvalid channels from " << col;
        // TODO: complete BULK mode DB operaton
        using bsoncxx::builder::basic::kvp;
        using bsoncxx::builder::basic::make_document;

        //Make map of type names
        std::map<long, std::string> type_map;
        json types = json::parse(Mongo::find_mony("live_inputs_types", "{}"));
        for(const auto& type : types) 
            type_map[type["_id"]] = type["name"];

        auto filter = json::object();
        json channels = json::parse(Mongo::find_mony(col, "{}"));
        //vector<mongocxx::model::delete_one> ops;
        for(auto& chan : channels){

            auto type_name = type_map[ chan["inputType"] ];
            auto input_col = "live_inputs_" + type_name;
            
            string in_chan_str = Mongo::find_id(input_col, chan["input"]);
            if(in_chan_str.size() < 10){
                // not exists input. remove output
                Mongo::remove_id(col, chan["_id"]);
            }else{
                // check if active field is differ
                json in_chan = json::parse(in_chan_str);
                if(in_chan["active"] != chan["active"]){
                    chan["active"] = in_chan["active"];
                    Mongo::update_id(col, chan["_id"], chan.dump());
                }
            }
        }
        /*
        if(ops.size()){
            // Create bulk DB operation
            auto client = Mongo::pool.acquire();
            auto colection = (*client)[DB_NAME][col];
            auto bulk = colection.create_bulk_write(); 
            for(auto& op : ops){
                bulk.append(op);
            }
            bulk.execute();
        }
        */

    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
void func_del_tuner_info(int64_t tuner_id)
{
    try{
        LOG(trace) << "Try to remove channels of tuner id: " << tuner_id;
        string filter = "{\"dvbId\":" + to_string(tuner_id) + "}";
        json chan_list = json::parse(Mongo::find_mony("live_inputs_dvb", filter));

        vector<int64_t> id_list;
        for(const auto& chan : chan_list){
            id_list.push_back(chan["_id"].get<int64_t>());
        }
        func_del_from_outputs_and_processed(id_list);
         
        Mongo::remove_mony("live_inputs_dvb", filter);
        Mongo::remove_mony("live_output_dvb", filter);
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
void func_add_tuner_info(json& tuner)
{
    try{
        if(tuner["systemId"] >= 1000 ){
            LOG(debug) << "Tuner type is not input";
            return;
        }

        LOG(trace) << "Try to add channels tuner id: " << tuner["_id"];
        string ffilter = "{\"frequencyId\":" + 
            to_string(tuner["frequencyId"].get<int64_t>()) + "}";
        json channels_list = json::parse(Mongo::find_mony("live_satellites_channels", 
                    ffilter));

        if(!channels_list.size()){ 
            LOG(debug) << "Channel list is empty";
            return;
        }
        for(const auto& chan : channels_list){
            string filter = "{\"type\":8, \"name\":\"" + chan["name"].get<string>() + "\"}";
            json logo = json::parse(Mongo::find_one("storage_contents_info", filter));

            json dvb_chan;
            dvb_chan["_id"] = Mongo::get_uniq_id(); 
            dvb_chan["active"] = tuner["active"];
            dvb_chan["logo"] = logo["_id"].is_number() ? logo["_id"].get<int64_t>() : 0; 
            dvb_chan["tv"] = chan["videoId"] > 0 ; 
            dvb_chan["dvbId"] = tuner["_id"]; 

            if(tuner["virtual"].is_null() || tuner["virtual"] == false){
                dvb_chan["channelId"] = chan["_id"]; 
                Mongo::insert("live_inputs_dvb", dvb_chan.dump());
            }else{
                dvb_chan["description"] = ""; 
                dvb_chan["input"] = 0; 
                dvb_chan["inputType"] = 0; 
                dvb_chan["category"] = json::array(); 
                dvb_chan["serviceId"] = chan["serviceId"]; 
                Mongo::insert("live_output_dvb", dvb_chan.dump());
            }
        }
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
void func_del_network_account(int64_t account_id)
{
    try{

        LOG(trace) << "Try to remove channels of network account:" << account_id;
        string filter = "{\"accountId\":" + to_string(account_id) + "}";
        json chan_list = json::parse(Mongo::find_mony("live_inputs_network", filter));

        vector<int64_t> id_list;
        for(const auto& chan : chan_list){
            id_list.push_back(chan["_id"].get<int64_t>());
        }
        func_del_from_outputs_and_processed(id_list);
         
        Mongo::remove_mony("live_network_channels", filter);
        Mongo::remove_mony("live_inputs_network", filter);
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
json get_iptv_account_channels(const std::string url)
{
    json list = json::array();
    try{
        LOG(trace) << "Try to get channels of url:" << url;
        string ans = Util::get_url(url);
        if(!ans.size()) return list;
        //  #EXTINF:1000771,IRIB TV1000671
        //  http://:8771/live.ts
        istringstream in(ans);

        string line, chan_name, chan_url;
        while(getline(in, line)){
            if(line.size() < 5 ) continue;
            else if(line.find("#EXTINF") != string::npos){
                auto pos = line.find_last_of(",");
                if(pos == string::npos) pos = line.find_last_of(":");
                chan_name = line.substr(pos+1);
            }else if(line.find("#") == 0 ){ 
                continue;
            }else if(char first = std::tolower(line[0]) ;
                    first == 'h' ||  // http, https 
                    first == 'r' ||  // rtsp, rtp
                    first == 'u'     // udp 
                    ){
                chan_url = line;
                json chan;
                chan["name"] = chan_name;
                chan["url"]  = chan_url;
                list.push_back(chan);
            }
        }
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
    return list;
}
void func_add_network_account(json account)
{
    try{
        LOG(trace) << "Try to add channels of network account:" << account["_id"];
        auto is_radio = [](const string ch_name) -> bool {
            string name = ch_name;
            std::transform(name.begin(), name.end(), name.begin(),[](auto c){
                    return std::tolower(c);
                    });
            if(name.find("radio") != string::npos && name.find(" nama") == string::npos)
                return true;
            else
                return false;
        };
        json channels_list = get_iptv_account_channels(account["url"]);
        if(!channels_list.size()) return;
        for(const auto& chan : channels_list){
            string name = chan["name"]; 
            json net_chan;
            net_chan["_id"] = Mongo::get_uniq_id(); 
            net_chan["name"] = name; 
            net_chan["url"] = chan["url"]; 
            net_chan["accountId"] = account["_id"]; 
            Mongo::insert("live_network_channels", net_chan.dump());

            json logo = json::parse(Mongo::find_one("storage_contents_info", 
                                            "{\"type\":8, \"name\":\"" + name + "\"}" ));
            json input_net;
            input_net["_id"] = net_chan["_id"]; // same as up record 
            input_net["active"] = true;
            input_net["name"] = name;
            input_net["type"] = "MST";
            input_net["description"] = "";
            input_net["accountId"] = account["_id"];
            input_net["channelId"] = net_chan["_id"];
            input_net["url"] = chan["url"];
            input_net["static"] = true;
            input_net["virtual"] = account["virtual"];
            input_net["webPage"] = false;
            input_net["logo"] = logo["_id"].is_number() ? logo["_id"].get<int64_t>() : 0; 
            input_net["tv"] = ! is_radio(name);
            Mongo::insert("live_inputs_network", input_net.dump());
        }
        add_network_account_to_out_archive(account);
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
void add_to_output_network(int64_t type_id, const string type_name)
{
    try{
        string input_col = "live_inputs_" + type_name;
        LOG(trace) << "Try to add to live_output_network from:" << input_col;
        auto is_active =  "{\"active\":true}";
        json inputs = json::parse(Mongo::find_mony(input_col,is_active));
        for(const auto& chan : inputs){
            auto input_id = chan["_id"].get<int64_t>();
            auto filter = "{\"input\":" + to_string(input_id) + "}";

            if(!Mongo::exists("live_output_network", filter)){
                json item;
                item["_id"] = Mongo::get_uniq_id();
                item["active"] = true; 
                item["description"] = ""; 
                item["input"] = input_id; 
                item["inputType"] = type_id; 
                item["category"] = json::array(); 
                item["udp"] = false; 
                item["hls"] = false; 
                item["http"] = false; 
                item["rtsp"] = false; 
                Mongo::insert("live_output_network", item.dump());
            }
        }
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
//////////////////////////////////////////////////////////////////////////////// APIs
void live_satellites_names_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_satellites_names");
}
void live_satellites_frequencies_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_satellites_frequencies");
}
void live_satellites_channels_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_satellites_channels");
}
void live_tuners_system_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    try{                                                            
        res.set_header("Content-type", "application/json");         
        res.set_status(200);                                        
        auto is_dvbt = [](std::string name){
            return name.find("0x62") != std::string::npos;
        };
        auto in_dvb_vec = Hardware::detect_input_tuners();
        auto out_dvb_vec = Hardware::detect_output_tuners();
        json tuners = json::array();
        for( auto [id, name] : in_dvb_vec ){
            json j;
            j["_id"] = id;
            j["systemId"] = id;
            j["name"] = name;
            j["dvbt"] = is_dvbt(name); 
            j["inputDvb"] = true; 
            tuners.push_back(j);
        }
        for( auto [id, name] : out_dvb_vec ){
            json j;
            j["_id"] = id;
            j["systemId"] = id;
            j["name"] = name;
            j["dvbt"] = true;  // TODO: for dvbs modulator
            j["inputDvb"] = false; 
            tuners.push_back(j);
        }
        res << tuners.dump(2);
    }catch(std::exception& e){                                      
        LOG(error) << e.what();                       
    }
}
void live_tuners_scan_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    int64_t id;
    if(!Util::get_id(req, id) ){
        ERRORSEND(res, 400, 1024, "Invalid tuner id!");
    }
    auto tuner = Mongo::find_id("live_tuners_info", id);
    if(tuner.size() < 10 ){
        ERRORSEND(res, 400, 1025, "Invalid tuner!");
    }
    res.set_header("Content-type", "application/json");     
    json channs = Hardware::scan_input_tuner(tuner);
    if(channs["total"] > 0){
        res << channs.dump(2);
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1026, channs["error"]);             \
    }
}
void func_del_input_dvb_if_invalid()
{
    json chan_list = json::parse(Mongo::find_mony("live_inputs_dvb", "{}"));

    vector<int64_t> id_list;
    for(const auto& chan : chan_list){
        auto tuner_id = chan["dvbId"];
        if(!Mongo::exists_id("live_tuners_info", tuner_id)){
            id_list.push_back(chan["_id"]);
        }
        Mongo::remove_id("live_inputs_dvb", chan["_id"]);
    }
    
    func_del_from_outputs_and_processed(id_list);
}
void func_del_input_net_if_invalid()
{
    json chan_list = json::parse(Mongo::find_mony("live_inputs_network", "{}"));

    vector<int64_t> id_list;
    for(const auto& chan : chan_list){
        if(chan["type"] == "MST"){
            auto account_id = chan["accountId"];
            if(!Mongo::exists_id("live_network_accounts", account_id)){
                id_list.push_back(chan["_id"]);
            }
            Mongo::remove_id("live_inputs_network", chan["_id"]);
        }
    }
    func_del_from_outputs_and_processed(id_list);
}
void live_tuners_scan_bw_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    ERRORSEND(res, 400, 1050, "NOT IMPLEMENTED!");
}
void live_network_channels_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_network_channels");
}
void live_inputs_types_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_inputs_types");
}
void live_profiles_mix_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_profiles_mix");
}
void live_profiles_transcode_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_profiles_transcode");
}
void live_profiles_scramble_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_profiles_scramble");
}
void live_network_accounts_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_network_accounts");
}
void live_tuners_info_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_tuners_info");
}
void live_inputs_dvb_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    func_del_input_dvb_if_invalid();
    GET_COL("live_inputs_dvb");
}
void live_inputs_archive_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_inputs_archive");
}
void live_inputs_network_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    func_del_input_net_if_invalid();
    GET_COL("live_inputs_network");
}
void live_inputs_transcode_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_inputs_transcode");
}
void live_inputs_scramble_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_inputs_scramble");
}
void live_inputs_mix_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_inputs_mix");
}
void live_output_dvb_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    remove_or_disable_output_channels_if_needs("live_output_dvb");
    GET_COL("live_output_dvb");
}
void live_output_network_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;

    remove_or_disable_output_channels_if_needs("live_output_network");

    // add inputs 
    json types = json::parse(Mongo::find_mony("live_inputs_types", "{}"));
    for(const auto& type : types){
        add_to_output_network(type["_id"], type["name"]);
    }

    GET_COL("live_output_network");
}
void live_output_archive_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    remove_or_disable_output_channels_if_needs("live_output_archive");
    GET_COL("live_output_archive");
}
///////////////////////////
void live_profiles_mix_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_profiles_mix");
}
void live_profiles_transcode_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_profiles_transcode");
}
void live_profiles_scramble_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_profiles_scramble");
}
void live_network_accounts_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_network_accounts");
    std::thread t(func_add_network_account, j);
    t.detach();
    // TODO: ... 
}
void live_tuners_info_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_tuners_info");
    if(j["systemId"] < 1000 )
        func_add_tuner_info(j);
    // TODO: ... 
}
void live_inputs_dvb_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_inputs_dvb");
}
void live_inputs_archive_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_inputs_archive");
}
void live_inputs_network_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_inputs_network");
}
void live_inputs_transcode_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_inputs_transcode");
}
void live_inputs_scramble_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_inputs_scramble");
}
void live_inputs_mix_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_inputs_mix");
}
void live_output_dvb_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_output_dvb");
}
void live_output_network_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_output_network");
}
void live_output_archive_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_output_archive");
}

///////////////////////////
void live_profiles_mix_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_profiles_mix");
}
void live_profiles_transcode_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_profiles_transcode");
}
void live_profiles_scramble_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_profiles_scramble");
}
void live_network_accounts_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    int64_t id;
    if(!Util::get_id(req, id) ){   
        ERRORSEND(res, 400, 1027, "Invalid id!"); 
    }                                            
    bool changed = false;
    json new_rec = json::parse(req.body());   
    json old_rec = json::parse(Mongo::find_id("live_network_accounts", id));
    if(new_rec["url"] != old_rec["url"]) 
        changed = true;

    if(changed)
        func_del_network_account(id);

    PUT_ID_COL("live_network_accounts");

    if(changed){
        std::thread t(func_add_network_account, new_rec);
        t.detach();
    }
}
void live_tuners_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;

    int64_t id;
    if(!Util::get_id(req, id) ){   
        ERRORSEND(res, 400, 1028, "Invalid id!"); 
    }                                            
    bool changed = false;
    json new_rec = json::parse(req.body());   
    json old_rec = json::parse(Mongo::find_id("live_tuners_info", id));
    if(new_rec["frequencyId"] != old_rec["frequencyId"]) 
        changed = true;

    if(changed)
        func_del_tuner_info(id);

    PUT_ID_COL("live_tuners_info");

    if(changed)
        func_add_tuner_info(new_rec);
}
void live_inputs_dvb_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_dvb");
}
void live_inputs_archive_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_archive");
}
void live_inputs_network_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_network");
}
void live_inputs_transcode_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_transcode");
}
void live_inputs_scramble_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_scramble");
}
void live_inputs_mix_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_mix");
}
void live_output_dvb_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_output_dvb");
}
void live_output_network_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_output_network");
}
void live_output_archive_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_output_archive");
}
///////////////////////////
void live_profiles_mix_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_profiles_mix");
}
void live_profiles_transcode_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_profiles_transcode");
}
void live_profiles_scramble_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_profiles_scramble");
}
void live_network_accounts_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_network_accounts");
    func_del_network_account(id);
}
void live_tuners_info_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_tuners_info");
    func_del_tuner_info(id);
}
void live_inputs_dvb_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_dvb");
    func_del_from_outputs_and_processed(id);
}
void live_inputs_archive_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_archive");
    func_del_from_outputs_and_processed(id);
}
void live_inputs_network_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_network");
    func_del_from_outputs_and_processed(id);
}
void live_inputs_transcode_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_transcode");
    func_del_from_outputs_and_processed(id);
}
void live_inputs_scramble_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_scramble");
    func_del_from_outputs_and_processed(id);
}
void live_inputs_mix_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_mix");
    func_del_from_outputs_and_processed(id);
}
void live_output_dvb_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_output_dvb");
}
void live_output_network_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_output_network");
}
void live_output_archive_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_output_archive");
}

/*
   void live_tuners_input_scan_get(served::response &res, const served::request &req)
   {
   CHECK_AUTH;
   int64_t id;
   if(!Util::get_id(req, id) ){
   ERRORSEND(res, 400, 1002, "Invalid id!");
   }
   auto tuner = Mongo::find_id("live_tuners_input", id);
   if(tuner.size() < 10 ){
   ERRORSEND(res, 400, 1002, "Invalid tuner!");
   }
   res.set_header("Content-type", "application/json");     
   json channs = Hardware::scan_input_tuner(tuner);
   if(channs["total"] > 0){
   res << channs.dump();
   res.set_status(200);
   }else{
   ERRORSEND(res, 400, 1008, channs["error"]);             \
   }
   }
   */
