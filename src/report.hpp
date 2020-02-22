#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void report_user(served::response &, const served::request &);
void report_system(served::response &, const served::request &);
void report_live(served::response &, const served::request &);
void report_vod(served::response &, const served::request &);
void report_component(served::response &, const served::request &);
void report_system_user(served::response &, const served::request &);
