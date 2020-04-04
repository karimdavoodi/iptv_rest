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
    res <<  Mongo::find_id("launcher_default", 1);
}
void launcher_default_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    if(req.body().size() == 0){
        ERRORSEND(res, 400, 1001, "No input!");
    }
    auto j = json::parse(req.body());
    if( j.count("_id") == 0 ){
        ERRORSEND(res, 400, 1002, "Invalid input JSON!(not found _id)");
    }
    if(Mongo::exists_id("launcher_default", 1))
        Mongo::replace_by_id("launcher_default",1,req.body());
    else
        Mongo::insert("launcher_default",req.body());
    res.set_status(200);

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
nlohmann::json get_json_array_scope(const served::request &req, const nlohmann::json j)
{
    int s = 0;
    int e = QUERY_SIZE;

    std::string from = req.query.get("from");
    if(from.size()>0){
        s = std::stoi(from);
        if( s < 0 || s > j.size() ) s = 0;
    }
    std::string to = req.query.get("to");
    if(to.size()>0){
        e = std::stoi(to);
        if( e < s || e > j.size() ) e = j.size();
    }else{
        e = s + QUERY_SIZE;
    }
    nlohmann::json j1;
    for(auto it = j.begin()+s; it != j.begin()+e && it != j.end(); ++it)
        j1.push_back(*it);
    nlohmann::json j2 = {
        {"total", j.size()},
        {"content", j1}
    };
    return j2;
}
void launcher_components_types_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    auto [from, to] = req_range(req);
    res << Mongo::find_id_range("components_types", from, to);
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
