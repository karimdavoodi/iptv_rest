#include <sstream>
#include <string>
#include "auth.hpp"
#include "util.hpp"
#include "live.hpp"
#include "hardware.hpp"
#include "mongo_driver.hpp"
using namespace std;

void remove_output_channels_if_invalid(const std::string col)
{
    try{
        std::map<long, std::string> type_map;

        json types = json::parse(Mongo::find_mony("live_inputs_types", "{}"));
        for(const auto type : types) 
            type_map[type["_id"]] = type["name"];

        json channels = json::parse(Mongo::find_mony(col, "{}"));
        for(const auto& chan : channels){
            auto input_id = chan["input"];
            auto type_name = type_map[ chan["inputType"] ];
            auto input_col = "live_inputs_" + type_name;
            if(!Mongo::exists_id(input_col, input_id ))
                Mongo::remove_id(col, chan["_id"]);
        }
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
void del_live_dvb_channels(int64_t tuner_id)
{
    try{
        string sfilter = "{\"dvbId\":" + to_string(tuner_id) + "}";
        Mongo::remove_mony("live_inputs_dvb", sfilter);
        Mongo::remove_mony("live_output_dvb", sfilter);
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
void add_live_inputs_dvb(json& tuner)
{
    try{
        if(tuner["systemId"] >= 1000 ){
            LOG(debug) << "Tuner type is not input";
            return;
        }

        del_live_dvb_channels(tuner["_id"]);

        string ffilter = "{\"frequencyId\":" + 
            to_string(tuner["frequencyId"].get<int64_t>()) + "}";
        json channels_list = json::parse(Mongo::find_mony("live_satellites_channels", 
                    ffilter));

        if(!channels_list.size()){ 
            LOG(debug) << "Channel list is empty";
            return;
        }
        for(const auto& chan : channels_list){
            string filter = "{\"name\":\"" + chan["name"].get<string>() + "\"}";
            json logo = json::parse(Mongo::find_one("storage_contents_info", filter));

            json dvb_chan;
            dvb_chan["_id"] = Mongo::get_uniq_id(); 
            dvb_chan["active"] = true;
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
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
void del_live_network_channels(int64_t account_id)
{
    try{
        json filter;
        filter["accountId"] = account_id;
        Mongo::remove_mony("live_network_channels", filter.dump());
        Mongo::remove_mony("live_inputs_network", filter.dump());
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
json get_iptv_account_channels(const std::string url)
{
    json list = json::array();
    try{
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
            }else if(line.find("#") == 0 ) continue;
            else{
                chan_url = line;
                json chan;
                chan["name"] = chan_name;
                chan["url"]  = chan_url;
                list.push_back(chan);
            }
        }
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
    return list;
}
void add_live_network_channels(json& account)
{
    try{
        del_live_network_channels(account["_id"]);

        json channels_list = get_iptv_account_channels(account["url"]);
        if(!channels_list.size()) return;
        for(const auto& chan : channels_list){
            json net_chan;
            net_chan["_id"] = Mongo::get_uniq_id(); 
            net_chan["name"] = chan["name"]; 
            net_chan["url"] = chan["url"]; 
            net_chan["accountId"] = account["_id"]; 
            Mongo::insert("live_network_channels", net_chan.dump());

            json input_net;
            input_net["_id"] = net_chan["_id"]; // same as up record 
            input_net["active"] = true;
            input_net["name"] = chan["name"];
            input_net["type"] = "SST";
            input_net["description"] = "";
            input_net["accountId"] = account["_id"];
            input_net["channelId"] = net_chan["_id"];
            input_net["url"] = chan["url"];
            input_net["static"] = true;
            input_net["virtual"] = false;
            input_net["webPage"] = false;
            input_net["logo"] = 0;
            input_net["tv"] = true;
            Mongo::insert("live_inputs_network", input_net.dump());
        }
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
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
        res << tuners.dump();
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
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
        res << channs.dump();
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1026, channs["error"]);             \
    }
}
void live_tuners_scan_bw_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_tuners_scan_bw");
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
    remove_output_channels_if_invalid("live_output_dvb");
    GET_COL("live_output_dvb");
}
void add_to_output_network(int64_t type_id, const string type_name)
{
    try{
        string input_col = "live_inputs_" + type_name;
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

                Mongo::insert_if_not_exists(
                        "live_output_network",
                        filter,
                        item.dump()
                        );
            }
        }
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
void live_output_network_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;

    remove_output_channels_if_invalid("live_output_network");

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
    remove_output_channels_if_invalid("live_output_archive");
    GET_COL("live_");
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
    add_live_network_channels(j);
}
void live_tuners_info_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_tuners_info");
    add_live_inputs_dvb(j);
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
    // TODO: if account url has not changed, 
    //       don't changes live_network_accounts and live_inputs_network
    CHECK_AUTH;
    // delete current net channels
    int64_t id;
    if(!Util::get_id(req, id) ){   
        ERRORSEND(res, 400, 1027, "Invalid id!"); 
    }                                            
    del_live_network_channels(id);

    PUT_ID_COL("live_network_accounts");

    // fill net channels
    json j = json::parse(req.body());   
    add_live_network_channels(j);
}
void live_tuners_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;

    {   // delete current dvb channels
        int64_t id;
        if(!Util::get_id(req, id) ){   
            ERRORSEND(res, 400, 1028, "Invalid id!"); 
        }                                            
        del_live_dvb_channels(id);
    }

    PUT_ID_COL("live_tuners_info");

    {   // fill dvb channels
        json j = json::parse(req.body());
        add_live_inputs_dvb(j);
    }
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
    del_live_network_channels(id);
}
void live_tuners_info_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_tuners_info");
    del_live_dvb_channels(id);
}
void live_inputs_dvb_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_dvb");
}
void live_inputs_archive_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_archive");
}
void live_inputs_network_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_network");
}
void live_inputs_transcode_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_transcode");
}
void live_inputs_scramble_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_scramble");
}
void live_inputs_mix_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_inputs_mix");
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
