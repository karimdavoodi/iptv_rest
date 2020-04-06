#include <utility>
#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "users.hpp"

void users_group_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("users_group");
}
void users_group_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("users_group");
}
void users_group_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("users_group");
}
void users_group_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("users_group");
}

void users_user_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("users_user");
}
void users_user_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("users_user");
}
void users_user_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("users_user");
}
void users_user_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("users_user");
}

void users_message_to_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("users_message_to");
}
void users_message_to_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("users_message_to");
}
void users_message_to_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("users_message_to");
}
void users_message_to_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("users_message_to");
}

void users_message_from_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("users_message_from");
}
void users_message_from_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("users_message_from");
}
void users_message_from_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("users_message_from");
}
void users_message_from_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("users_message_from");
}

void users_message_broadcast_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("users_message_broadcast");
}
void users_message_broadcast_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("users_message_broadcast");
}
void users_message_broadcast_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("users_message_broadcast");
}
void users_message_broadcast_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("users_message_broadcast");
}


