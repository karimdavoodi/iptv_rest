//////////////  LAUNCHER    /////////////////////////////////////////////////////
LOG(trace) << "Add route /launcher/* ";
mux.handle("/launcher/components/info/{id}")
        .get(launcher_components_info_get)
        .del(launcher_components_info_del)
        .put(launcher_components_info_put);
mux.handle("/launcher/components/info")
        .get(launcher_components_info_get)
        .post(launcher_components_info_post);
mux.handle("/launcher/components/types/{id}")
        .get(launcher_components_types_get);
mux.handle("/launcher/components/types")
        .get(launcher_components_types_get);
mux.handle("/launcher/components/fonts/{id}")
        .get(launcher_components_fonts_get);
mux.handle("/launcher/components/fonts")
        .get(launcher_components_fonts_get);
mux.handle("/launcher/menu/{id}")
        .get (launcher_menu_get)
        .put (launcher_menu_put)
        .del (launcher_menu_del);
mux.handle("/launcher/menu")
        .post(launcher_menu_post)
        .get (launcher_menu_get);
mux.handle("/launcher/setting/{id}")
        .get (launcher_setting_get)
        .put (launcher_setting_put)
        .del (launcher_setting_del);
mux.handle("/launcher/setting")
        .post(launcher_setting_post)
        .get (launcher_setting_get);
////////////////////// USERS //////////////////////////////////////////////////
LOG(trace) << "Add route /users/* ALL_METHODS";
mux.handle("/users/group/{id}")
        .get (users_group_get)
        .put (users_group_put)
        .del (users_group_del);
mux.handle("/users/group")
        .post(users_group_post)
        .get (users_group_get);
mux.handle("/users/user/{id}")
        .get (users_user_get)
        .put (users_user_put)
        .del (users_user_del);
mux.handle("/users/user")
        .post(users_user_post)
        .get (users_user_get);
mux.handle("/users/message/to/{id}")
        .get (users_message_to_get)
        .put (users_message_to_put)
        .del (users_message_to_del);
mux.handle("/users/message/to")
        .post(users_message_to_post)
        .get (users_message_to_get);
mux.handle("/users/message/from/{id}")
        .get (users_message_from_get)
        .put (users_message_from_put)
        .del (users_message_from_del);
mux.handle("/users/message/from")
        .post(users_message_from_post)
        .get (users_message_from_get);
mux.handle("/users/message/broadcast/{id}")
        .get (users_message_broadcast_get)
        .put (users_message_broadcast_put)
        .del (users_message_broadcast_del);
mux.handle("/users/message/broadcast")
        .post(users_message_broadcast_post)
        .get (users_message_broadcast_get);
////////////////////// LIVE //////////////////////////////////////////////////
LOG(trace) << "Add route /live/* ALL_METHODS";

mux.handle("/live/satellites/names/{id}")      
	.get(live_satellites_names_get)
	.put(live_satellites_names_put)
	.del(live_satellites_names_del);
mux.handle("/live/satellites/names")      
	.get(live_satellites_names_get)
	.post(live_satellites_names_post);

mux.handle("/live/satellites/frequencies/{id}")      
	.get(live_satellites_frequencies_get)
	.put(live_satellites_frequencies_put)
	.del(live_satellites_frequencies_del);
mux.handle("/live/satellites/frequencies")      
	.get(live_satellites_frequencies_get)
	.post(live_satellites_frequencies_post);

mux.handle("/live/satellites/channels/{id}")      
	.get(live_satellites_channels_get)
	.put(live_satellites_channels_put)
	.del(live_satellites_channels_del);
mux.handle("/live/satellites/channels")      
	.get(live_satellites_channels_get)
	.post(live_satellites_channels_post);

mux.handle("/live/tuners/system")         
    .get(live_tuners_system_get);
mux.handle("/live/tuners/scan/{id}")      
    .get(live_tuners_scan_get);
mux.handle("/live/tuners/scan_bw/{id}")   
    .get(live_tuners_scan_bw_get);
mux.handle("/live/network/channels")      
    .get(live_network_channels_get);
mux.handle("/live/inputs/types")          
    .get(live_inputs_types_get);
///////////////////
mux.handle("/live/profiles/mix/{id}")
	.get(live_profiles_mix_get)
	.put(live_profiles_mix_put)
	.del(live_profiles_mix_del);
mux.handle("/live/profiles/transcode/{id}")
	.get(live_profiles_transcode_get)
	.put(live_profiles_transcode_put)
	.del(live_profiles_transcode_del);
mux.handle("/live/profiles/scramble/{id}")
	.get(live_profiles_scramble_get)
	.put(live_profiles_scramble_put)
	.del(live_profiles_scramble_del);
