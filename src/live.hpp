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

void live_inputs_types_get(served::response &, const served::request &);

void live_inputs_dvb_get(served::response &, const served::request &);
void live_inputs_dvb_del(served::response &, const served::request &);
void live_inputs_dvb_put(served::response &, const served::request &);
void live_inputs_dvb_post(served::response &, const served::request &);

void live_inputs_archive_get(served::response &, const served::request &);
void live_inputs_archive_del(served::response &, const served::request &);
void live_inputs_archive_put(served::response &, const served::request &);
void live_inputs_archive_post(served::response &, const served::request &);

void live_inputs_network_get(served::response &, const served::request &);
void live_inputs_network_del(served::response &, const served::request &);
void live_inputs_network_put(served::response &, const served::request &);
void live_inputs_network_post(served::response &, const served::request &);

void live_inputs_transcode_get(served::response &, const served::request &);
void live_inputs_transcode_del(served::response &, const served::request &);
void live_inputs_transcode_put(served::response &, const served::request &);
void live_inputs_transcode_post(served::response &, const served::request &);

void live_inputs_web_get(served::response &, const served::request &);
void live_inputs_web_del(served::response &, const served::request &);
void live_inputs_web_put(served::response &, const served::request &);
void live_inputs_web_post(served::response &, const served::request &);

void live_inputs_mixed_get(served::response &, const served::request &);
void live_inputs_mixed_del(served::response &, const served::request &);
void live_inputs_mixed_put(served::response &, const served::request &);
void live_inputs_mixed_post(served::response &, const served::request &);

void live_inputs_virtual_net_get(served::response &, const served::request &);
void live_inputs_virtual_net_del(served::response &, const served::request &);
void live_inputs_virtual_net_put(served::response &, const served::request &);
void live_inputs_virtual_net_post(served::response &, const served::request &);

void live_inputs_virtual_dvb_get(served::response &, const served::request &);
void live_inputs_virtual_dvb_del(served::response &, const served::request &);
void live_inputs_virtual_dvb_put(served::response &, const served::request &);
void live_inputs_virtual_dvb_post(served::response &, const served::request &);

void live_transcode_profile_get(served::response &, const served::request &);
void live_transcode_profile_del(served::response &, const served::request &);
void live_transcode_profile_put(served::response &, const served::request &);
void live_transcode_profile_post(served::response &, const served::request &);

void live_cccam_get(served::response &, const served::request &);
void live_cccam_del(served::response &, const served::request &);
void live_cccam_put(served::response &, const served::request &);
void live_cccam_post(served::response &, const served::request &);

void live_inputs_unscramble_get(served::response &, const served::request &);
void live_inputs_unscramble_del(served::response &, const served::request &);
void live_inputs_unscramble_put(served::response &, const served::request &);
void live_inputs_unscramble_post(served::response &, const served::request &);

void live_inputs_scramble_get(served::response &, const served::request &);
void live_inputs_scramble_del(served::response &, const served::request &);
void live_inputs_scramble_put(served::response &, const served::request &);
void live_inputs_scramble_post(served::response &, const served::request &);

void live_output_silver_get(served::response &, const served::request &);
void live_output_silver_del(served::response &, const served::request &);
void live_output_silver_put(served::response &, const served::request &);
void live_output_silver_post(served::response &, const served::request &);

void live_output_gold_get(served::response &, const served::request &);
void live_output_gold_del(served::response &, const served::request &);
void live_output_gold_put(served::response &, const served::request &);
void live_output_gold_post(served::response &, const served::request &);

void live_icons_get(served::response &, const served::request &);
void live_icons_del(served::response &, const served::request &);
void live_icons_put(served::response &, const served::request &);
void live_icons_post(served::response &, const served::request &);


