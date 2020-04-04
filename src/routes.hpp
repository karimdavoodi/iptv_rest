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
