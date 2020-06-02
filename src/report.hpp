#pragma once
#include <served/served.hpp>
void status_information_get(served::response &res, const served::request &req);
void report_system_usage_get(served::response &res, const served::request &req);
void report_iptv_user_get(served::response &res, const served::request &req);
void report_webui_user_get(served::response &res, const served::request &req);
void report_tuners_get(served::response &res, const served::request &req);
void report_channels_get(served::response &res, const served::request &req);
void report_error_get(served::response &res, const served::request &req);
void report_operations_get(served::response &res, const served::request &req);
void report_sensor_get(served::response &res, const served::request &req);
void report_sensor_put(served::response &res, const served::request &req);
void report_sensor_post(served::response &res, const served::request &req);
void report_sensor_del(served::response &res, const served::request &req);
