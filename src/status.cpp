#include "auth.hpp"
#include "status.hpp"

extern MainStorage st;
void status_information(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_information";
	CHECK_AUTH;
}
void status_cpu_mem(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_cpu_mem";
	CHECK_AUTH;
}
void status_network(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_network";
	CHECK_AUTH;
}
void status_storage(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_storage";
	CHECK_AUTH;
}
void status_dvb(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_dvb";
	CHECK_AUTH;
}
void status_channels_input(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_channels_input";
	CHECK_AUTH;
}
void status_channels_output(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_channels_output";
	CHECK_AUTH;
}
void status_channels_output_view(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_channels_output_view";
	CHECK_AUTH;
}
void status_users(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_users";
	CHECK_AUTH;
}
void status_errors(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start status_errors";
	CHECK_AUTH;
}
