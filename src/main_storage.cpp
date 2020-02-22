#include <iostream>
#include <fstream>
#include <mutex>

#include "main_storage.hpp"
using namespace std;

MainStorage::MainStorage()
{
    ifstream  conf("conf/configs.json");
    if(conf.is_open()){
        conf >> configs;
        BOOST_LOG_TRIVIAL(trace) << "Load configs.json with size:" << configs.size();
    }else{
        throw std::runtime_error("file 'configs.json' not found");
    }
    ifstream  chan("conf/channels.json");
    if(chan.is_open()){
        chan >> channels;
        BOOST_LOG_TRIVIAL(trace) << "Load channels.json with size:" << channels.size();
    }else{
        throw std::runtime_error("file 'channels.json' not found");
    }
    ifstream  user("conf/users.json");
    if(user.is_open()){
        user >> users;
        BOOST_LOG_TRIVIAL(trace) << "Load users.json with size:" << users.size();
    }else{
        throw std::runtime_error("file 'users.json' not found");
    }
    ifstream  vod("conf/vod_users.json");
    if(vod.is_open()){
        vod >> vod_users;
        BOOST_LOG_TRIVIAL(trace) << "Load vod_users.json with size:" << vod_users.size();
    }else{
        throw std::runtime_error("file 'vod_users.json' not found");
    }

}
MainStorage::~MainStorage()
{
    ofstream  conf("conf/configs.json");
    if(conf.is_open()){
        conf << configs.dump(4);
        BOOST_LOG_TRIVIAL(trace) << "Save configs.json with size:" << configs.size();
    }
    ofstream  chan("conf/channels.json");
    if(chan.is_open()){
        chan << channels.dump(4);
        BOOST_LOG_TRIVIAL(trace) << "Save channels.json with size:" << channels.size();
    }else{
        BOOST_LOG_TRIVIAL(trace) << "file 'channels.json' not found";
    }
    ofstream  user("conf/users.json");
    if(user.is_open()){
        user << users.dump(4);
        BOOST_LOG_TRIVIAL(trace) << "Save users.json with size:" << users.size();
    }else{
        BOOST_LOG_TRIVIAL(trace) << "file 'users.json' not found";
    }
    ofstream  vod("conf/vod_users.json");
    if(vod.is_open()){
        vod << vod_users.dump(4);
        BOOST_LOG_TRIVIAL(trace) << "Save vod_users.json with size:" << vod_users.size();
    }else{
        BOOST_LOG_TRIVIAL(trace) <<"file 'vod_users.json' not found";
    }
        BOOST_LOG_TRIVIAL(info) << "END MainStorage";
}

nlohmann::json MainStorage::getJson(
        std::string fileName,
        std::string section = "")
{
        if(fileName == "configs")
            return (section == "") ? configs : configs[section] ;
        else if(fileName == "channels")
            return (section == "") ? channels : channels[section] ;
        else if(fileName == "users")
            return (section == "") ? users : users[section] ;
        else if(fileName == "vod_users")
            return (section == "") ? vod_users : vod_users[section] ;

        return nlohmann::json();
}
void MainStorage::setJson(
        std::string fileName,
        std::string section,
        nlohmann::json js)
{
        std::unique_lock<std::mutex> lock(write_mutex);

        if(fileName == "configs"){
            if(section == "") configs = js; else configs[section] = js;
        }else if(fileName == "channels"){
            if(section == "") channels = js; else channels[section] = js;
        }else if(fileName == "users"){
            if(section == "") users = js; else users[section] = js;
        }else if(fileName == "vod_users"){
            if(section == "") vod_users = js; else vod_users[section] = js;
        }
}
