#include <exception>
#include <fstream>
#include <served/served.hpp>
#include <boost/log/trivial.hpp>

#include "util.hpp"

bool get_id(const served::request &req, std::string& id)
{
    id = req.params.get("id");
    if(id.size() < 1) return false;
    return true;
}
bool get_id(const served::request &req, int& id)
{
    auto sid = req.params.get("id");
    if(sid.size() < 1) return false;
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
        res.set_header("Content-Lenght", std::to_string(res.body_size()));
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

