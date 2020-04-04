#pragma once
#include <served/served.hpp>

void live_tuners_hardware_input_get(served::response &, const served::request &);
void live_tuners_hardware_output_get(served::response &, const served::request &);
void live_tuners_input_scan_get(served::response &, const served::request &);

void live_tuners_input_get(served::response &, const served::request &);
void live_tuners_input_del(served::response &, const served::request &);
void live_tuners_input_put(served::response &, const served::request &);
void live_tuners_input_post(served::response &, const served::request &);

void live_tuners_output_get(served::response &, const served::request &);
void live_tuners_output_del(served::response &, const served::request &);
void live_tuners_output_put(served::response &, const served::request &);
void live_tuners_output_post(served::response &, const served::request &);

void live_input_dvb_get(served::response &, const served::request &);
void live_input_dvb_del(served::response &, const served::request &);
void live_input_dvb_put(served::response &, const served::request &);
void live_input_dvb_post(served::response &, const served::request &);






void live_input_tuners(served::response &, const served::request &);
void live_input_tuners_scan_id(served::response &, const served::request &);
void live_output_tuners(served::response &, const served::request &);
void live_inputs_dvb(served::response &, const served::request &);
void live_inputs_dvb_id(served::response &, const served::request &);
void live_inputs_archive(served::response &, const served::request &);
void live_inputs_archive_id(served::response &, const served::request &);
void live_inputs_network(served::response &, const served::request &);
void live_inputs_network_id(served::response &, const served::request &);
void live_inputs_iptv(served::response &, const served::request &);
void live_inputs_iptv_id(served::response &, const served::request &);
void live_inputs_virtual_net(served::response &, const served::request &);
void live_inputs_virtual_net_id(served::response &, const served::request &);
void live_inputs_virtual_dvb(served::response &, const served::request &);
void live_inputs_virtual_dvb_id(served::response &, const served::request &);
void live_transcode(served::response &, const served::request &);
void live_transcode_id(served::response &, const served::request &);
void live_cccam(served::response &, const served::request &);
void live_cccam_id(served::response &, const served::request &);
void live_unscramble(served::response &, const served::request &);
void live_unscramble_id(served::response &, const served::request &);
void live_scramble(served::response &, const served::request &);
void live_scramble_id(served::response &, const served::request &);
void live_output_silver(served::response &, const served::request &);
void live_output_silver_id(served::response &, const served::request &);
void live_output_gold(served::response &, const served::request &);
void live_output_gold_id(served::response &, const served::request &);
void live_icons(served::response &, const served::request &);
void live_icons_id(served::response &, const served::request &);
