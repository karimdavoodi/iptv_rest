#include "auth.hpp"
#include "launcher.hpp"

extern MainStorage st;
void launcher_default(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_default";
	CHECK_AUTH;
}
void launcher_background(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_background";
	CHECK_AUTH;
}
void launcher_logo(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_logo";
	CHECK_AUTH;
}
void launcher_make(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_make";
	CHECK_AUTH;
}
void launcher_make_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_make_id";
	CHECK_AUTH;
}
void launcher_arrange(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_arrange";
	CHECK_AUTH;
}
void launcher_arrange_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_arrange_id";
	CHECK_AUTH;
}
