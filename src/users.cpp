#include "auth.hpp"
#include "users.hpp"

extern MainStorage st;
void users_group(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_group";
	CHECK_AUTH;
}
void users_group_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_group_id";
	CHECK_AUTH;
}
void users_user(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_user";
	CHECK_AUTH;
}
void users_user_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_user_id";
	CHECK_AUTH;
}
void users_message_to_userid(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_message_to_userid";
	CHECK_AUTH;
}
void users_message_to_userid_msg_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_message_to_userid_msg_id";
	CHECK_AUTH;
}
void users_message_from_userid(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_message_from_userid";
	CHECK_AUTH;
}
void users_message_broadcast(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_message_broadcast";
	CHECK_AUTH;
}
void users_message_broadcast_msg_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start users_message_broadcast_msg_id";
	CHECK_AUTH;
}
