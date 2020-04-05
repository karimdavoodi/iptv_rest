#include <algorithm>
#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <nlohmann/json.hpp>
#include <utility>
#include "auth.hpp"
#include "launcher.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"

void launcher_default_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID1_COL("launcher_default");
}
void launcher_default_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID1_COL("launcher_default");
}
void launcher_background_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;

    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }

    std::string bg_name = "conf/icon/background_" + id + ".png";
    if(!send_file(res, req, bg_name)){
        ERRORSEND(res, 403, 1004, "background not found! " + bg_name);
    }
}
void launcher_background_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }
    CHECK_PATH("conf/icon"); 

    std::string bg_name = "conf/icon/background_" + id + ".png";
    if(!save_file(res, req, bg_name)){
        ERRORSEND(res, 400, 1007, "Can't save image!" + bg_name);
    }
}
void launcher_background_put(served::response &res, const served::request &req)
{
    launcher_background_post(res, req);
}
void launcher_background_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }
    CHECK_PATH("conf/icon"); 
    std::string bg_name = "conf/icon/background_" + id + ".png";
    if(std::filesystem::exists(bg_name)){
        std::filesystem::remove(bg_name); 
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1006, "File not found!");
    }
}

void launcher_logo_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;

    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid launcher id!");
    }
    std::string lang = req.query.get("language");
    if(lang.size() < 1){
        ERRORSEND(res, 400, 1003, "Invalid language id!");
    }
    std::string bg_name = "conf/icon/logo_" + id + "_" + lang + ".png";
    if(!send_file(res, req, bg_name)){
        ERRORSEND(res, 403, 1004, "logo not found! " + bg_name);
    }
}
void launcher_logo_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }
    CHECK_PATH("conf/icon"); 
    std::string lang = req.query.get("language");
    if(lang.size() < 1){
        ERRORSEND(res, 400, 1003, "Invalid language id!");
    }
    std::string bg_name = "conf/icon/logo_" + id + "_" + lang + ".png";

    if(!save_file(res, req, bg_name)){
        ERRORSEND(res, 400, 1007, "Can't save image!" + bg_name);
    }
}
void launcher_logo_put(served::response &res, const served::request &req)
{
    launcher_logo_post(res, req);
}
void launcher_logo_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }
    CHECK_PATH("conf/icon"); 
    std::string lang = req.query.get("language");
    if(lang.size() < 1){
        ERRORSEND(res, 400, 1003, "Invalid language id!");
    }
    std::string bg_name = "conf/icon/logo_" + id + "_" + lang + ".png";
    if(std::filesystem::exists(bg_name)){
        std::filesystem::remove(bg_name); 
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1006, "File not found!");
    }
}
void launcher_components_types_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("components_types");
}
void launcher_components_logo_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;

    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid logo id!");
    }
    std::string lang = req.query.get("launcher");
    if(lang.size() < 1){
        ERRORSEND(res, 400, 1003, "Invalid launcher id!");
    }
    std::string bg_name = "conf/icon/component_logo_" + id + "_" + lang + ".png";
    if(!send_file(res, req, bg_name)){
        ERRORSEND(res, 403, 1004, "logo not found! " + bg_name);
    }
}
void launcher_components_logo_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid logo name!");
    }
    CHECK_PATH("conf/icon"); 
    std::string lang = req.query.get("launcher");
    if(lang.size() < 1){
        ERRORSEND(res, 400, 1003, "Invalid launcher id!");
    }
    std::string bg_name = "conf/icon/component_logo_" + id + "_" + lang + ".png";

    if(!save_file(res, req, bg_name)){
        ERRORSEND(res, 400, 1007, "Can't save image!" + bg_name);
    }
}
void launcher_components_logo_put(served::response &res, const served::request &req)
{
    launcher_logo_post(res, req);
}
void launcher_components_logo_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid logo name!");
    }
    CHECK_PATH("conf/icon"); 
    std::string lang = req.query.get("launcher");
    if(lang.size() < 1){
        ERRORSEND(res, 400, 1003, "Invalid launcher id!");
    }
    std::string bg_name = "conf/icon/component_logo_" + id + "_" + lang + ".png";
    if(std::filesystem::exists(bg_name)){
        std::filesystem::remove(bg_name); 
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1006, "File not found!");
    }
}
void launcher_components_info_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("launcher_components_info");
}
void launcher_components_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("launcher_components_info");
}
void launcher_components_info_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("launcher_components_info");
}
void launcher_components_info_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("launcher_components_info");
}
void launcher_menu_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("launcher_menu");
}
void launcher_menu_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("launcher_menu");
}
void launcher_menu_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("launcher_menu");
}
void launcher_menu_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("launcher_menu");
}
