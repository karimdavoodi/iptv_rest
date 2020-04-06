#pragma once
#include <served/served.hpp>

void report_user_get(served::response &, const served::request &);
void report_system_get(served::response &, const served::request &);
void report_live_get(served::response &, const served::request &);
void report_vod_get(served::response &, const served::request &);
void report_component_get(served::response &, const served::request &);
void report_system_user_get(served::response &, const served::request &);
