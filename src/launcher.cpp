#include <algorithm>
#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <utility>
#include <boost/filesystem.hpp>
#include "auth.hpp"
#include "launcher.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"

void launcher_components_info_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("launcher_components_info");
}
void launcher_components_info_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("launcher_components_info");
}
void launcher_components_info_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("launcher_components_info");
}
void launcher_components_info_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("launcher_components_info");
}
void launcher_components_types_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("launcher_components_types");
}
void launcher_components_types_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("launcher_components_types");
}
void launcher_components_types_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("launcher_components_types");
}
void launcher_components_types_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("launcher_components_types");
}
void launcher_menu_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("launcher_menu");
}
void launcher_menu_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("launcher_menu");
}
void launcher_menu_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("launcher_menu");
}
void launcher_menu_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("launcher_menu");
}
void launcher_setting_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("launcher_setting");
}
void launcher_setting_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    PUT_ID_COL("launcher_setting");
}
void launcher_setting_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID_COL("launcher_setting");
}
void launcher_setting_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_COL("launcher_setting");
}
