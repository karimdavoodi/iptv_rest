#include <nlohmann/json.hpp>
#include "mongo_driver.hpp"
#include "hardware.hpp"
#include "auth.hpp"
#include "util.hpp"
#include "live.hpp"

void live_tuners_hardware_input_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    res << Hardware::input_tuners();
    res.set_status(200);
}
void live_tuners_hardware_output_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
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
void live_input_dvb_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("live_input_dvb");
}
void live_input_dvb_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("live_input_dvb");
}
void live_input_dvb_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("live_input_dvb");
}
void live_input_dvb_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("live_input_dvb");
}