mux.handle("/live/network/accounts/{id}")
	.get(live_network_accounts_get)
	.put(live_network_accounts_put)
	.del(live_network_accounts_del);
mux.handle("/live/tuners/info/{id}")
	.get(live_tuners_info_get)
	.put(live_tuners_info_put)
	.del(live_tuners_info_del);
mux.handle("/live/inputs/dvb/{id}")
	.get(live_inputs_dvb_get)
	.put(live_inputs_dvb_put)
	.del(live_inputs_dvb_del);
mux.handle("/live/inputs/archive/{id}")
	.get(live_inputs_archive_get)
	.put(live_inputs_archive_put)
	.del(live_inputs_archive_del);
mux.handle("/live/inputs/network/{id}")
	.get(live_inputs_network_get)
	.put(live_inputs_network_put)
	.del(live_inputs_network_del);
mux.handle("/live/inputs/transcode/{id}")
	.get(live_inputs_transcode_get)
	.put(live_inputs_transcode_put)
	.del(live_inputs_transcode_del);
mux.handle("/live/inputs/scramble/{id}")
	.get(live_inputs_scramble_get)
	.put(live_inputs_scramble_put)
	.del(live_inputs_scramble_del);
mux.handle("/live/inputs/mix/{id}")
	.get(live_inputs_mix_get)
	.put(live_inputs_mix_put)
	.del(live_inputs_mix_del);
mux.handle("/live/output/dvb/{id}")
	.get(live_output_dvb_get)
	.put(live_output_dvb_put)
	.del(live_output_dvb_del);
mux.handle("/live/output/network/{id}")
	.get(live_output_network_get)
	.put(live_output_network_put)
	.del(live_output_network_del);
mux.handle("/live/output/archive/{id}")
	.get(live_output_archive_get)
	.put(live_output_archive_put)
	.del(live_output_archive_del);
////////////////////////
mux.handle("/live/profiles/mix")
	.get(live_profiles_mix_get)
	.post(live_profiles_mix_post);
mux.handle("/live/profiles/transcode")
	.get(live_profiles_transcode_get)
	.post(live_profiles_transcode_post);
mux.handle("/live/profiles/scramble")
	.get(live_profiles_scramble_get)
	.post(live_profiles_scramble_post);
mux.handle("/live/network/accounts")
	.get(live_network_accounts_get)
	.post(live_network_accounts_post);
mux.handle("/live/tuners/info")
	.get(live_tuners_info_get)
	.post(live_tuners_info_post);
mux.handle("/live/inputs/dvb")
	.get(live_inputs_dvb_get)
	.post(live_inputs_dvb_post);
mux.handle("/live/inputs/archive")
	.get(live_inputs_archive_get)
	.post(live_inputs_archive_post);
mux.handle("/live/inputs/network")
	.get(live_inputs_network_get)
	.post(live_inputs_network_post);
mux.handle("/live/inputs/transcode")
	.get(live_inputs_transcode_get)
	.post(live_inputs_transcode_post);
mux.handle("/live/inputs/scramble")
	.get(live_inputs_scramble_get)
	.post(live_inputs_scramble_post);
mux.handle("/live/inputs/mix")
	.get(live_inputs_mix_get)
	.post(live_inputs_mix_post);
mux.handle("/live/output/dvb")
	.get(live_output_dvb_get)
	.post(live_output_dvb_post);
mux.handle("/live/output/network")
	.get(live_output_network_get)
	.post(live_output_network_post);
mux.handle("/live/output/archive")
	.get(live_output_archive_get)
	.post(live_output_archive_post);

////////////////////// REPORT //////////////////////////////////////////////////
LOG(trace) << "Add route /report/* GET";
mux.handle("/report/new").get(report_new_get);
mux.handle("/status/information").get(status_information_get);
mux.handle("/report/tuners").get(report_tuners_get);
mux.handle("/report/channels").get(report_channels_get);
mux.handle("/report/output_channels").get(report_output_channels_get);
mux.handle("/report/error").get(report_error_get);
mux.handle("/report/survey").get(report_survey_get);
mux.handle("/report/iptv_user").get(report_iptv_user_get);
mux.handle("/report/webui_user").get(report_webui_user_get);
mux.handle("/report/system_usage").get(report_system_usage_get);
mux.handle("/report/webui_state")
        .get(report_webui_state_get)
        .post(report_webui_state_post);

////////////////////// SYSTEM //////////////////////////////////////////////////
LOG(trace) << "Add route /system/* GET";
mux.handle("/system/operations").get(system_operations_get);
mux.handle("/system/general").get(system_general_get);
mux.handle("/system/sensor/{id}")
            .get (system_sensor_get)
            .put (system_sensor_put)
            .del (system_sensor_del);
mux.handle("/system/sensor")
            .post(system_sensor_post)
            .get (system_sensor_get);
