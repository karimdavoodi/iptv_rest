#pragma once
#include <served/served.hpp>

void launcher_default_get(served::response &, const served::request &);
void launcher_default_post(served::response &, const served::request &);

void launcher_menu_get(served::response &, const served::request &);
void launcher_menu_put(served::response &, const served::request &);
void launcher_menu_del(served::response &, const served::request &);
void launcher_menu_post(served::response &, const served::request &);

void launcher_components_info_get(served::response &, const served::request &);
void launcher_components_info_put(served::response &, const served::request &);
void launcher_components_info_del(served::response &, const served::request &);
void launcher_components_info_post(served::response &, const served::request &);

void launcher_setting_get(served::response &, const served::request &);
void launcher_setting_put(served::response &, const served::request &);
void launcher_setting_del(served::response &, const served::request &);
void launcher_setting_post(served::response &, const served::request &);

void launcher_components_types_get(served::response &, const served::request &);
void launcher_components_types_put(served::response &, const served::request &);
void launcher_components_types_del(served::response &, const served::request &);
void launcher_components_types_post(served::response &, const served::request &);

