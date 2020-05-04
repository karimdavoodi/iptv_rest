#pragma onc;
#include <iostream>
#include <served/served.hpp>
#include <boost/log/trivial.hpp>
#include "../third_party/json.hpp"
#define  QUERY_SIZE 10
#define  MEDIA_ROOT "/opt/sms/www/iptv/media/"
using json = nlohmann::json;

std::string get_content_path(const served::request &req, int id);
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
void sys_backup();
void sys_restore();
void sys_update();
void sys_restart();
void sys_stop();
void sys_reboot();
