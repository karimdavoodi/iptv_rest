#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void storage_setting(served::response &, const served::request &);
void storage_timeshift_setting(served::response &, const served::request &);
void storage_timeshift_files(served::response &, const served::request &);
void storage_npvr_setting(served::response &, const served::request &);
void storage_npvr_files(served::response &, const served::request &);
void storage_avod_import(served::response &, const served::request &);
void storage_avod_files(served::response &, const served::request &);
void storage_audio_book_import(served::response &, const served::request &);
void storage_audio_book_files(served::response &, const served::request &);
void storage_book_import(served::response &, const served::request &);
void storage_book_files(served::response &, const served::request &);
void storage_advertize_import(served::response &, const served::request &);
void storage_advertize_files(served::response &, const served::request &);
void storage_advertize_files_id(served::response &, const served::request &);
