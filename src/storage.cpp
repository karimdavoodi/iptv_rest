#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "storage.hpp"
using namespace std;

void storage_setting_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("storage_setting");
}
void storage_setting_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("storage_setting");
}
void storage_contents_types_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("storage_contents_types");
}
void storage_contents_types_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_contents_types");
}
void storage_contents_types_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_contents_types");
}
void storage_contents_types_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_contents_types");
}
void storage_platforms_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("storage_contents_platforms");
}
void storage_platforms_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_contents_platforms");
}
void storage_platforms_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_contents_platforms");
}
void storage_platforms_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_contents_platforms");
}
void storage_categories_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("storage_contents_categories");
}
void storage_categories_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_contents_categories");
}
void storage_categories_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_contents_categories");
}
void storage_categories_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_contents_categories");
}
void storage_info_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    auto col = "storage_contents_info";

    try{                                                         
        int id;                                                  
        std::string result = "";
        res.set_header("Content-type", "application/json");      
        if(Util::get_id(req, id)){                               
            result =  Mongo::find_id(col, id);                      
        }else{                                                   
            auto [from, to] = Util::req_range(req);              
            const std::string parameters = Util::req_parameters(req); 
            result =  Mongo::find_filter_range(col, parameters, from, to);                         
        }   
        // Add media status
        if(result.size()){
            json list = json::parse(result);
            if(!list["content"].is_null()){
                for(auto& item : list["content"] ){
                    item["files_exist"] = Util::check_media_exists(req, item["_id"]);
                }
            }else if(!list["_id"].is_null()){
                    list["files_exist"] = Util::check_media_exists(req, list["_id"]);
            }
            res << list.dump(2); 
        }
        res.set_status(200);                                    
    }catch(std::exception& e){                                  
        BOOST_LOG_TRIVIAL(error) << e.what();                   
    };
}
void storage_info_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_contents_info");
}
void storage_info_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_contents_info");
}
void storage_info_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_contents_info");
}
void storage_media_get(served::response &res, const served::request &req)
{
	//CHECK_AUTH;
    SEND_ID_FILE;
}
void storage_media_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE;
}
void storage_media_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE;
}
void storage_media_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_FILE;
}
void storage_poster_get(served::response &res, const served::request &req)
{
	//CHECK_AUTH;
    SEND_ID_FILE;
}
void storage_poster_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE;
}
void storage_poster_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE;
}
void storage_poster_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_FILE;
}
void storage_subtitle_get(served::response &res, const served::request &req)
{
	//CHECK_AUTH;
    SEND_ID_FILE;
}
void storage_subtitle_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE;
}
void storage_subtitle_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE;
}
void storage_subtitle_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_FILE;
}
void storage_advertize_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("storage_advertize");
}
void storage_advertize_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_advertize");
}
void storage_advertize_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_advertize");
}
void storage_advertize_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_advertize");
}
void storage_contents_formats_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("storage_contents_formats");
}
