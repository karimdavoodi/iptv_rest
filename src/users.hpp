#pragma once
#include <served/served.hpp>

void users_group_get(served::response &, const served::request &);
void users_group_put(served::response &, const served::request &);
void users_group_del(served::response &, const served::request &);
void users_group_post(served::response &, const served::request &);
            
void users_user_get(served::response &, const served::request &);
void users_user_put(served::response &, const served::request &);
void users_user_del(served::response &, const served::request &);
void users_user_post(served::response &, const served::request &);

void users_message_to_get(served::response &, const served::request &);
void users_message_to_put(served::response &, const served::request &);
void users_message_to_del(served::response &, const served::request &);
void users_message_to_post(served::response &, const served::request &);

void users_message_from_get(served::response &, const served::request &);
void users_message_from_put(served::response &, const served::request &);
void users_message_from_del(served::response &, const served::request &);
void users_message_from_post(served::response &, const served::request &);

void users_message_broadcast_get(served::response &, const served::request &);
void users_message_broadcast_put(served::response &, const served::request &);
void users_message_broadcast_del(served::response &, const served::request &);
void users_message_broadcast_post(served::response &, const served::request &);


