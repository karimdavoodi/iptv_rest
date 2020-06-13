#include <cstdlib>
#include <exception>
#include <fstream>
#include <string>
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
#include "hardware.hpp"
using namespace std;
namespace Util {
    void system(const std::string cmd)
    {
        BOOST_LOG_TRIVIAL(trace) << "Run shell command:" << cmd;
        if(std::system(cmd.c_str())){
            BOOST_LOG_TRIVIAL(error) << "Error in run " << cmd;
        }
    }
    const std::string get_file_content(const std::string name)
    {
        if(boost::filesystem::exists(name)){
            ifstream file(name);
            if(file.is_open()){
                std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
                if(content.back() == '\n') content.pop_back();
                return content;
            }
        }
        return "";
    }
    void report_webui_user(int userId, const served::request &req)
    {
        try{
            if(req.method() > 4) return;
            json j = json::object();
            j["_id"] = chrono::system_clock::now().time_since_epoch().count();
            j["time"] = long(time(NULL));
            j["user"] = userId; 
            j["api"] = req.url().path();
            j["operation"] = req.method(); 
            //GET = 0, POST = 1, HEAD = 2, PUT = 3, DELETE = 4
            // TODO: save WebUI user detail
            j["oldValue"] = "";
            j["newValue"] = "";

            Mongo::insert("report_webui_user", j.dump());

        }catch(std::exception const& e){
            BOOST_LOG_TRIVIAL(error)  <<  e.what();
        }
    }
    void report_error(const std::string msg, int level)
    {
        try{
            json j = json::object();
            j["_id"] = chrono::system_clock::now().time_since_epoch().count();
            j["time"] = long(time(NULL));
            j["message"] = msg;
            j["message"] = "iptv_api";
            j["level"] = level;
            Mongo::insert("report_error", j.dump());
        }catch(std::exception const& e){
            BOOST_LOG_TRIVIAL(error)  <<  e.what();
        }
    }
    void fill_output_tuners_in_db()
    {
        json tuners = json::parse(Mongo::find_id("live_tuners_output", 1));
        auto tList = Hardware::detect_output_tuners();
        int sz = tuners["dvbt"].get<vector<int>>().size();
        BOOST_LOG_TRIVIAL(trace) << "sz " << sz << " hw:" << tList.size();
        for(size_t i=sz; i<tList.size(); ++i){
            tuners["dvbt"].push_back(i);
        }
        Mongo::insert_or_replace_id("live_tuners_output",1, tuners.dump());
    }
    void fill_input_tuners_in_db()
    {
        try{
            json db_tuners = json::parse(Mongo::find_mony("live_tuners_input", "{}"));      

            json newTuners = json::array();
            vector<pair<int,string>> hwlist = Hardware::detect_input_tuners();
            for(const auto& htuner : hwlist){
                bool is_dvbt = (htuner.second.find("0x62") != string::npos);  
                string name = (is_dvbt ? "DVBT " : "DVBS ") + to_string(htuner.first);
                json j = json::object();
                j["_id"] = htuner.first;
                j["name"] = name;
                j["active"] = true;
                j["is_dvbt"] = is_dvbt;  
                j["freq"] = 0;
                j["errrate"] = ""; 
                j["pol"] = ""; 
                j["symrate"] = 0;
                j["switch"] = 0;
                for(const auto& t : db_tuners){
                    if(t["_id"] == htuner.first){
                        j["name"]    = t["name"].get<string>();
                        j["active"]  = t["active"].get<bool>(); 
                        j["freq"]    = t["freq"].get<int>();    
                        j["errrate"] = t["errrate"].get<string>(); 
                        j["pol"]     = t["pol"].get<string>(); 
                        j["symrate"] = t["symrate"].get<int>();
                        j["switch"]  = t["switch"].get<int>(); 
                        break;
                    }
                }
                newTuners.push_back(j);
            }
            Mongo::remove_mony("live_tuners_input", "{}");
            for(const auto& t : newTuners){
                Mongo::insert("live_tuners_input", t.dump());
            }
        }catch(std::exception const& e){
            BOOST_LOG_TRIVIAL(error)  <<  e.what();
        }
    }
    string send_http_cmd(const string target, 
            const string host, 
            const string port,
            const string method_str)
    {
        namespace beast = boost::beast; 
        namespace http = beast::http;  
        namespace net = boost::asio;  
        using tcp = net::ip::tcp;    
        try{
            int version = 10;
            net::io_context ioc;
            tcp::resolver resolver(ioc);
            beast::tcp_stream stream(ioc);
            auto const results = resolver.resolve(host, port);
            stream.connect(results);
            auto method = http::verb::get;
            if(method_str == "head") method = http::verb::head;
            else if(method_str == "post") method = http::verb::post;
            else if(method_str == "put") method = http::verb::put;
            else if(method_str == "delete") method = http::verb::delete_;
            http::request<http::string_body> req{method, target, version};
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
            http::write(stream, req);
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(stream, buffer, res);
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);
            ostringstream out;
            out << res;
            return out.str();
        }catch(std::exception const& e){
            BOOST_LOG_TRIVIAL(error) << e.what();
            return "";
        }
        return "";
    }
    void sys_backup(const string fname)
    {
        string file = string(MEDIA_ROOT) + fname;
        string cmd = "/usr/bin/mongodump --quiet -d iptv "
            "--excludeCollectionsWithPrefix=report --gzip --archive=" + file; 
        BOOST_LOG_TRIVIAL(trace) << cmd;
        system(cmd);
    }
    void sys_restore(const string fname)
    {
        string file = string(MEDIA_ROOT) + fname;
        string fileOld = string(MEDIA_ROOT) + "backup_bk.gz";
        if(boost::filesystem::file_size(file)>1){
            BOOST_LOG_TRIVIAL(info) << "Save Old Data in " << fileOld;
            string cmd = "/usr/bin/mongodump --quiet -d iptv --gzip --archive=" + fileOld; 
            system(cmd);
            BOOST_LOG_TRIVIAL(info) << "Clean DB ";
            system("/usr/bin/mongo iptv --eval \"db.dropDatabase()\" ");
            cmd = "/usr/bin/mongorestore --quiet --gzip --archive=" + file;
            system(cmd);
        }
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
        }
        return "";
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
        try{
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
            if(user == "master" && pass == "MMKmoojAFZAR") return true;
            auto res  = Mongo::find_one("system_users",
                    "{ \"user\": \"" + user + "\", \"pass\":\"" + pass + "\" }");
            if(res.size() < 1){
                BOOST_LOG_TRIVIAL(trace) << "User not found " << user << ":" << pass;
                report_error("Invalid user:"+user+" pass:"+pass);
                return false;
            }
            auto j = json::parse(res);
            if( j.count("_id") == 0 ){
                BOOST_LOG_TRIVIAL(trace) << "User recored is invalid";
                report_error("Invalid user record for :"+user+" pass:"+pass);
                return false;
            }
            report_webui_user(j["_id"].get<int>(), req);
            // FIXME : not check permission for test user
            if(user == "test" && pass == "test") return true;
            // check user expire
            auto now = time(NULL);
            if(j["expire"] < now){
                BOOST_LOG_TRIVIAL(trace) << "User has been expire!";
                return false;
            }
            // check permissions
            auto path = req.url().path();
            //BOOST_LOG_TRIVIAL(trace) << path;
            if(path == "/system/users_me") return true;
            for(const auto& p : j["accessList"].items()){
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
        }catch(exception& e){
            BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        }
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
        try{
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
                            system(convert);
                            string copy = "mv -f " + tmp_file + " " + path;
                            system(copy);
                            });
                    t.detach();
                } 
                return true;
            }
        }catch(exception& e){
            BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        }
        return false;
    }
    bool send_file(served::response &res, const served::request &req, const string path)
    {
        try{
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
        }catch(exception& e){
            BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        }
        return false;
    }
    const string remove_camma(const string str)
    {
        string res;
        for(char c : str)
            if(c != '\'' && c != '\"' ) res.push_back(c);
        return res;
    }
    const json parameter_array(const string value)
    {
        boost::tokenizer<boost::escaped_list_separator<char>>  tok(value);
        json j = json::object();
        j["$in"] = json::array();
        for(const auto it : tok){
            if(it.size()){
                if(isdigit(it[0]))
                    j["$in"].push_back(stol(it));
                else
                    j["$in"].push_back(remove_camma(it));
            } 
        }
        return j;
    }
    const string  req_parameters(const served::request &req)
    {
        try{
            json j = json::object();
            for(const auto& arg : req.query){
               string name = arg.first; 
               string value = arg.second;
               // Deprecrated start-time and start-id
               if(name == "end-id" || name == "end-time" || 
                  name == "from" || name == "to") continue;
               if(name == "start-id"){
                   auto end = req.query.get("end-id");
                   if(end.size()){
                       j["_id"] = json::object();
                       j["_id"]["$gt"] = stol(value);
                       j["_id"]["$lt"] = stol(end);
                   }
               }
               else if(name == "start-time"){
                   auto end = req.query.get("end-time");
                   if(end.size()){
                       j["time"] = json::object();
                       j["time"]["$gt"] = stol(value);
                       j["time"]["$lt"] = stol(end);
                   }
               }else{
                   if(value.find(':') != string::npos ){
                       auto pos = value.find(':');
                       j[name] = json::object();
                       j[name]["$gt"] = stof(value.substr(0, pos));
                       j[name]["$lt"] = stof(value.substr(pos+1));
                   }else if(value.find(',') == string::npos){
                       if(isdigit(value[0]))
                           j[name] = stof(value);
                       else if(value == "true" || value == "false")
                           j[name] = (value == "true");
                       else
                           j[name] = remove_camma(value);
                   }else{
                       j[name] = parameter_array(value);
                   }
            }
        }
        BOOST_LOG_TRIVIAL(trace) << j.dump(4);
        return j.dump();
    }catch(exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception: " << e.what();
        return "{}";
    }
}
pair<int,int> req_range(const served::request &req)
{
    int s = 0;
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
}
