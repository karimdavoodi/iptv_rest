#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "system.hpp"
#include <chrono>
#include <served/methods.hpp>
#include <served/status.hpp>

void system_location_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("system_location");
}
void system_location_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("system_location");
}

void system_network_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("system_network");
}
void system_network_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("system_network");
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
    auto auth = req.header("Authorization").substr(6); // remove "Base "
    auto text = base64_decode(auth);
    auto pos = text.find(':');
    if(pos == std::string::npos) return;
    auto user = text.substr(0,pos);
    res << Mongo::find_one("system_users","{\"user\": \"" + user + "\"}");
    res.set_status(200);                                        \
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
    GET_ID1_COL("system_pms");
}
void system_pms_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("system_pms");
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
void system_backup_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    sys_backup();
    SEND_FILE("backup.zip");	
}
void system_backup_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_FILE("backup.zip");	
    sys_restore();
}

void system_license_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("system_license");
}
void system_license_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_FILE("license.bin");	
    std::string from = std::string(MEDIA_ROOT) + "license.bin";
    if(boost::filesystem::exists(from)){
        boost::filesystem::copy_file(from, "/opt/sms/lic.bin");
    }
}
void system_firmware_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_FILE("firmware.deb");	
    std::string deb = std::string(MEDIA_ROOT) + "firmware.deb";
    if(boost::filesystem::exists(deb)){
        auto cmd = std::string("dpkg -i ") + deb;
        std::system(cmd.c_str());
    }
    sys_update();
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
    if(send_http_cmd("/start"))
        res.set_status(served::status_2XX::OK);
    else
        res.set_status(served::status_5XX::INTERNAL_SERVER_ERROR);
}
void system_stop_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    if(send_http_cmd("/stop"))
        res.set_status(served::status_2XX::OK);
    else
        res.set_status(served::status_5XX::INTERNAL_SERVER_ERROR);
}
void system_reboot_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    if(send_http_cmd("/reboot"))
        res.set_status(served::status_2XX::OK);
    else
        res.set_status(served::status_5XX::INTERNAL_SERVER_ERROR);
}

