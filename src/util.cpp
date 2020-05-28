#include <cstdlib>
#include <exception>
#include <fstream>
#include <thread>
#include <served/served.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/tokenizer.hpp>
#include <sstream>
#include "mongo_driver.hpp"
#include "util.hpp"
using namespace std;
bool send_http_cmd(const string target, const string host, const string port)
{
    namespace beast = boost::beast; 
    namespace http = beast::http;  
    namespace net = boost::asio;  
    using tcp = net::ip::tcp;    
    try
    {
        int version = 10;
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);
        auto const results = resolver.resolve(host, port);
        stream.connect(results);
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        http::write(stream, req);
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);
        std::cout << res << std::endl;
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};
    }catch(std::exception const& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}
void sys_backup()
{
// TODO: ... 
}
void sys_restore()
{
// TODO: ... 
}
void sys_update()
{
// TODO: ... 
}
const string get_content_path(const served::request &req, int id)
{
    try{
        string dir = "", ext = "";
        auto req_path = req.url().path();
        BOOST_LOG_TRIVIAL(trace) << "content path:" << req_path;
        if(req_path.find("/storage/contents/poster") != string::npos){
            dir = "Poster/"; ext = ".jpg";
        }else if(req_path.find("/storage/contents/subtitle") != string::npos){
            dir = "Subtitle/"; ext = ".srt";
        }
        if(req_path.find("/storage/contents/poster") != string::npos || 
           req_path.find("/storage/contents/subtitle") != string::npos){
            string path = string(MEDIA_ROOT);
            path += dir;
            if(!boost::filesystem::exists(path)){                   
                boost::filesystem::create_directory(path);          
                BOOST_LOG_TRIVIAL(trace) << "Create " << path;      
            }                                                       
            path += to_string(id);
            string type = req.header("content-type");
            path += ext;
            BOOST_LOG_TRIVIAL(trace) << "path of poster or subtitle:" << path;
            return path;
        }
        json content_info = json::parse(Mongo::find_id("storage_contents_info",id));
        if(content_info["_id"].is_null()){
            BOOST_LOG_TRIVIAL(info) << "Invalid content info by id " << id;
            return "";
        }
        json content_type = json::parse(Mongo::find_id("storage_contents_types",
                    content_info["type"]));
        json content_format = json::parse(Mongo::find_id("storage_contents_formats",
                    content_info["format"]));
        
        if(content_type["_id"].is_null() || content_format["_id"].is_null()){
            BOOST_LOG_TRIVIAL(info) << "Invalid content type or format for id: " << id;
            return "";
        }
        string path = string(MEDIA_ROOT);
        path += content_type["name"];
        path += "/";
        path += to_string(id);
        path += ".";
        path += content_format["name"];
        BOOST_LOG_TRIVIAL(trace) << "Media Path:" << path;
        return path;

    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(error) << e.what();
        return "";
    }
}
bool is_path_equal(string path, string perm)
{
    //BOOST_LOG_TRIVIAL(trace) << path << " ?= " << perm;
    if(perm.find("{id}") == string::npos) return path == perm;
    auto id_pos_perm = perm.rfind('/');
    auto id_pos_path = path.rfind('/');
    if(id_pos_perm == string::npos || id_pos_path == string::npos )
        return false;
    auto path1 = path.substr(0,id_pos_path);
    auto perm1 = perm.substr(0,id_pos_perm);
    return path1 == perm1;
}
bool check_auth(const served::request &req)
{
    auto auth_hdr = req.header("Authorization");
    if(auth_hdr.size() < 10){
        BOOST_LOG_TRIVIAL(trace) << "header Authorization not found!";
        return false;
    } 
    auto auth = auth_hdr.substr(6); // remove 'Base '
    auto text = base64_decode(auth);
    auto pos = text.find(':');
    if(pos == string::npos){
        BOOST_LOG_TRIVIAL(trace) << "Authorization is invalid!";
        return false;
    }
    auto user = text.substr(0,pos);
    auto pass = text.substr(pos+1);
    //if(user == "test" && pass == "test") return true;
    auto res  = Mongo::find_one("system_users",
            "{ \"user\": \"" + user + "\", \"pass\":\"" + pass + "\" }");
    if(res.size() < 1){
        BOOST_LOG_TRIVIAL(trace) << "User not found " << user << ":" << pass;
        return false;
    }
    auto j = json::parse(res);
    if( j.count("_id") == 0 ){
        BOOST_LOG_TRIVIAL(trace) << "Recored is invalid";
        return false;
    }
    // check user expire
    auto now = chrono::system_clock::now().time_since_epoch().count()/1000000000L;
    if(j["expire"] < now){
        BOOST_LOG_TRIVIAL(trace) << "User has been expire!";
        return false;
    }
    // check permissions
    auto path = req.url().path();
    BOOST_LOG_TRIVIAL(trace) << path;
    if(path == "/system/users_me") return true;
    for(auto& p : j["accessList"].items()){
        if(is_path_equal(path,p.key())){
            auto req_method = served::method_to_string(req.method());
            for(auto& m : p.value()){
                if(req_method == m){
                    return true;
                }
            }
        }
    }
    BOOST_LOG_TRIVIAL(trace) << "User not access to " << path;
    return false;
}
void test(served::response &res, const served::request &req)
{
    stringstream s;
    s << "Authorization:" << req.header("Authorization") << "\n";
    s << "User-Agent:" << req.header("User-Agent")  << "\n";
    s << "Content-type: "<< req.header("Content-type")  << "\n";
    s << "Content-Length: "<< req.header("Content-length")  << "\n";
    s << "Param:";
    for(const auto p : req.params) s << p.first << "->" << p.second << " ";
    s << "\nQuery:" << req.query.get("id") << "\n";
    for(const auto q : req.query) s << q.first << "->" << q.second << " ";
    s << "\nSourcs: " << req.source() << "\n";
    s << "Body size:" << req.body().size() << "\n";
    BOOST_LOG_TRIVIAL(trace) << s.str();

}
bool get_id(const served::request &req, string& id)
{
    id = req.params.get("id");
    if(id.size() < 1) return false;
    return true;
}
bool get_id(const served::request &req, int& id)
{
    id = 0;
    auto sid = req.params.get("id");
    if(sid.size() < 1) return false;
    for(auto c : sid)
        if(!isdigit(c)) return false;
    id = stoi(sid);
    return true;
}
int get_id_from_body_and_url(const served::request &req)
{
    int id;
    try{
        if(!get_id(req, id)){
            BOOST_LOG_TRIVIAL(trace) << "Not exists 'id' in url";
            return -1;
        }
        auto j = json::parse(req.body());
        if( j.count("_id") == 0 ){
            BOOST_LOG_TRIVIAL(trace) << "Not exists '_id' in body json";
            return -1;
        }
        int _id = j["_id"];
        if(id != _id){
            BOOST_LOG_TRIVIAL(trace) << "Diffrent '_id' in body and 'id' in url";
            return -1;
        }
        return id;

    }catch(exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        return -1;
    }
}
bool save_file(served::response &res, const served::request &req, const string path)
{
    if(path == ""){
        BOOST_LOG_TRIVIAL(trace) << "Path is empty ";
        return false; 
    }
    BOOST_LOG_TRIVIAL(trace) << "Try to save " << path << " size " << req.body().size();
    ofstream bg(path, ios_base::binary);
    if(bg.is_open()){
        bg.write(req.body().data(), req.body().size());
        bg.close(); 
        res.set_status(200);
        BOOST_LOG_TRIVIAL(trace) << "Saved: " << path;
        auto req_path = req.url().path();
        if(req_path.find("/storage/contents/poster") != string::npos){
            // TODO: convert poster to JPEG by size 512x512 
            thread t([path](){
                    string tmp_file = "/tmp/" + to_string(rand()%1000)+".jpg";
                    string convert = "convert " + path + " -resize 512x512 " + tmp_file;
                    BOOST_LOG_TRIVIAL(trace) << convert;
                    system(convert.c_str());
                    string copy = "mv -f " + tmp_file + " " + path;
                    system(copy.c_str());
                    });
            t.detach();
        } 
        return true;
    }
    return false;
}
bool send_file(served::response &res, const served::request &req, const string path)
{
    BOOST_LOG_TRIVIAL(trace) << "Send " << path;
    ifstream bg(path, ios_base::binary);
    if(bg.is_open()){
        res.set_body(string(
                    (istreambuf_iterator<char>(bg) ),
                    (istreambuf_iterator<char>()    )
                    ));
        res.set_header("Content-type", "image/png");
        //res.set_header("Content-Lenght", to_string(res.body_size()));
        res.set_status(200);
        return true;
    }
    return false;
}
const json parameter_int_value(const string value)
{
    if(value.find(',') == string::npos) return json::parse(value);
    boost::tokenizer<boost::escaped_list_separator<char>>  tok(value);
    json j = json::object();
    j["$in"] = json::array();
    for(const auto it : tok){
        if(it.size()) j["$in"].push_back(stol(it));
    }
    return j;
}
const string  req_parameters(const served::request &req)
{
    try{
        auto sid = req.query.get("start-id");
        auto eid = req.query.get("end-id");
        auto stime = req.query.get("start-time");
        auto etime = req.query.get("end-time");
        auto type = req.query.get("type");
        auto user = req.query.get("user");
        auto active = req.query.get("active");
        auto category = req.query.get("category");
        auto activityType = req.query.get("activityType");
        auto content = req.query.get("content");
        json j = json::object();
        if(stime.size() && etime.size()){
            j["time"] = json::object();
            j["time"]["$gt"] = stol(stime);
            j["time"]["$lt"] = stol(etime);
        }
        if(stime.size() && etime.size()){
            j["_id"] = json::object();
            j["_id"]["$gt"] = stol(stime);
            j["_id"]["$lt"] = stol(etime);
        }
        if(type.size()) j["type"] = parameter_int_value(type);
        if(user.size()) j["user"] = parameter_int_value(user);
        if(content.size()) j["content"] = parameter_int_value(content);
        if(category.size()) j["category"] = parameter_int_value(category);
        if(active.size()) j["active"] = active.compare("true");
        if(activityType.size()) j["activityType"] = parameter_int_value(activityType);
        BOOST_LOG_TRIVIAL(trace) << j.dump(4);
        return j.dump();
    }catch(exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        return "{}";
    }
}
pair<int,int> req_range(const served::request &req)
{
    int s = 1;
    int e = QUERY_SIZE;

    string from = req.query.get("from");
    if(from.size()>0){
        s = stoi(from);
    }
    string to = req.query.get("to");
    if(to.size()>0){
        e = stoi(to);
    }else{
        e = s + QUERY_SIZE;
    }
    return make_pair(s, e);
}
/*
string b64decode(const char* data, const size_t len)
{
    unsigned char* p = (unsigned char*)data;
    int pad = len > 0 && (len % 4 || p[len - 1] == '=');
    const size_t L = ((len + 3) / 4 - pad) * 4;
    string str(L / 4 * 3 + pad, '\0');
    static const int B64index[256] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
        7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
        0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };


    for (size_t i = 0, j = 0; i < L; i += 4)
    {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;
    }
    if (pad)
    {
        int n = B64index[p[L]] << 18 | B64index[p[L + 1]] << 12;
        str[str.size() - 1] = n >> 16;

        if (len > L + 2 && p[L + 2] != '=')
        {
            n |= B64index[p[L + 2]] << 6;
            str.push_back(n >> 8 & 0xFF);
        }
    }
    return str;
}
*/
static const string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_decode(string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
