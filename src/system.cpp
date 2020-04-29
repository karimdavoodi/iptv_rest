#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "system.hpp"
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
    GET_ID_COL("system_users");
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
    auto auth = req.header("Authorization");
    // TODO : get user from Base64 ... by boost/beast/core/detail/base64.hpp 
    std::string user = "test";
    res << Mongo::find("system_users","{\"user\": \"" + user + "\"}");
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
    GET_ID_COL("system_vod_account");
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
    GET_ID_COL("system_permission");
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
    GET_ID_COL("system_weektime");
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
    SEND_FILE(ICON_PATH, "backup", ZIP);	
}
void system_backup_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_FILE(ICON_PATH, "backup", ZIP);	
}

void system_license_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("system_license");
}
void system_license_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_FILE(ICON_PATH, "license", ZIP);	
}
void system_firmware_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_FILE(ICON_PATH, "firmware", ZIP);	
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
    res.set_status(served::status_2XX::OK);
    // TODO : restart system
}
void system_stop_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    res.set_status(served::status_2XX::OK);
    // TODO : stop system
}
void system_reboot_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    res.set_status(served::status_2XX::OK);
    // TODO : reboot system
}

