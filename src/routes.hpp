///////////////  LAUNCHER    /////////////////////////////////////////////////////
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/default GET & POST";
mux.handle("/launcher/default")
        .get(launcher_default_get)
        .post(launcher_default_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/background/{id} ALL_METHODS";
mux.handle("/launcher/background/{id}")
        .get(launcher_background_get)
        .post(launcher_background_post)
        .put(launcher_background_put)
        .del(launcher_background_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/logo/{id} ALL_METHODS";
mux.handle("/launcher/logo/{id}")
        .get(launcher_logo_get)
        .del(launcher_logo_del)
        .put(launcher_logo_put)
        .post(launcher_logo_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/types GET";
mux.handle("/launcher/components/types")
        .get(launcher_components_types_get);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/logo/{id} ALL_METHODS";
mux.handle("/launcher/components/logo/{id}")
        .get(launcher_components_logo_get)
        .del(launcher_components_logo_del)
        .put(launcher_components_logo_put)
        .post(launcher_components_logo_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/info/{id} ALL_METHODS";
mux.handle("/launcher/components/info/{id}")
        .get(launcher_components_info_get)
        .del(launcher_components_info_del)
        .put(launcher_components_info_put)
        .post(launcher_components_info_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/info GET";
mux.handle("/launcher/components/info")
        .get(launcher_components_info_get);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/menu/{id} ALL_METHODS";
mux.handle("/launcher/menu/{id}")
        .get (launcher_menu_get)
        .put (launcher_menu_put)
        .post(launcher_menu_post)
        .del (launcher_menu_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/menu GET";
mux.handle("/launcher/menu")
        .get (launcher_menu_get);
////////////////////// USERS //////////////////////////////////////////////////
BOOST_LOG_TRIVIAL(trace) << "Add route /users/group/{id} ALL_METHODS";
mux.handle("/users/group/{id}")
        .get (users_group_get)
        .put (users_group_put)
        .post(users_group_post)
        .del (users_group_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/group GET";
mux.handle("/users/group")
        .get (users_group_get);

BOOST_LOG_TRIVIAL(trace) << "Add route /users/user/{id} ALL_METHODS";
mux.handle("/users/user/{id}")
        .get (users_user_get)
        .put (users_user_put)
        .post(users_user_post)
        .del (users_user_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/user GET";
mux.handle("/users/user")
        .get (users_user_get);

BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/to/{id} ALL_METHODS";
mux.handle("/users/message/to/{id}")
        .get (users_message_to_get)
        .put (users_message_to_put)
        .post(users_message_to_post)
        .del (users_message_to_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/from/{id} ALL_METHODS";
mux.handle("/users/message/from/{id}")
        .get (users_message_from_get)
        .put (users_message_from_put)
        .post(users_message_from_post)
        .del (users_message_from_del);

BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/broadcast/{id} ALL_METHODS";
mux.handle("/users/message/broadcast/{id}")
        .get (users_message_broadcast_get)
        .put (users_message_broadcast_put)
        .post(users_message_broadcast_post)
        .del (users_message_broadcast_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/broadcast GET";
mux.handle("/users/message/broadcast")
        .get (users_message_broadcast_get);
////////////////////// LIVE //////////////////////////////////////////////////

BOOST_LOG_TRIVIAL(trace) << "Add route /live/tuners/input/{id} ALL_METHODS";
mux.handle("/live/tuners/input/{id}")
        .get (live_tuners_input_get)
        .put (live_tuners_input_put)
        .post(live_tuners_input_post)
        .del (live_tuners_input_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/tuners/input GET";
mux.handle("/live/tuners/input")
        .get (live_tuners_input_get);

BOOST_LOG_TRIVIAL(trace) << "Add route /live/tuners/output ALL_METHODS";
mux.handle("/live/tuners/output")
        .get (live_tuners_output_get)
        .put (live_tuners_output_put)
        .post(live_tuners_output_post)
        .del (live_tuners_output_del);

BOOST_LOG_TRIVIAL(trace) << "Add route /live/input/dvb/{id} ALL_METHODS";
mux.handle("/live/input/dvb/{id}")
        .get (live_input_dvb_get)
        .put (live_input_dvb_put)
        .post(live_input_dvb_post)
        .del (live_input_dvb_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/input/dvb GET";
mux.handle("/live/input/dvb")
        .get (live_input_dvb_get);

BOOST_LOG_TRIVIAL(trace) << "Add route /live/tuners/hardware/input GET";
mux.handle("/live/tuners/hardware/input")
        .get (live_tuners_hardware_input_get);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/tuners/hardware/output GET";
mux.handle("/live/tuners/hardware/output")
        .get (live_tuners_hardware_output_get);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/tuners/input/scan/{id} GET";
mux.handle("/live/tuners/input/scan/{id}")
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
mux.handle("/status/channels_output_view").get(status_channels_output_view_get);
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
mux.handle("/system/system_logo")
            .get (system_system_logo_get)
            .put (system_system_logo_put)
            .post(system_system_logo_put);
mux.handle("/system/subtitle_logo")
            .get (system_subtitle_logo_get)
            .put (system_subtitle_logo_put)
            .post(system_subtitle_logo_put);
mux.handle("/system/network")
            .get (system_network_get)
            .put (system_network_put)
            .post(system_network_put);
mux.handle("/system/users")
            .get (system_users_get);
mux.handle("/system/users/{id}")
            .get (system_users_get)
            .put (system_users_put)
            .del (system_users_del)
            .post(system_users_post);
mux.handle("/system/users/me")
            .get (system_users_me_get);
mux.handle("/system/pms")
            .get (system_pms_get)
            .put (system_pms_put)
            .post(system_pms_put);
mux.handle("/system/vod_account")
            .get (system_vod_account_get);
mux.handle("/system/vod_account/{id}")
            .get (system_vod_account_get)
            .put (system_vod_account_put)
            .del (system_vod_account_del)
            .post(system_vod_account_post);
mux.handle("/system/permission")
            .get (system_permission_get);
mux.handle("/system/permission/{id}")
            .get (system_permission_get)
            .put (system_permission_put)
            .del (system_permission_del)
            .post(system_permission_post);
mux.handle("/system/weektime")
            .get (system_weektime_get);
mux.handle("/system/weektime/{id}")
            .get (system_weektime_get)
            .put (system_weektime_put)
            .del (system_weektime_del)
            .post(system_weektime_post);
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
mux.handle("/storage/contents/types")
            .get (storage_contents_types_get);
mux.handle("/storage/contents/types/{id}")
            .get (storage_contents_types_get)
            .put (storage_contents_types_put)
            .del (storage_contents_types_del)
            .post(storage_contents_types_post);
mux.handle("/storage/contents/platforms")
            .get (storage_platforms_get);
mux.handle("/storage/contents/platforms/{id}")
            .get (storage_platforms_get)
            .put (storage_platforms_put)
            .del (storage_platforms_del)
            .post(storage_platforms_post);
mux.handle("/storage/contents/categories")
            .get (storage_categories_get);
mux.handle("/storage/contents/categories/{id}")
            .get (storage_categories_get)
            .put (storage_categories_put)
            .del (storage_categories_del)
            .post(storage_categories_post);
mux.handle("/storage/contents/info")
            .get (storage_info_get);
mux.handle("/storage/contents/info/{id}")
            .get (storage_info_get)
            .put (storage_info_put)
            .del (storage_info_del)
            .post(storage_info_post);
mux.handle("/storage/contents/media")
            .get (storage_media_get)
            .put (storage_media_put)
            .del (storage_media_del)
            .post(storage_media_post);
mux.handle("/storage/contents/poster")
            .get (storage_poster_get)
            .put (storage_poster_put)
            .del (storage_poster_del)
            .post(storage_poster_post);
mux.handle("/storage/contents/subtitle")
            .get (storage_subtitle_get)
            .put (storage_subtitle_put)
            .del (storage_subtitle_del)
            .post(storage_subtitle_post);
mux.handle("/storage/advertize")
            .get (storage_advertize_get);
mux.handle("/storage/advertize/{id}")
            .get (storage_advertize_get)
            .put (storage_advertize_put)
            .del (storage_advertize_del)
            .post(storage_advertize_post);
