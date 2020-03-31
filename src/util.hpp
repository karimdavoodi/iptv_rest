#pragma onc;
#include <iostream>
#include <nlohmann/json.hpp>
#include <served/served.hpp>
#include <boost/log/trivial.hpp>
#define  QUERY_SIZE 10
using json = nlohmann::json;

bool get_id(const served::request &req, std::string& id);
bool get_id(const served::request &req, int& id);
int get_id_from_body_and_url(const served::request &req);
bool save_file(served::response &res, const served::request &req, const std::string path);
bool send_file(served::response &res, const served::request &req, const std::string path);
std::pair<int,int> req_range(const served::request &req);

