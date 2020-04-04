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
    int id = 1;
    if(Mongo::exists_id("live_tuners_output", id)){
        ERRORSEND(res, 400, 1002, "Not insert, exists by _id = 1!");
    }
    Mongo::insert("live_tuners_output", req.body());
    res.set_status(200);
}
void live_tuners_output_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    int id = 1;
    if(!Mongo::exists_id("live_tuners_output", id)){
        ERRORSEND(res, 400, 1002, "Not update, not exists by _id!");
    }
    Mongo::replace_by_id("live_tuners_output", id, req.body());
    res.set_status(200);
}
void live_tuners_output_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    int id = 1;
    if(!Mongo::exists_id("live_tuners_output", id)){
        ERRORSEND(res, 400, 1002, "Not remove, not exists by _id!");
    }
    Mongo::remove_by_id("live_tuners_output", id);
    res.set_status(200);
}
void live_tuners_output_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    int id = 1;
    res << Mongo::find_id("live_tuners_output", id);
    res.set_status(200);
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
