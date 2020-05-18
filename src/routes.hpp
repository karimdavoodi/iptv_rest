///////////////  LAUNCHER    /////////////////////////////////////////////////////
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/* ";
mux.handle("/launcher/components/info/{id}")
        .get(launcher_components_info_get)
        .del(launcher_components_info_del)
        .put(launcher_components_info_put);
mux.handle("/launcher/components/info")
        .get(launcher_components_info_get)
        .post(launcher_components_info_post);
mux.handle("/launcher/components/types/{id}")
        .get(launcher_components_types_get)
        .del(launcher_components_types_del)
        .put(launcher_components_types_put);
mux.handle("/launcher/components/types")
        .get(launcher_components_types_get)
        .post(launcher_components_types_post);
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
BOOST_LOG_TRIVIAL(trace) << "Add route /users/* ALL_METHODS";
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
BOOST_LOG_TRIVIAL(trace) << "Add route /live/* ALL_METHODS";
mux.handle("/live/tuners/input/{id}")
        .get (live_tuners_input_get)
        .put (live_tuners_input_put)
        .del (live_tuners_input_del);
mux.handle("/live/tuners/input")
        .post(live_tuners_input_post)
        .get (live_tuners_input_get);
mux.handle("/live/tuners/output")
        .get (live_tuners_output_get)
        .put (live_tuners_output_put);
mux.handle("/live/inputs/types/{id}")
        .get (live_inputs_types_get);
mux.handle("/live/inputs/types")
        .get (live_inputs_types_get);
mux.handle("/live/inputs/dvb/{id}")
        .get (live_inputs_dvb_get)
        .put (live_inputs_dvb_put)
        .del (live_inputs_dvb_del);
mux.handle("/live/inputs/dvb")
        .post(live_inputs_dvb_post)
        .get (live_inputs_dvb_get);
mux.handle("/live/inputs/archive/{id}")
        .get (live_inputs_archive_get)
        .put (live_inputs_archive_put)
        .del (live_inputs_archive_del);
mux.handle("/live/inputs/archive")
        .post(live_inputs_archive_post)
        .get (live_inputs_archive_get);
mux.handle("/live/inputs/network/{id}")
        .get (live_inputs_network_get)
        .put (live_inputs_network_put)
        .del (live_inputs_network_del);
mux.handle("/live/inputs/network")
        .post(live_inputs_network_post)
        .get (live_inputs_network_get);
mux.handle("/live/inputs/web/{id}")
        .get (live_inputs_web_get)
        .put (live_inputs_web_put)
        .del (live_inputs_web_del);
mux.handle("/live/inputs/web")
        .post(live_inputs_web_post)
        .get (live_inputs_web_get);
mux.handle("/live/inputs/virtual_net/{id}")
        .get (live_inputs_virtual_net_get)
        .put (live_inputs_virtual_net_put)
        .del (live_inputs_virtual_net_del);
mux.handle("/live/inputs/virtual_net")
        .post(live_inputs_virtual_net_post)
        .get (live_inputs_virtual_net_get);
mux.handle("/live/inputs/virtual_dvb/{id}")
        .get (live_inputs_virtual_dvb_get)
        .put (live_inputs_virtual_dvb_put)
        .del (live_inputs_virtual_dvb_del);
mux.handle("/live/inputs/virtual_dvb")
        .post(live_inputs_virtual_dvb_post)
        .get (live_inputs_virtual_dvb_get);
mux.handle("/live/inputs/transcode/{id}")
        .get (live_inputs_transcode_get)
        .put (live_inputs_transcode_put)
        .del (live_inputs_transcode_del);
mux.handle("/live/inputs/transcode")
        .post(live_inputs_transcode_post)
        .get (live_inputs_transcode_get);
mux.handle("/live/transcode_profile/{id}")
        .get (live_transcode_profile_get)
        .put (live_transcode_profile_put)
        .del (live_transcode_profile_del);
mux.handle("/live/transcode_profile")
        .post(live_transcode_profile_post)
        .get (live_transcode_profile_get);
mux.handle("/live/cccam/{id}")
        .get (live_cccam_get)
        .put (live_cccam_put)
        .del (live_cccam_del);
mux.handle("/live/cccam")
        .post(live_cccam_post)
        .get (live_cccam_get);
mux.handle("/live/inputs/unscramble/{id}")
        .get (live_inputs_unscramble_get)
        .put (live_inputs_unscramble_put)
        .del (live_inputs_unscramble_del);
mux.handle("/live/inputs/unscramble")
        .post(live_inputs_unscramble_post)
        .get (live_inputs_unscramble_get);
mux.handle("/live/inputs/scramble/{id}")
        .get (live_inputs_scramble_get)
        .put (live_inputs_scramble_put)
        .del (live_inputs_scramble_del);
mux.handle("/live/inputs/scramble")
        .post(live_inputs_scramble_post)
        .get (live_inputs_scramble_get);
mux.handle("/live/output/silver/{id}")
        .get (live_output_silver_get)
        .put (live_output_silver_put)
        .del (live_output_silver_del);
mux.handle("/live/output/silver")
        .post(live_output_silver_post)
        .get (live_output_silver_get);
mux.handle("/live/output/gold/{id}")
        .get (live_output_gold_get)
        .put (live_output_gold_put)
        .del (live_output_gold_del);
mux.handle("/live/output/gold")
        .post(live_output_gold_post)
        .get (live_output_gold_get);
mux.handle("/live/icons/{id}")
        .get (live_icons_get)
        .put (live_icons_put)
        .del (live_icons_del);
mux.handle("/live/icons")
        .post(live_icons_post)
        .get (live_icons_get);
mux.handle("/live/tuners/hardware/input")
        .get (live_tuners_hardware_input_get);
mux.handle("/live/tuners/hardware/output")
        .get (live_tuners_hardware_output_get);
mux.handle("/live/tuners/scan/{id}")
        .get (live_tuners_input_scan_get);
////////////////////// STATUS //////////////////////////////////////////////////
BOOST_LOG_TRIVIAL(trace) << "Add route /status/* GET";
mux.handle("/status/information").get(status_information_get);
mux.handle("/status/cpu_mem").get(status_cpu_mem_get);
mux.handle("/status/network").get(status_network_get);
mux.handle("/status/storage").get(status_storage_get);
mux.handle("/status/dvb").get(status_dvb_get);
mux.handle("/status/channels_input").get(status_channels_input_get);
mux.handle("/status/channels_output").get(status_channels_output_get);
mux.handle("/status/channels_output_view/{id}").get(status_channels_output_view_get);
mux.handle("/status/users").get(status_users_get);
mux.handle("/status/error").get(status_errors_get);
////////////////////// REPORT //////////////////////////////////////////////////
BOOST_LOG_TRIVIAL(trace) << "Add route /report/* GET";
mux.handle("/report/user").get(report_user_get);
mux.handle("/report/system").get(report_system_get);
mux.handle("/report/live").get(report_live_get);
mux.handle("/report/vod").get(report_vod_get);
mux.handle("/report/component").get(report_component_get);
mux.handle("/report/system_user").get(report_system_user_get);
////////////////////// SYSTEM //////////////////////////////////////////////////
BOOST_LOG_TRIVIAL(trace) << "Add route /system/* GET";
mux.handle("/system/location")
            .get (system_location_get)
            .put (system_location_put)
            .post(system_location_put);
mux.handle("/system/network")
            .get (system_network_get)
            .put (system_network_put)
            .post(system_network_put);
mux.handle("/system/users/{id}")
            .get (system_users_get)
            .put (system_users_put)
            .del (system_users_del);
mux.handle("/system/users")
            .post(system_users_post)
            .get (system_users_get);
mux.handle("/system/users_me")
            .get (system_users_me_get);
mux.handle("/system/pms")
            .get (system_pms_get)
            .put (system_pms_put)
            .post(system_pms_put);
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
mux.handle("/system/backup")
            .get (system_backup_get)
            .put (system_backup_put)
            .post(system_backup_put);
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
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/* GET";
mux.handle("/storage/setting")
            .get (storage_setting_get)
            .put (storage_setting_put)
            .post(storage_setting_put);
mux.handle("/storage/contents/types/{id}")
            .get (storage_contents_types_get);
//            .put (storage_contents_types_put)
//            .del (storage_contents_types_del)
//            .post(storage_contents_types_post);
mux.handle("/storage/contents/types")
            .get (storage_contents_types_get);
mux.handle("/storage/contents/formats/{id}")
            .get (storage_contents_formats_get);
//            .put (storage_contents_formats_put)
//            .del (storage_contents_formats_del)
//            .post(storage_contents_formats_post);
mux.handle("/storage/contents/formats")
            .get (storage_contents_formats_get);
mux.handle("/storage/contents/platforms/{id}")
            .get (storage_platforms_get);
//            .put (storage_platforms_put)
//            .del (storage_platforms_del)
//            .post(storage_platforms_post);
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
