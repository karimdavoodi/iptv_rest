//
/*
 *   users_me  - set Cookie
 *   
 *
 *
 *
 * */
#include "auth.hpp"

#include "mongo_driver.hpp"
#include "util.hpp"
#include "system.hpp"
#include "hardware.hpp"
#include <chrono>
#include <ctime>
using namespace std;
time_t currentTime = 0;
string currentZone;
void system_general_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_general");
}
void system_location_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    try{                                                        
        json net = json::parse(Mongo::find_id("system_location", 1));      
        // Read system time and zone
        currentTime = time(nullptr);
        net["systemTime"] = long(currentTime);
        ifstream zone("/etc/timezone");
        if(zone.is_open()) zone >> currentZone; 
        net["timeZone"] = currentZone;
        
        res.set_header("Content-type", "application/json");     
        res << net.dump(2);                                          
        res.set_status(200);                                    
    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }                       
}
void system_location_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("system_location");
    try{
        json system_location = json::parse(req.body());
        auto now = system_location["systemTime"].get<long>();
        auto tzone = system_location["timeZone"].get<string>();
        if(now != currentTime){
            LOG(info) << "Set time:" << now;
            struct timespec n {};
            n.tv_sec = now;
            n.tv_nsec = 0;
            clock_settime(CLOCK_REALTIME, &n); // FIXME: not work
        }
        if(tzone != currentZone){
            LOG(info) << "Set timeZone:" << tzone;
            ofstream zone("/etc/timezone");
            if(zone.is_open()) zone <<  tzone;
        }
    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }                       
}
void system_network_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    try{                                                        
        // Get current system interfaces
        auto system_nics = Hardware::detect_interfaces();

        // Get from net config fron DB
        json net = json::parse(Mongo::find_id("system_network", 1));      
        if(net["interfaces"].is_null())
            net["interfaces"] = json::array();
        json valid_nics = json::array();
        int i = 1;
        for(const auto& interface : system_nics){
            json nic = json::object();
            nic["_id"] = i++;
            nic["name"] = interface["name"];
            nic["ip"] = interface["ip"];
            nic["mask"] = interface["mask"];
            nic["description"] = "";
            for(const auto& _nic : net["interfaces"]){
                if(nic["name"].get<string>() == _nic["name"].get<string>()){
                    //nic["ip"] = _nic["ip"];   Don't overwrite DB ip to system ip
                    //nic["mask"] = _nic["mask"];
                    nic["description"] = _nic["description"];
                    break;
                }
            }
            valid_nics.push_back(nic);
        }
        net["interfaces"].clear();
        net["interfaces"] = valid_nics;
        net["_id"] = 1;
        if(net["dns"].is_null()) net["dns"] = "";
        if(net["gateway"].is_null()) net["gateway"] = "";
        if(net["mainInterface"].is_null()) net["mainInterface"] = "";
        if(net["multicastBase"].is_null()) net["multicastBase"] = "";
        if(net["multicastInterface"].is_null()) net["multicastInterface"] = "";
        if(net["addressForNAT"].is_null()) net["addressForNAT"] = "";
        if(net["staticRoute"].is_null()) net["staticRoute"] = json::array();
        if(net["firewallRule"].is_null()) net["firewallRule"] = json::array();

        res.set_header("Content-type", "application/json");     
        res << net.dump(2);                                          
        res.set_status(200);                                    
        Mongo::update_id("system_network", 1, net.dump());

    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }                       
}
void system_network_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("system_network");
    try{
        json net = json::parse(req.body());
        //Hardware::apply_network(net); 
        Hardware::save_network(net);
    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }                       
}
void system_users_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_users");
}
void system_users_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("system_users");
}
void system_users_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("system_users");
}
void system_users_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("system_users");
}
void system_users_me_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;

    auto auth_str = req.header("Authorization");
    if(auth_str.empty()){
        ERRORSEND(res, 401, 1000, "Not Authorized!"); 
    }
    auto auth = auth_str.substr(6); // remove "Base "
    auto text = Util::base64_decode(auth);
    auto pos = text.find(':');
    if(pos == std::string::npos) return;
    auto user = text.substr(0,pos);
    res << Mongo::find_one("system_users","{\"user\": \"" + user + "\"}");
    res.set_status(200);                                        
}
void system_cities_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_cities");
}
void system_survey_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_survey");
}
void system_survey_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("system_survey");
}
void system_survey_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("system_survey");
}
void system_survey_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("system_survey");
}
void system_pms_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_pms");
}
void system_pms_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("system_pms");
}
void system_pms_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("system_pms");
}
void system_pms_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("system_pms");
}

