#include "auth.hpp"
#include "system.hpp"

extern MainStorage st;
void system_location(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_location";
	CHECK_AUTH;
}
void system_system_logo(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_system_logo";
	CHECK_AUTH;
}
void system_subtitle_logo(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_subtitle_logo";
	CHECK_AUTH;
}
void system_network(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_network";
	CHECK_AUTH;
}
void system_users(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_users";
	CHECK_AUTH;
}
void system_users_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_users_id";
	CHECK_AUTH;
}
void system_pms(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_pms";
	CHECK_AUTH;
}
void system_vod_account(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_vod_account";
	CHECK_AUTH;
}
void system_vod_account_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_vod_account_id";
	CHECK_AUTH;
}
void system_permission(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_permission";
	CHECK_AUTH;
}
void system_permission_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_permission_id";
	CHECK_AUTH;
}
void system_weektime(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_weektime";
	CHECK_AUTH;
}
void system_weektime_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_weektime_id";
	CHECK_AUTH;
}
void system_backup(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_backup";
	CHECK_AUTH;
}
void system_license(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_license";
	CHECK_AUTH;
}
void system_firmware(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_firmware";
	CHECK_AUTH;
}
void system_restart(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_restart";
	CHECK_AUTH;
}
void system_stop(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_stop";
	CHECK_AUTH;
}
void system_reboot(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_reboot";
	CHECK_AUTH;
}
void system_logout(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start system_logout";
	CHECK_AUTH;
}
