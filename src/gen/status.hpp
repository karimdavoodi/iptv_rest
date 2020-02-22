#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void status_information(served::response &, const served::request &);
void status_cpu_mem(served::response &, const served::request &);
void status_network(served::response &, const served::request &);
void status_storage(served::response &, const served::request &);
void status_dvb(served::response &, const served::request &);
void status_channels_input(served::response &, const served::request &);
void status_channels_output(served::response &, const served::request &);
void status_channels_output_view(served::response &, const served::request &);
void status_users(served::response &, const served::request &);
void status_errors(served::response &, const served::request &);
