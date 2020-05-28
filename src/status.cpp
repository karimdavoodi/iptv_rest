#include <fstream>
#include <utility>
#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "status.hpp"

void status_information_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("status_information");
}
void status_cpu_mem_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("status_cpu_mem");
}
void status_network_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_network");
}
void status_storage_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_storage");
}
void status_dvb_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_dvb");
}
void status_channels_input_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_channels_input");
}
void status_channels_output_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_channels_output");
}
void status_channels_output_view_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;                                                
    auto col = "status_channels_output_view";
    auto [from, to] = req_range(req);                  
    if(get_id(req, id)){                               
        std::string view = "data/screen_shots/" + id + ".jpg";
        if(boost::filesystem::exists(view)){
            send_file(res, req, view);
        }else{
            ERRORSEND(res, 400, 1002, "View not exists!");
        }
    }else{                                             
        res << Mongo::find_range(col, from, to);    
    }                                                  
    res.set_status(200);                               
}
void status_users_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_users");
}
void status_errors_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("status_errors");
}
