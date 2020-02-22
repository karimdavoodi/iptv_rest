#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void launcher_default(served::response &, const served::request &);
void launcher_background(served::response &, const served::request &);
void launcher_logo(served::response &, const served::request &);
void launcher_make(served::response &, const served::request &);
void launcher_make_id(served::response &, const served::request &);
void launcher_arrange(served::response &, const served::request &);
void launcher_arrange_id(served::response &, const served::request &);
