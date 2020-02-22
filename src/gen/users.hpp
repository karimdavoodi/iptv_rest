#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include "main_storage.hpp"

void users_group(served::response &, const served::request &);
void users_group_id(served::response &, const served::request &);
void users_user(served::response &, const served::request &);
void users_user_id(served::response &, const served::request &);
void users_message_to_userid(served::response &, const served::request &);
void users_message_to_userid_msg_id(served::response &, const served::request &);
void users_message_from_userid(served::response &, const served::request &);
void users_message_broadcast(served::response &, const served::request &);
void users_message_broadcast_msg_id(served::response &, const served::request &);
