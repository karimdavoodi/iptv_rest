#pragma once
#include <served/served.hpp>

void status_information_get(served::response &, const served::request &);
void status_cpu_mem_get(served::response &, const served::request &);
void status_network_get(served::response &, const served::request &);
void status_storage_get(served::response &, const served::request &);
void status_dvb_get(served::response &, const served::request &);
void status_channels_input_get(served::response &, const served::request &);
void status_channels_output_get(served::response &, const served::request &);
void status_channels_output_view_get(served::response &, const served::request &);
void status_users_get(served::response &, const served::request &);
void status_errors_get(served::response &, const served::request &);
