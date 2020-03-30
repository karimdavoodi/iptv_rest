BOOST_LOG_TRIVIAL(trace) << "Add route /status/information";
mux.handle("/status/information").get(status_information);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/cpu_mem";
mux.handle("/status/cpu_mem").get(status_cpu_mem);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/network";
mux.handle("/status/network").get(status_network);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/storage";
mux.handle("/status/storage").get(status_storage);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/dvb";
mux.handle("/status/dvb").get(status_dvb);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/channels/input";
mux.handle("/status/channels/input").get(status_channels_input);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/channels/output";
mux.handle("/status/channels/output").get(status_channels_output);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/channels/output/view";
mux.handle("/status/channels/output/view").get(status_channels_output_view);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/users";
mux.handle("/status/users").get(status_users);
BOOST_LOG_TRIVIAL(trace) << "Add route /status/errors";
mux.handle("/status/errors").get(status_errors);
BOOST_LOG_TRIVIAL(trace) << "Add route /report/user";
mux.handle("/report/user").get(report_user);
BOOST_LOG_TRIVIAL(trace) << "Add route /report/system";
mux.handle("/report/system").get(report_system);
BOOST_LOG_TRIVIAL(trace) << "Add route /report/live";
mux.handle("/report/live").get(report_live);
BOOST_LOG_TRIVIAL(trace) << "Add route /report/vod";
mux.handle("/report/vod").get(report_vod);
BOOST_LOG_TRIVIAL(trace) << "Add route /report/component";
mux.handle("/report/component").get(report_component);
BOOST_LOG_TRIVIAL(trace) << "Add route /report/system_user";
mux.handle("/report/system_user").get(report_system_user);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/location";
mux.handle("/system/location").get(system_location);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/system_logo";
mux.handle("/system/system_logo").get(system_system_logo);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/subtitle_logo";
mux.handle("/system/subtitle_logo").get(system_subtitle_logo);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/network";
mux.handle("/system/network").get(system_network);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/users";
mux.handle("/system/users").get(system_users);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/users/id";
mux.handle("/system/users/id").get(system_users_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/pms";
mux.handle("/system/pms").get(system_pms);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/vod_account";
mux.handle("/system/vod_account").get(system_vod_account);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/vod_account/id";
mux.handle("/system/vod_account/id").get(system_vod_account_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/permission";
mux.handle("/system/permission").get(system_permission);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/permission/id";
mux.handle("/system/permission/id").get(system_permission_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/weektime";
mux.handle("/system/weektime").get(system_weektime);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/weektime/id";
mux.handle("/system/weektime/id").get(system_weektime_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/setting";
mux.handle("/storage/setting").get(storage_setting);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/timeshift/setting";
mux.handle("/storage/timeshift/setting").get(storage_timeshift_setting);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/timeshift/files";
mux.handle("/storage/timeshift/files").get(storage_timeshift_files);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/npvr/setting";
mux.handle("/storage/npvr/setting").get(storage_npvr_setting);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/npvr/files";
mux.handle("/storage/npvr/files").get(storage_npvr_files);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/avod/import";
mux.handle("/storage/avod/import").get(storage_avod_import);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/avod/files";
mux.handle("/storage/avod/files").get(storage_avod_files);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/audio_book/import";
mux.handle("/storage/audio_book/import").get(storage_audio_book_import);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/audio_book/files";
mux.handle("/storage/audio_book/files").get(storage_audio_book_files);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/book/import";
mux.handle("/storage/book/import").get(storage_book_import);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/book/files";
mux.handle("/storage/book/files").get(storage_book_files);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/advertize/import";
mux.handle("/storage/advertize/import").get(storage_advertize_import);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/advertize/files";
mux.handle("/storage/advertize/files").get(storage_advertize_files);
BOOST_LOG_TRIVIAL(trace) << "Add route /storage/advertize/files/id";
mux.handle("/storage/advertize/files/id").get(storage_advertize_files_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/backup";
mux.handle("/system/backup").get(system_backup);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/license";
mux.handle("/system/license").get(system_license);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/firmware";
mux.handle("/system/firmware").get(system_firmware);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/restart";
mux.handle("/system/restart").get(system_restart);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/stop";
mux.handle("/system/stop").get(system_stop);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/reboot";
mux.handle("/system/reboot").get(system_reboot);
BOOST_LOG_TRIVIAL(trace) << "Add route /system/logout";
mux.handle("/system/logout").get(system_logout);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/input_tuners";
mux.handle("/live/input_tuners").get(live_input_tuners);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/input_tuners_scan/id";
mux.handle("/live/input_tuners_scan/id").get(live_input_tuners_scan_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/output_tuners";
mux.handle("/live/output_tuners").get(live_output_tuners);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/dvb";
mux.handle("/live/inputs/dvb").get(live_inputs_dvb);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/dvb/id";
mux.handle("/live/inputs/dvb/id").get(live_inputs_dvb_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/archive";
mux.handle("/live/inputs/archive").get(live_inputs_archive);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/archive/id";
mux.handle("/live/inputs/archive/id").get(live_inputs_archive_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/network";
mux.handle("/live/inputs/network").get(live_inputs_network);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/network/id";
mux.handle("/live/inputs/network/id").get(live_inputs_network_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/iptv";
mux.handle("/live/inputs/iptv").get(live_inputs_iptv);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/iptv/id";
mux.handle("/live/inputs/iptv/id").get(live_inputs_iptv_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/virtual_net";
mux.handle("/live/inputs/virtual_net").get(live_inputs_virtual_net);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/virtual_net/id";
mux.handle("/live/inputs/virtual_net/id").get(live_inputs_virtual_net_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/virtual_dvb";
mux.handle("/live/inputs/virtual_dvb").get(live_inputs_virtual_dvb);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/inputs/virtual_dvb/id";
mux.handle("/live/inputs/virtual_dvb/id").get(live_inputs_virtual_dvb_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/transcode";
mux.handle("/live/transcode").get(live_transcode);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/transcode/id";
mux.handle("/live/transcode/id").get(live_transcode_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/cccam";
mux.handle("/live/cccam").get(live_cccam);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/cccam/id";
mux.handle("/live/cccam/id").get(live_cccam_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/unscramble";
mux.handle("/live/unscramble").get(live_unscramble);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/unscramble/id";
mux.handle("/live/unscramble/id").get(live_unscramble_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/scramble";
mux.handle("/live/scramble").get(live_scramble);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/scramble/id";
mux.handle("/live/scramble/id").get(live_scramble_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/output/silver";
mux.handle("/live/output/silver").get(live_output_silver);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/output/silver/id";
mux.handle("/live/output/silver/id").get(live_output_silver_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/output/gold";
mux.handle("/live/output/gold").get(live_output_gold);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/output/gold/id";
mux.handle("/live/output/gold/id").get(live_output_gold_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/icons";
mux.handle("/live/icons").get(live_icons);
BOOST_LOG_TRIVIAL(trace) << "Add route /live/icons/id";
mux.handle("/live/icons/id").get(live_icons_id);

BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/default GET & POST";
mux.handle("/launcher/default")
        .get(launcher_default_get)
        .post(launcher_default_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/background GET & POST & PUT & DEL";
mux.handle("/launcher/background/{id}")
        .get(launcher_background_get)
        .post(launcher_background_post)
        .put(launcher_background_put)
        .del(launcher_background_del);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/logo";
mux.handle("/launcher/logo/{id}")
        .get(launcher_logo_get)
        .del(launcher_logo_del)
        .put(launcher_logo_put)
        .post(launcher_logo_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/types";
mux.handle("/launcher/components/types")
        .get(launcher_components_types_get);

BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/logo";
mux.handle("/launcher/components/logo/{id}")
        .get(launcher_components_logo_get)
        .del(launcher_components_logo_del)
        .put(launcher_components_logo_put)
        .post(launcher_components_logo_post);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/components/logo";
mux.handle("/launcher/components/info/{id}")
        .get(launcher_components_info_get)
        .del(launcher_components_info_del)
        .put(launcher_components_info_put)
        .post(launcher_components_info_post);
mux.handle("/launcher/components/info")
        .get(launcher_components_info_get);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/make";
mux.handle("/launcher/make")
        .get(launcher_make_get)
        .put(launcher_make_put)
        .post(launcher_make_post)
        .del(launcher_make_delete);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/arrange";
mux.handle("/launcher/arrange").get(launcher_arrange);
BOOST_LOG_TRIVIAL(trace) << "Add route /launcher/arrange/id";
mux.handle("/launcher/arrange/id").get(launcher_arrange_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/group";
mux.handle("/users/group").get(users_group);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/group/id";
mux.handle("/users/group/id").get(users_group_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/user";
mux.handle("/users/user").get(users_user);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/user/id";
mux.handle("/users/user/id").get(users_user_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/to/userid";
mux.handle("/users/message/to/userid").get(users_message_to_userid);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/to/userid/msg_id";
mux.handle("/users/message/to/userid/msg_id").get(users_message_to_userid_msg_id);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/from/userid";
mux.handle("/users/message/from/userid").get(users_message_from_userid);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/broadcast";
mux.handle("/users/message/broadcast").get(users_message_broadcast);
BOOST_LOG_TRIVIAL(trace) << "Add route /users/message/broadcast/msg_id";
mux.handle("/users/message/broadcast/msg_id").get(users_message_broadcast_msg_id);
