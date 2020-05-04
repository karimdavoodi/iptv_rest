#include <exception>
#include <fstream>
#include <served/served.hpp>
#include <boost/log/trivial.hpp>
#include <sstream>
#include "mongo_driver.hpp"
#include "util.hpp"

void sys_restart()
{
// TODO: ... 

}
void sys_stop()
{
// TODO: ... 

}
void sys_reboot()
{
// TODO: ... 

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
std::string get_content_path(const served::request &req, int id)
{
    json content_info = json::parse(Mongo::find_id("storage_contents_info",id));
    if(content_info["type"].is_null()){
        BOOST_LOG_TRIVIAL(info) << "Invalid content info by id " << id;
        return "";
    }
    json content_type = json::parse(Mongo::find_id("storage_contents_types",
                content_info["type"]));
    json content_format = json::parse(Mongo::find_id("storage_contents_formats",
                content_info["format"]));
    
    auto req_path = req.url().path();
    std::string perfix = "";
    if(req_path.find("/storage/poster") != std::string::npos){
        perfix = "poster_";
    }else if(req_path.find("/storage/subtitle") != std::string::npos){
        perfix = "subtitle_";
    }
    std::string path = std::string(MEDIA_ROOT);
    path += content_type["name"];
    path += "/";
    path += perfix;
    path += std::to_string(id);
    path += ".";
    path += content_format["name"];
    BOOST_LOG_TRIVIAL(trace) << "Media Path:" << path;
    return path;
}
bool is_path_equal(std::string path, std::string perm)
{
    if(perm.find("{id}") == std::string::npos) return path == perm;
    auto id_pos_perm = perm.rfind('/');
    auto id_pos_path = path.rfind('/');
    if(id_pos_perm == std::string::npos || id_pos_path == std::string::npos )
        return false;
    auto path1 = path.substr(0,id_pos_path);
    auto perm1 = perm.substr(0,id_pos_perm);
    return path1 == perm1;
}
bool check_auth(const served::request &req)
{
    auto auth = req.header("Authorization").substr(6); // remove "Base "
    auto text = base64_decode(auth);
    auto pos = text.find(':');
    if(pos == std::string::npos) return false;
    auto user = text.substr(0,pos);
    auto pass = text.substr(pos+1);
    //if(user == "test" && pass == "test") return true;
    auto res  = Mongo::find("system_users",
            "{ \"user\": \"" + user + "\", \"pass\":\"" + pass + "\" }");
    if(res.size() < 1) return false;
    auto j = json::parse(res);
    if( j.count("_id") == 0 ) return false;
    // check user expire
    auto now = std::chrono::system_clock::now().time_since_epoch().count()/1000000000L;
    if(j["end"] < now) return false;
    // check permissions
    auto path = req.url().path();
    if(path == "system/user_me") return true;
    for(auto& p : j["permission"].items()){
        if(is_path_equal(path,p.key())){
            auto req_method = served::method_to_string(req.method());
            for(auto& m : p.value()){
                if(req_method == m){
                    return true;
                }
            }
        }
    }
    return false;
}
void test(served::response &res, const served::request &req)
{
    std::stringstream s;
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
bool get_id(const served::request &req, std::string& id)
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
    id = std::stoi(sid);
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

    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        return -1;
    }
}
bool save_file(served::response &res, const served::request &req, const std::string path)
{
    BOOST_LOG_TRIVIAL(trace) << "Save " << path;
    std::ofstream bg(path, std::ios_base::binary);
    if(bg.is_open()){
        bg.write(req.body().c_str(), req.body().size());
        bg.close(); 
        res.set_status(200);
        BOOST_LOG_TRIVIAL(trace) << "Saved: " << path;
        return true;
    }
    return false;
}
bool send_file(served::response &res, const served::request &req, const std::string path)
{
    BOOST_LOG_TRIVIAL(trace) << "Send " << path;
    std::ifstream bg(path, std::ios_base::binary);
    if(bg.is_open()){
        res.set_body(std::string(
                    (std::istreambuf_iterator<char>(bg) ),
                    (std::istreambuf_iterator<char>()    )
                    ));
        res.set_header("Content-type", "image/png");
        //res.set_header("Content-Lenght", std::to_string(res.body_size()));
        res.set_status(200);
        return true;
    }
    return false;
}
std::pair<int,int> req_range(const served::request &req)
{
    int s = 1;
    int e = QUERY_SIZE;

    std::string from = req.query.get("from");
    if(from.size()>0){
        s = std::stoi(from);
    }
    std::string to = req.query.get("to");
    if(to.size()>0){
        e = std::stoi(to);
    }else{
        e = s + QUERY_SIZE;
    }
    return std::make_pair(s, e);
}
/*
std::string b64decode(const char* data, const size_t len)
{
    unsigned char* p = (unsigned char*)data;
    int pad = len > 0 && (len % 4 || p[len - 1] == '=');
    const size_t L = ((len + 3) / 4 - pad) * 4;
    std::string str(L / 4 * 3 + pad, '\0');
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
static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

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
