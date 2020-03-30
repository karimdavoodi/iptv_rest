#include <algorithm>
#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <nlohmann/json.hpp>
#define  QUERY_SIZE 10
#include "auth.hpp"
#include "launcher.hpp"

extern MainStorage st;
void launcher_default_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    res << st.getJson("configs", "launcher_default").dump(4);
}
void launcher_default_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    if(req.body().size() == 0){
        ERRORSEND(res, 400, 1001, "No input!");
    }
    auto j = json::parse(req.body());
    if( j.count("launcher") == 0 || j.count("welcome") == 0 ){
        ERRORSEND(res, 400, 1002, "Invalid input JSON!");
    }
    st.setJson("configs", "launcher_default", j);
    res.set_status(200);

}
bool save_file(served::response &res, const served::request &req, const std::string path)
{
    BOOST_LOG_TRIVIAL(trace) << "Save " << path;
    std::ofstream bg(path, std::ios_base::binary);
    if(bg.is_open()){
        bg.write(req.body().c_str(), req.body().size());
        bg.close(); 
        res.set_status(200);
        BOOST_LOG_TRIVIAL(trace) << "Saved: " << path;
        return true;
    }
    return false;
}
bool send_file(served::response &res, const served::request &req, const std::string path)
{
    BOOST_LOG_TRIVIAL(trace) << "Send " << path;
    std::ifstream bg(path, std::ios_base::binary);
    if(bg.is_open()){
        res.set_body(std::string(
                    (std::istreambuf_iterator<char>(bg) ),
                    (std::istreambuf_iterator<char>()    )
                    ));
        res.set_header("Content-type", "image/png");
        res.set_header("Content-Lenght", std::to_string(res.body_size()));
        res.set_status(200);
        return true;
    }
    return false;
}
bool get_id(const served::request &req, std::string& id)
{
    id = req.params["id"];
    //std::cout  << "ID:" << id << std::endl;
    if(id.size() < 1) return false;
    return true;
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

    res <<  get_json_array_scope(req, st.getComponentsTypes()).dump(4);
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
    std::string id;
    if(!get_id(req, id)){ // get range 
        res <<  get_json_array_scope(req, 
                    st.getJson("configs", "launcher_components_info")).dump(4);
        return;
    }
    auto j = st.getJson("configs", "launcher_components_info");
    res << j[std::stoi(id)].dump(4);
}
void launcher_components_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid info id!");
    }
    auto j = json::parse(req.body());
    if( j.count("name") == 0 || j.count("id") == 0 ){
        ERRORSEND(res, 400, 1002, "Invalid input JSON!");
    }
    auto jall = st.getJson("configs", "launcher_components_info");
    jall[std::stoi(id)] = j;
    st.setJson("configs", "launcher_components_info", jall);
    res.set_status(200);
}
void launcher_components_info_post(served::response &res, const served::request &req)
{
    launcher_components_info_put(res, req);
}
void launcher_components_info_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    std::string id;
    if(!get_id(req, id)){
        ERRORSEND(res, 400, 1003, "Invalid info id!");
    }
    int _id = std::stoi(id);
    auto jall = st.getJson("configs", "launcher_components_info");
    for(size_t i=0; i<jall.size(); ++i){
        if(jall[i]["id"].get<int>() = _id){

        }
    } 
    jall[std::stoi(id)] = j;
    st.setJson("configs", "launcher_components_info", jall);
    res.set_status(200);
}
void launcher_make_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
}
void launcher_make_post(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
	CHECK_AUTH;
}
void launcher_make_put(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
	CHECK_AUTH;
    if(req.body().size() == 0){
        ERRORSEND(res, 400, 1001, "No input!");
    }
    auto j = json::parse(req.body());
    int id = j["id"];
    std::cout << "id:" << id << std::endl;
    if( id == 0 ){
        ERRORSEND(res, 400, 1002, "Invalid input JSON!");
    }
    json make = st.getJson("configs", "launcher_make");
    if(make.size() == 0 ){
        make = json::array();
        std::cout << "Make empty make\n";
    } 
    make = {j, j};
    //make.push_back(j);
    st.setJson("configs", "launcher_make", j);
    res.set_status(200);
}
void launcher_make_delete(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
	CHECK_AUTH;
}
void launcher_arrange(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_arrange";
	CHECK_AUTH;
}
void launcher_arrange_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_arrange_id";
	CHECK_AUTH;
}
