#pragma once
#include <iostream>
#include <served/served.hpp>
#include <boost/log/trivial.hpp>
#include "../third_party/json.hpp"
#define  MEDIA_ROOT "/opt/sms/www/iptv/media/"
using json = nlohmann::json;
namespace Util {
    void system(const std::string cmd);
    const std::string get_file_content(const std::string name);
    void report_error(const std::string, int level = 1);
    void report_webui_user(int userId, const served::request &req);
    void fill_input_tuners_in_db();
    void fill_output_tuners_in_db();
    std::string send_http_cmd(const std::string target, 
            const std::string host = "127.0.0.1" , 
            const std::string port = "10012",
            const std::string method = "get");
    const std::string req_parameters(const served::request &req);
    const std::string get_content_path(const served::request &req, int id);
    const json check_media_exists(const served::request &req, int id);
    bool check_auth(const served::request &req);
    void test(served::response &res, const served::request &req);
    bool get_id(const served::request &req, std::string& id);
    bool get_id(const served::request &req, int& id);
    int get_id_from_body_and_url(const served::request &req);
    bool save_file(served::response &res, const served::request &req, const std::string path);
    bool send_file(served::response &res, const served::request &req, const std::string path);
    std::pair<int,int> req_range(const served::request &req);
    //std::string b64decode(const char* data, const size_t len);
    std::string base64_decode(std::string const& encoded_string);
    void sys_backup(const std::string fname);
    void sys_restore(const std::string fname);
    void sys_update();
    void sys_restart();
    void sys_stop();
    void sys_reboot();
}