mux.handle("/system/cities")
            .get (system_cities_get);
mux.handle("/system/location")
            .get (system_location_get)
            .put (system_location_put)
            .post(system_location_put);
mux.handle("/system/network")
            .get (system_network_get)
            .put (system_network_put)
            .post(system_network_put);
mux.handle("/system/ui_pages/{id}")
            .get (system_ui_pages_get);
mux.handle("/system/ui_pages")
            .get (system_ui_pages_get);
mux.handle("/system/users/{id}")
            .get (system_users_get)
            .put (system_users_put)
            .del (system_users_del);
mux.handle("/system/users")
            .post(system_users_post)
            .get (system_users_get);
mux.handle("/system/users_me")
            .get (system_users_me_get);
mux.handle("/system/survey/{id}")
            .get (system_survey_get)
            .put (system_survey_put)
            .del (system_survey_del);
mux.handle("/system/survey")
            .post(system_survey_post)
            .get (system_survey_get);
mux.handle("/system/pms/{id}")
            .get (system_pms_get)
            .put (system_pms_put)
            .del (system_pms_del);
mux.handle("/system/pms")
            .post(system_pms_post)
            .get (system_pms_get);
mux.handle("/system/vod_account/{id}")
            .get (system_vod_account_get)
            .put (system_vod_account_put)
            .del (system_vod_account_del);
mux.handle("/system/vod_account")
            .post(system_vod_account_post)
            .get (system_vod_account_get);
mux.handle("/system/permission/{id}")
            .get (system_permission_get)
            .put (system_permission_put)
            .del (system_permission_del);
mux.handle("/system/permission")
            .post(system_permission_post)
            .get (system_permission_get);
mux.handle("/system/weektime/{id}")
            .get (system_weektime_get)
            .put (system_weektime_put)
            .del (system_weektime_del);
mux.handle("/system/weektime")
            .post(system_weektime_post)
            .get (system_weektime_get);
mux.handle("/system/backup/list")
            .get (system_backup_list_get);
mux.handle("/system/backup/backup")
            .get (system_backup_get)
            .post(system_backup_post)
            .put (system_backup_put)
            .del (system_backup_del);
mux.handle("/system/license")
            .get (system_license_get)
            .put (system_license_put)
            .post(system_license_put);
mux.handle("/system/firmware")
            .put(system_firmware_put);
mux.handle("/system/logout")
            .get(system_logout_get);
mux.handle("/system/reboot")
            .get(system_reboot_get);
mux.handle("/system/restart")
            .get(system_restart_get);
mux.handle("/system/stop")
            .get(system_stop_get);
////////////////////// STORAGE //////////////////////////////////////////////////
LOG(trace) << "Add route /storage/* GET";
mux.handle("/storage/setting")
            .get (storage_setting_get)
            .put (storage_setting_put)
            .post(storage_setting_put);
mux.handle("/storage/status")
            .get (storage_status_get);
mux.handle("/storage/contents/types/{id}")
            .get (storage_contents_types_get);
mux.handle("/storage/contents/types")
            .get (storage_contents_types_get);
mux.handle("/storage/contents/formats/{id}")
            .get (storage_contents_formats_get);
mux.handle("/storage/contents/formats")
            .get (storage_contents_formats_get);
mux.handle("/storage/contents/platforms/{id}")
            .get (storage_platforms_get);
mux.handle("/storage/contents/platforms")
            .get (storage_platforms_get);
mux.handle("/storage/contents/categories/{id}")
            .get (storage_categories_get)
            .put (storage_categories_put)
            .del (storage_categories_del);
mux.handle("/storage/contents/categories")
            .post(storage_categories_post)
            .get (storage_categories_get);
mux.handle("/storage/contents/info/{id}")
            .get (storage_info_get)
            .put (storage_info_put)
            .del (storage_info_del);
mux.handle("/storage/contents/info")
            .post(storage_info_post)
            .get (storage_info_get);
mux.handle("/storage/contents/media/{id}") 
            .get (storage_media_get)
            .put (storage_media_put)
            .del (storage_media_del)
            .post(storage_media_post);
mux.handle("/storage/contents/poster/{id}")
            .get (storage_poster_get)
            .put (storage_poster_put)
            .del (storage_poster_del)
            .post(storage_poster_post);
mux.handle("/storage/contents/subtitle/{id}")
            .get (storage_subtitle_get)
            .put (storage_subtitle_put)
            .del (storage_subtitle_del)
            .post(storage_subtitle_post);
mux.handle("/storage/advertize/{id}")
            .get (storage_advertize_get)
            .put (storage_advertize_put)
            .del (storage_advertize_del);
mux.handle("/storage/advertize")
            .post(storage_advertize_post)
            .get (storage_advertize_get);
