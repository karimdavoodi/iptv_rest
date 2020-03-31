#pragma once
#include <served/served.hpp>

void launcher_default_get(served::response &, const served::request &);
void launcher_default_post(served::response &, const served::request &);

void launcher_background_get(served::response &, const served::request &);
void launcher_background_post(served::response &, const served::request &);
void launcher_background_put(served::response &, const served::request &);
void launcher_background_del(served::response &, const served::request &);

void launcher_logo_get(served::response &, const served::request &);
void launcher_logo_post(served::response &, const served::request &);
void launcher_logo_put(served::response &, const served::request &);
void launcher_logo_del(served::response &, const served::request &);

void launcher_components_types_get(served::response &, const served::request &);
void launcher_components_logo_get(served::response &, const served::request &);
void launcher_components_logo_post(served::response &, const served::request &);
void launcher_components_logo_put(served::response &, const served::request &);
void launcher_components_logo_del(served::response &, const served::request &);

void launcher_menu_get(served::response &, const served::request &);
void launcher_menu_put(served::response &, const served::request &);
void launcher_menu_del(served::response &, const served::request &);
void launcher_menu_post(served::response &, const served::request &);

void launcher_components_info_get(served::response &, const served::request &);
void launcher_components_info_put(served::response &, const served::request &);
void launcher_components_info_del(served::response &, const served::request &);
void launcher_components_info_post(served::response &, const served::request &);

