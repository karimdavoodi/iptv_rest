#include <sstream>
#include <string>
#include "auth.hpp"
#include "util.hpp"
#include "live.hpp"
#include "hardware.hpp"
#include "mongo_driver.hpp"
using namespace std;

void del_live_inputs_dvb(long tuner_id)
{
    try{
        string sfilter = "{\"dvbId\":" + to_string(tuner_id) + "}";
        Mongo::remove_mony("live_inputs_dvb", sfilter);
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
void add_live_inputs_dvb(json& tuner)
{
    try{
        // check if tuner is inputDvb
        string sfilter = "{\"systemId\":" + to_string(tuner["systemId"].get<long>()) + "}";
        json tuner_system = json::parse(Mongo::find_one("live_tuners_system", sfilter));
        if(tuner_system["inputDvb"].is_boolean() && tuner_system["inputDvb"] == false ){
            LOG(debug) << "Tuner type is not input";
            return;
        }
        
        del_live_inputs_dvb(tuner["_id"]);

        string ffilter = "{\"frequencyId\":" + 
                            to_string(tuner["frequencyId"].get<long>()) + "}";
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
            dvb_chan["logo"] = logo["_id"].is_number() ? logo["_id"].get<int>() : 0; 
            dvb_chan["tv"] = chan["videoId"] > 0 ; 
            dvb_chan["dvbId"] = tuner["_id"]; 
            dvb_chan["channelId"] = chan["_id"]; 
            Mongo::insert("live_inputs_dvb", dvb_chan.dump());
        }
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
void del_live_network_channels(long account_id)
{
    try{
        json filter;
        filter["accountId"] = account_id;
        Mongo::remove_mony("live_network_channels", filter.dump());
    }catch(std::exception& e){                                      
        BOOST_LOG_TRIVIAL(error) << e.what();                       
    }
}
json get_iptv_account_channels(const std::string url)
{
    json list = json::array();
    string ans = Util::get_url(url);
    if(!ans.size()) return list;
    //  #EXTINF:1000771,IRIB TV1000671
    //  http://:8771/live.ts
    istringstream in(ans);
    
    string line, chan_name, chan_url;
    while( in >> line ){
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

    return list;
}
void add_live_network_channels(json& account)
{
    try{
        json channels_list = get_iptv_account_channels(account["url"]);
        if(!channels_list.size()) return;
        for(const auto& chan : channels_list){
            json net_chan;
            net_chan["_id"] = Mongo::get_uniq_id(); 
            net_chan["name"] = chan["name"]; 
            net_chan["url"] = chan["url"]; 
            net_chan["accountId"] = account["_id"]; 
            Mongo::insert("live_network_channels", net_chan.dump());
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
    uint64_t id;
    if(!Util::get_id(req, id) ){
        ERRORSEND(res, 400, 1002, "Invalid tuner id!");
    }
    auto tuner = Mongo::find_id("live_tuners_info", id);
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
    GET_COL("live_output_dvb");
}
void live_output_network_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
    GET_COL("live_output_network");
}
void live_output_archive_get(served::response &res , const served::request &req)
{
    CHECK_AUTH;
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
    CHECK_AUTH;
    // delete current net channels
    uint64_t id;
    if(!Util::get_id(req, id) ){   
        ERRORSEND(res, 400, 1002, "Invalid id!"); 
    }                                            
    del_live_network_channels(id);

    PUT_ID_COL("live_network_accounts");
    
    // fill net channels
    json j = json::parse(req.body());                            \
    add_live_network_channels(j);
}
void live_tuners_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    // delete current dvb channels
    uint64_t id;
    if(!Util::get_id(req, id) ){   
        ERRORSEND(res, 400, 1002, "Invalid id!"); 
    }                                            
    del_live_inputs_dvb(id);

    PUT_ID_COL("live_tuners_info");
    
    // fill dvb channels
    json j = json::parse(req.body());                            \
    add_live_inputs_dvb(j);
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
    del_live_inputs_dvb(id);
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


void live_tuners_input_scan_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    uint64_t id;
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

