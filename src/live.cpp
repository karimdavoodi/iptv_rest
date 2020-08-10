#include "auth.hpp"
#include "util.hpp"
#include "live.hpp"
#include "hardware.hpp"
#include "mongo_driver.hpp"

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
        int id;                                                     
        res.set_header("Content-type", "application/json");         
        res.set_status(200);                                        
        auto is_dvbt = [](string name){
            return true;
        };
        auto in_dvb_vec = Hardware::detect_input_tuners();
        auto out_dvb_vec = Hardware::detect_output_tuners();
        json tuners = json::array();
        int i = 0;
        for( auto [id, name] : in_dvb_vec ){
            json j;
            j["_id"] = i++;
            j["systemId"] = id;
            j["name"] = name;
            j["dvbt"] = is_dvbt(name); 
            j["inputDvb"] = true; 
            tuners.push_back(j);
        }
        for( auto [id, name] : out_dvb_vec ){
            json j;
            j["_id"] = i++;
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
    GET_COL("live_tuners_scan");
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
}
void live_tuners_info_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("live_tuners_info");
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
    PUT_ID_COL("live_network_accounts");
}
void live_tuners_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_tuners_info");
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
}
void live_tuners_info_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("live_tuners_info");
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
    int id;
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

