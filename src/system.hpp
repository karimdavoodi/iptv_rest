#pragma once
#include <served/served.hpp>

void system_general_get(served::response &, const served::request &);
void system_location_get(served::response &, const served::request &);
void system_location_put(served::response &, const served::request &);
void system_location_post(served::response &, const served::request &);

void system_network_get(served::response &, const served::request &);
void system_network_put(served::response &, const served::request &);

void system_users_get(served::response &, const served::request &);
void system_users_put(served::response &, const served::request &);
void system_users_del(served::response &, const served::request &);
void system_users_post(served::response &, const served::request &);

void system_cities_get(served::response &, const served::request &);

void system_users_me_get(served::response &, const served::request &);

void system_survey_get(served::response &, const served::request &);
void system_survey_put(served::response &, const served::request &);
void system_survey_del(served::response &, const served::request &);
void system_survey_post(served::response &, const served::request &);

void system_pms_get(served::response &, const served::request &);
void system_pms_put(served::response &, const served::request &);
void system_pms_del(served::response &, const served::request &);
void system_pms_post(served::response &, const served::request &);

void system_vod_account_get(served::response &, const served::request &);
void system_vod_account_put(served::response &, const served::request &);
void system_vod_account_del(served::response &, const served::request &);
void system_vod_account_post(served::response &, const served::request &);

void system_permission_get(served::response &, const served::request &);
void system_permission_put(served::response &, const served::request &);
void system_permission_post(served::response &, const served::request &);
void system_permission_del(served::response &, const served::request &);

void system_weektime_get(served::response &, const served::request &);
void system_weektime_put(served::response &, const served::request &);
void system_weektime_del(served::response &, const served::request &);
void system_weektime_post(served::response &, const served::request &);

void system_backup_list_get(served::response &, const served::request &);
void system_backup_get(served::response &, const served::request &);
void system_backup_post(served::response &, const served::request &);
void system_backup_put(served::response &, const served::request &);
void system_backup_del(served::response &, const served::request &);
    
void system_license_get(served::response &, const served::request &);
void system_license_put(served::response &, const served::request &);
void system_firmware_put(served::response &, const served::request &);

void system_restart_get(served::response &, const served::request &);
void system_stop_get(served::response &, const served::request &);
void system_reboot_get(served::response &, const served::request &);
void system_logout_get(served::response &, const served::request &);

void system_operations_get(served::response &res, const served::request &req);
void system_sensor_get(served::response &res, const served::request &req);
void system_sensor_put(served::response &res, const served::request &req);
void system_sensor_post(served::response &res, const served::request &req);
void system_sensor_del(served::response &res, const served::request &req);
