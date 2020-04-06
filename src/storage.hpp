#pragma once
#include <served/served.hpp>

void storage_setting_get(served::response &, const served::request &);
void storage_setting_put(served::response &, const served::request &);

void storage_contents_types_get(served::response &, const served::request &);
void storage_contents_types_put(served::response &, const served::request &);
void storage_contents_types_post(served::response &, const served::request &);
void storage_contents_types_del(served::response &, const served::request &);

void storage_platforms_get(served::response &, const served::request &);
void storage_platforms_put(served::response &, const served::request &);
void storage_platforms_post(served::response &, const served::request &);
void storage_platforms_del(served::response &, const served::request &);

void storage_categories_get(served::response &, const served::request &);
void storage_categories_put(served::response &, const served::request &);
void storage_categories_post(served::response &, const served::request &);
void storage_categories_del(served::response &, const served::request &);

void storage_info_get(served::response &, const served::request &);
void storage_info_put(served::response &, const served::request &);
void storage_info_post(served::response &, const served::request &);
void storage_info_del(served::response &, const served::request &);

void storage_media_get(served::response &, const served::request &);
void storage_media_put(served::response &, const served::request &);
void storage_media_post(served::response &, const served::request &);
void storage_media_del(served::response &, const served::request &);

void storage_poster_get(served::response &, const served::request &);
void storage_poster_put(served::response &, const served::request &);
void storage_poster_post(served::response &, const served::request &);
void storage_poster_del(served::response &, const served::request &);

void storage_subtitle_get(served::response &, const served::request &);
void storage_subtitle_put(served::response &, const served::request &);
void storage_subtitle_post(served::response &, const served::request &);
void storage_subtitle_del(served::response &, const served::request &);

void storage_advertize_get(served::response &, const served::request &);
void storage_advertize_put(served::response &, const served::request &);
void storage_advertize_post(served::response &, const served::request &);
void storage_advertize_del(served::response &, const served::request &);
