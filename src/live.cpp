#include "mongo_driver.hpp"
#include "hardware.hpp"
#include "auth.hpp"
#include "util.hpp"
#include "live.hpp"

void live_tuners_hardware_input_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    res.set_header("Content-type", "application/json");     
    res << Hardware::input_tuners();
    res.set_status(200);
}
void live_tuners_hardware_output_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    res.set_header("Content-type", "application/json");     
    res << Hardware::output_tuners();
    res.set_status(200);
}
void live_tuners_input_scan_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    int id;
    if(!get_id(req, id) ){
        ERRORSEND(res, 400, 1002, "Invalid id!");
    }
    auto tuner = Mongo::find_id("live_tuners_input", id);
    if(tuner.size() == 0 ){
        ERRORSEND(res, 400, 1002, "Invalid tuner!");
    }
    res.set_header("Content-type", "application/json");     
    res << Hardware::scan_input_tuner(tuner);
    res.set_status(200);
}

void live_tuners_input_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_tuners_input");
}
void live_tuners_input_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_tuners_input");
}
void live_tuners_input_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_tuners_input");
}
void live_tuners_input_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_tuners_input");
}

void live_tuners_output_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID1_COL("live_tuners_output");
}
void live_tuners_output_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID1_COL("live_tuners_output");
}
void live_tuners_output_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID1_COL("live_tuners_output");
}
void live_tuners_output_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("live_tuners_output");
}
void live_inputs_types_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_types");
}
void live_inputs_dvb_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_dvb");
}
void live_inputs_dvb_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_dvb");
}
void live_inputs_dvb_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_dvb");
}
void live_inputs_dvb_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_dvb");
}
void live_inputs_archive_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_archive");
}
void live_inputs_archive_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_archive");
}
void live_inputs_archive_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_archive");
}
void live_inputs_archive_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_archive");
}
void live_inputs_network_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_network");
}
void live_inputs_network_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_network");
}
void live_inputs_network_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_network");
}
void live_inputs_network_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_network");
}
void live_inputs_web_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_web");
}
void live_inputs_web_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_web");
}
void live_inputs_web_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_web");
}
void live_inputs_web_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_web");
}
void live_inputs_virtual_net_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_virtual_net");
}
void live_inputs_virtual_net_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_virtual_net");
}
void live_inputs_virtual_net_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_virtual_net");
}
void live_inputs_virtual_net_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_virtual_net");
}
void live_inputs_virtual_dvb_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_virtual_dvb");
}
void live_inputs_virtual_dvb_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_virtual_dvb");
}
void live_inputs_virtual_dvb_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_virtual_dvb");
}
void live_inputs_virtual_dvb_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_virtual_dvb");
}
void live_inputs_transcode_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_transcode");
}
void live_inputs_transcode_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_transcode");
}
void live_inputs_transcode_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_transcode");
}
void live_inputs_transcode_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_transcode");
}
void live_transcode_profile_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_transcode_profile");
}
void live_transcode_profile_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_transcode_profile");
}
void live_transcode_profile_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_transcode_profile");
}
void live_transcode_profile_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_transcode_profile");
}
void live_cccam_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_cccam");
}
void live_cccam_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_cccam");
}
void live_cccam_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_cccam");
}
void live_cccam_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_cccam");
}
void live_inputs_unscramble_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_unscramble");
}
void live_inputs_unscramble_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_unscramble");
}
void live_inputs_unscramble_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_unscramble");
}
void live_inputs_unscramble_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_unscramble");
}
void live_inputs_scramble_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_inputs_scramble");
}
void live_inputs_scramble_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_inputs_scramble");
}
void live_inputs_scramble_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_inputs_scramble");
}
void live_inputs_scramble_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_inputs_scramble");
}
void live_output_silver_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_output_silver");
}
void live_output_silver_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_output_silver");
}
void live_output_silver_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_output_silver");
}
void live_output_silver_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_output_silver");
}
void live_output_gold_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_output_gold");
}
void live_output_gold_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_output_gold");
}
void live_output_gold_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_output_gold");
}
void live_output_gold_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_output_gold");
}
void live_icons_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_icons");
}
void live_icons_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_icons");
}
void live_icons_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_icons");
}
void live_icons_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_icons");
}
