#include "hardware.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include <fstream>
#include <time.h>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace Hardware {
    const std::vector<int> detect_output_tuners()
    {
        std::vector<int> list;
        try{
            for(int i=0; i<4; ++i){
                if(boost::filesystem::exists("/dev/tbsmod"+to_string(i))){
                    for(int j=0; j<5; ++j){
                        auto dev = "/dev/tbsmod" + to_string(i) + "/mod" + to_string(j);
                        if(boost::filesystem::exists(dev)){
                            list.push_back(j);
                        }
                    }
                }
            }
            // FIXME: conflict tuners index
            for(size_t i=0; i<32; ++i){
                auto dev = "/dev/usb-it950x"+to_string(i); 
                if(boost::filesystem::exists(dev)){
                    list.push_back(i);
                }
            }
        }catch(std::exception& e){
            BOOST_LOG_TRIVIAL(error) << e.what();
        }
        return list;
    }
    const vector<pair<int,string>> detect_input_tuners()
    {
        vector<pair<int,string>> list;
        try{
            if(boost::filesystem::exists("/dev/dvb")){
                for(size_t i=0; i<32; ++i){
                    ostringstream path;
                    path << "/sys/class/dvb/dvb"<< i <<".frontend0/device";
                    if(!boost::filesystem::exists(path.str())) continue;
                    string vendor_file = path.str() + "/subsystem_vendor";
                    string device_file = path.str() + "/subsystem_device";
                    string vendor_id = Util::get_file_content(vendor_file);
                    string device_id = Util::get_file_content(device_file);
                    string name = vendor_id + ":" + device_id;
                    list.push_back(make_pair(i,name));
                }
            }
        }catch(std::exception& e){
            BOOST_LOG_TRIVIAL(error) << e.what();
        }
        return list;
    }
    const std::string detect_network()
    {
        return "";
    }
    const std::string scan_input_tuner(const std::string& tuner_json)
    {
        ostringstream cmd;
        json res = json::object();
        res["content"] = json::array();
        try{
            json tuner = json::parse(tuner_json);
            if(tuner["_id"].is_null()){
                BOOST_LOG_TRIVIAL(error) << "Tuner is invalid:" << tuner_json;
                return res.dump();
            }
            if(!boost::filesystem::exists("/dev/dvb/adapter"+
                        to_string(tuner["_id"])+"/frontend0")){
                BOOST_LOG_TRIVIAL(error) << "Tuner Not Exists:" << tuner["_id"];
                return res.dump();
            }
            auto cfg_file = "/tmp/scan_freq_"+to_string(tuner["_id"]);
            auto out_file = "/tmp/scan_chans_"+to_string(tuner["_id"]);
            ofstream freq(cfg_file);
            if(!freq.is_open()){
                BOOST_LOG_TRIVIAL(error) << "Can't open scan config file";
                return res.dump();
            }
            if(tuner["is_dvbt"] == true){
                freq << "T " << tuner["freq"].get<int>() 
                     << "000 8MHz 2/3 NONE QAM64 8k 1/8 NONE";
            }else{
                freq << "S "<< tuner["freq"].get<int>()<<"000 "
                     << tuner["pol"].get<string>()
                     <<" "<< tuner["symrate"].get<int>()
                     << "000 " << tuner["errrate"].get<string>();
            }
            freq.close();
            cmd << "/usr/bin/scan -o vdr -a " 
                << tuner["_id"].get<int>() << " -s " 
                << tuner["switch"].get<int>() 
                << " " << cfg_file << " > " << out_file;
            BOOST_LOG_TRIVIAL(info) << "Scan cmd:" << cmd.str();
            std::system(cmd.str().c_str());
            ifstream vdr_file(out_file);
            if(!vdr_file.is_open()){
                BOOST_LOG_TRIVIAL(error) << "Can't open scan vdr file";
                return res.dump();
            }
            string line;
            while( vdr_file >> line ){
                int colons = std::count_if(line.begin(), line.end(), 
                        [](char c){ return c == ':'; });
                if(colons < 8) continue;
                json chan = json::object();
                boost::tokenizer<boost::char_separator<char>> 
                    tok(line, boost::char_separator(":"));
                auto it = tok.begin();
                auto pos = it->find(';');
                if(it->at(0) == '[') continue;
                chan["dvb_id"] = tuner["_id"];
                chan["name"] = (pos == string::npos) ? *it : it->substr(0,pos); 
                chan["freq"] = *(++it); // 1
                ++it; ++it; 
                chan["symb"] = *(++it);  // 4
                ++it; ++it; ++it; ++it; 
                chan["scramble"]  = (it->at(0) == '0') ? false : true;
                chan["sid"]  = *(++it); //9
                chan["vid"]  = 0; //?
                chan["aid"]  = 0; //?
                chan["pol"]  = *(++it); //10
                res["content"].push_back(chan);
            }
        }catch(std::exception& e){
            BOOST_LOG_TRIVIAL(error) << "Exception:" << e.what();
        }
        res["total"] = res["content"].size();
        return res.dump();
    }
    const std::string detect_cpu_model()
    {
        string line;
        BOOST_LOG_TRIVIAL(trace) << __func__;
        ifstream disk("/proc/cpuinfo");
        // model name	: Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz
        while(disk.good()){
            getline(disk, line);
            if(line.find("model name") != string::npos){
                return line.substr(line.find(':')+1);
            }
        }
        return "";
    }
    const std::string detect_cpu_core_number()
    {
        string line;
        int num = 0;
        BOOST_LOG_TRIVIAL(trace) << __func__;
        ifstream disk("/proc/cpuinfo");
        while(disk.good()){
            getline(disk, line);
            if(line.find("model name") != string::npos){
                num++;
            }
        }
        return to_string(num);
    }
    const std::string detect_motherboard()
    {
        string vendor = Util::get_file_content("/sys/devices/virtual/dmi/id/board_vendor");
        string name = Util::get_file_content("/sys/devices/virtual/dmi/id/board_name");
        string version = Util::get_file_content("/sys/devices/virtual/dmi/id/board_version");
        return vendor + ":" + name + ":" + version;
    }
    const std::string detect_time()
    {
        BOOST_LOG_TRIVIAL(trace) << __func__;
        const time_t now = time(NULL); 
        string tm = ctime(&now);
        tm.pop_back();
        return tm;
    }
    const std::string detect_ip()
    { // TODO
        json ips = json::array();
        json net = json::parse(Mongo::find_id("system_network",1));
        if(!net.is_null()){
            for(const auto& nic : net["interfaces"]){
                if(!nic["ip"].is_null()){
                    string ip = nic["ip"];
                    if(ip.size()>1)
                        ips.push_back(nic["ip"].get<string>());
                }
            }
        }
        return ips.dump();
    }
    const std::string detect_storage()
    {
        BOOST_LOG_TRIVIAL(trace) << __func__;
        vector<string> disks = {"sda", "sdb", "sdc", "sdd"};
        long size = 0;
        for(const auto& disk : disks){
            auto path = "/sys/class/block/" + disk + "/size";
            auto sz = Util::get_file_content(path);
            if(sz.size()){
                size += stol(sz);
            }
        }
        return to_string(size*512);
    }
    const std::string detect_memory()
    {
        long total = 0;
        string line;
        BOOST_LOG_TRIVIAL(trace) << __func__;
        ifstream mem("/proc/meminfo");
        while(mem.good()){
            getline(mem, line);
            if(line.find("MemTotal") != string::npos){
                boost::tokenizer<> tok(line);
                auto it = tok.begin();
                total = stof(*(++it));
            }
        }
        return to_string(total);
    }
    const std::string detect_uptime()
    {
        ifstream d("/proc/uptime");
        float sz = 0;
        if(d.is_open()) d >> sz;
        time_t tm = time(NULL) - sz; 
        string t = ctime(&tm);
        t.pop_back();
        return t;
    }
    const std::string detect_mmk_version()
    { 
        return Util::get_file_content("/opt/sms/www/VERSION");
    }
    const std::string detect_internet()
    { // TODO
        return "TODO";
    }
    const std::vector<std::string> detect_interfaces()
    {
        vector<string> interfaces;
        for(const auto& path : boost::filesystem::directory_iterator("/sys/class/net/")){
            string p = path.path().filename().c_str();
            string address = "/sys/class/net/" + p + "/address";
            if(boost::filesystem::exists(address)){
                ifstream addr(address);
                string mac;
                addr >> mac;
                if(mac.find("00:00:00:00:00:00") == string::npos){
                    interfaces.push_back(p);
                }
            }
        } 
        BOOST_LOG_TRIVIAL(trace) << "find interfaces num: " << interfaces.size();
        return interfaces;
    }
}
