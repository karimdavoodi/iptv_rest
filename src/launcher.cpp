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
    GET_COL("launcher_components_info");
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
    GET_COL("launcher_components_types");
}
void launcher_components_fonts_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("launcher_components_fonts");
}
void launcher_menu_get(served::response &res, const served::request &req)
{
    CHECK_AUTH;
    GET_COL("launcher_menu");
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
    GET_COL("launcher_setting");
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
    try{
        // Remove all 'menu' and 'components' that this launcher used
        int64_t id;                                             
        if(!Util::get_id(req, id) ){                            
            ERRORSEND(res, 400, 1006, "Id not exists in url!");
        }                                                     
        auto launcher = json::parse(Mongo::find_id("launcher_setting", id));
        if(launcher["_id"].is_number()){
            for(const auto menu_id : launcher["menu"]){
                auto menu = json::parse(Mongo::find_id("launcher_menu", menu_id));
                if(menu["_id"].is_number()){
                    for(const auto component_id : menu["components"]){
                        Mongo::remove_id("launcher_components_info", component_id);
                    }
                    Mongo::remove_id("launcher_menu", menu_id);
                }
            }
        }
    }catch(std::exception& e){
        LOG(error) << e.what();
    }

    DEL_ID_COL("launcher_setting");
}
