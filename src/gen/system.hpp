#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void system_location(served::response &, const served::request &);
void system_system_logo(served::response &, const served::request &);
void system_subtitle_logo(served::response &, const served::request &);
void system_network(served::response &, const served::request &);
void system_users(served::response &, const served::request &);
void system_users_id(served::response &, const served::request &);
void system_pms(served::response &, const served::request &);
void system_vod_account(served::response &, const served::request &);
void system_vod_account_id(served::response &, const served::request &);
void system_permission(served::response &, const served::request &);
void system_permission_id(served::response &, const served::request &);
void system_weektime(served::response &, const served::request &);
void system_weektime_id(served::response &, const served::request &);
void system_backup(served::response &, const served::request &);
void system_license(served::response &, const served::request &);
void system_firmware(served::response &, const served::request &);
void system_restart(served::response &, const served::request &);
void system_stop(served::response &, const served::request &);
void system_reboot(served::response &, const served::request &);
void system_logout(served::response &, const served::request &);
