#include "auth.hpp"
#include "report.hpp"

extern MainStorage st;
void report_user(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start report_user";
	CHECK_AUTH;
}
void report_system(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start report_system";
	CHECK_AUTH;
}
void report_live(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start report_live";
	CHECK_AUTH;
}
void report_vod(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start report_vod";
	CHECK_AUTH;
}
void report_component(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start report_component";
	CHECK_AUTH;
}
void report_system_user(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start report_system_user";
	CHECK_AUTH;
}
