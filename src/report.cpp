#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "report.hpp"

void report_user_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_user");
}
void report_system_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_system");
}
void report_live_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_live");
}
void report_vod_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_vod");
}
void report_component_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_component");
}
void report_system_user_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_system_user");
}
