#include <algorithm>
#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <utility>
#include <boost/filesystem.hpp>
#include "auth.hpp"
#include "launcher.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"

void launcher_default_get(served::response &res, const served::request &req)
{
    
    CHECK_AUTH;
    GET_ID1_COL("launcher_default");
}
void launcher_default_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    POST_ID1_COL("launcher_default");
}
void launcher_background_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    SEND_ID_FILE(ICON_PATH ,"background", PNG);
}
void launcher_background_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    RECV_ID_FILE(ICON_PATH ,"background", PNG);
}
void launcher_background_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    RECV_ID_FILE(ICON_PATH ,"background", PNG);
}
void launcher_background_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_FILE(ICON_PATH ,"background", PNG);
}

void launcher_logo_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    SEND_ID_LANG_FILE(ICON_PATH, "logo", PNG);
}
void launcher_logo_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    RECV_ID_LANG_FILE(ICON_PATH, "logo", PNG);
}
void launcher_logo_put(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    RECV_ID_LANG_FILE(ICON_PATH, "logo", PNG);
}
void launcher_logo_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_LANG_FILE(ICON_PATH, "logo", PNG);
}
void launcher_components_types_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_ID_COL("components_types");
}
void launcher_components_logo_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    SEND_ID_LANG_FILE(ICON_PATH, "component_logo", PNG);
}
void launcher_components_logo_post(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    RECV_ID_LANG_FILE(ICON_PATH, "component_logo", PNG);
}
void launcher_components_logo_put(served::response &res, const served::request &req)
{
    launcher_components_logo_post(res, req);
}
void launcher_components_logo_del(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    DEL_ID_LANG_FILE(ICON_PATH, "component_logo", PNG);
}
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
