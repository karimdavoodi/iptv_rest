#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void launcher_default_get(served::response &, const served::request &);
void launcher_default_post(served::response &, const served::request &);
void launcher_background_get(served::response &, const served::request &);
void launcher_background_post(served::response &, const served::request &);
void launcher_logo(served::response &, const served::request &);
void launcher_make(served::response &, const served::request &);
void launcher_make_id(served::response &, const served::request &);
void launcher_arrange(served::response &, const served::request &);
void launcher_arrange_id(served::response &, const served::request &);
