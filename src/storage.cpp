#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "storage.hpp"
#include <boost/filesystem/operations.hpp>
using namespace std;

void del_all_media_related_records(const served::request &req, int64_t id)
{
    try{
        auto media_path = Util::get_content_path(req, id);
        Util::remove_file(media_path);

        // TODO: do only for VIDEO and AUDIO type!
        if(media_path.find("/Video/") != string::npos ||
           media_path.find("/Audio/") != string::npos){

            if(media_path.find("/Video/") != string::npos){
                Util::remove_file(MEDIA_ROOT "Subtitle/" + to_string(id) + ".srt");
                Util::remove_file(MEDIA_ROOT "Poster/" + to_string(id) + ".jpg");
            }            
            // Also remove form inputs/archive  
            json archive_channels = json::parse(Mongo::find_mony("live_inputs_archive", "{}"));
            for(auto& chan : archive_channels){
                if(chan["contents"].is_null()) continue;
                json new_contents = json::array();
                for(auto& content : chan["contents"]){
                    if(content["content"].is_null()) continue;
                    if(content["content"] != id){
                        new_contents.push_back(content);
                    }else{
                        LOG(info) << "remove content id " << id << " from chan " << chan["name"]; 
                    }
                }
                if(new_contents.size() != chan["contents"].size()){
                    chan["contents"].clear();
                    chan["contents"] = new_contents;
                    Mongo::update_id("live_inputs_archive", chan["_id"], chan.dump());
                }
            }
        }
    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }
}
void storage_status_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    json status;
    status["_id"] = 1;
    status["timeShift"] = json::object();
    status["timeShift"]["freeSizeGB"] = 1000;
    status["timeShift"]["freeRecordTime"] = 40;
    status["NPVR"] = json::object();
    status["NPVR"]["freeSizeGB"] = 1000;
    status["NPVR"]["freeRecordTime"] = 40;
    res.set_header("Content-Type", "application/json");
    res.set_status(200);                                    
    res << status.dump(2); 
}
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
        int64_t id;                                                  
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
        LOG(error) << e.what();                   
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
    {                 
        int64_t id;     
        if(!Util::get_id(req, id)){      
            ERRORSEND(res, 400, 1006, "Id not exists in url!");  
        }                                                       
        del_all_media_related_records(req, id);
    }                                                       
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