void system_vod_account_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_vod_account");
}
void system_vod_account_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("system_vod_account");
}
void system_vod_account_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("system_vod_account");
}
void system_vod_account_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("system_vod_account");
}
void system_permission_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_permission");
}
void system_permission_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("system_permission");
}
void system_permission_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("system_permission");
}
void system_permission_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("system_permission");
}

void system_weektime_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("system_weektime");
}
void system_weektime_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("system_weektime");
}
void system_weektime_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("system_weektime");
}
void system_weektime_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("system_weektime");
}
void system_backup_list_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    auto path = string(MEDIA_ROOT) + "Backup/";
    CHECK_PATH(path);
    json list = json::array();
    for(const auto& file : boost::filesystem::directory_iterator(path)){
        string name = file.path().filename().c_str();
        json item = json::object();
        item["name"] = (string)file.path().filename().c_str();
        item["size"] = (long)boost::filesystem::file_size(file);
        item["time"] = (long)boost::filesystem::last_write_time(file); 
        list.push_back(item);
    }
    json all = json::object();
    all["total"] = list.size();
    all["content"] = list;
    res << all.dump(2);
    res.set_status(200);
}
void system_backup_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    auto name = req.query.get("name");
    if(!name.empty()){
        auto path = "Backup/" + name;
        SEND_FILE(path);	
        res.set_header("Content-type", "application/octet-stream");
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1019, "Parameter required");
    }
}
void system_backup_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    auto name = req.query.get("name");
    if(!name.empty()){
        auto path = "Backup/" + name;
        if(path.find(".gz") == string::npos)
            path = path + ".gz";
        Util::sys_backup(path);
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1020, "Parameter required");
    }
}
void system_backup_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    auto name = req.query.get("name");
    if(!name.empty()){
        auto path = "Backup/" + name;
        Util::sys_restore(path);
        res.set_status(200);
    }else{
        ERRORSEND(res, 400, 1021, "Parameter required");
    }
}
void system_backup_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    auto name = req.query.get("name");
    if(!name.empty()){
        auto path = string(MEDIA_ROOT) +  "Backup/" + name;
        if(Util::remove_file(path)){
            res.set_status(200);
        }else{
            ERRORSEND(res, 400, 1022, "Fie not found!");
        }
    }else{
        ERRORSEND(res, 400, 1023, "Parameter required");
    }
}
void system_license_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("system_license");
}
void system_license_put(served::response &res, const served::request &req)
{
    try{
        CHECK_AUTH;
        RECV_FILE("license.bin");	
        std::string from = std::string(MEDIA_ROOT) + "license.bin";
        if(boost::filesystem::exists(from)){
            LOG(debug) << "Copy " << from << " to /opt/sms/lic.bin";
            boost::filesystem::copy_file(from, "/opt/sms/lic.bin", 
                    boost::filesystem::copy_option::overwrite_if_exists);
        }
    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }                       
}
void system_firmware_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    RECV_FILE("firmware.deb");	
    std::string deb = std::string(MEDIA_ROOT) + "firmware.deb";
    if(boost::filesystem::exists(deb)){
        auto cmd = std::string("dpkg -i ") + deb;
        Util::system(cmd);
    }
    res.set_status(200);
}
void system_logout_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    res.set_status(served::status_2XX::OK);
    // TODO : do nothing...
}
void system_restart_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    if(!Util::send_http_cmd("/start").empty())
        res.set_status(served::status_2XX::OK);
    else
        res.set_status(served::status_5XX::INTERNAL_SERVER_ERROR);
    Util::build_temp_records();
}
void system_stop_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    if(!Util::send_http_cmd("/stop").empty())
        res.set_status(served::status_2XX::OK);
    else
        res.set_status(served::status_5XX::INTERNAL_SERVER_ERROR);
}
void system_reboot_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    if(!Util::send_http_cmd("/reboot").empty())
        res.set_status(served::status_2XX::OK);
    else
        res.set_status(served::status_5XX::INTERNAL_SERVER_ERROR);
}
void system_operations_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("system_operations");
}
void system_sensor_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("system_sensor");
}
void system_sensor_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("system_sensor");
}
void system_sensor_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("system_sensor");
}
void system_sensor_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("system_sensor");
}

