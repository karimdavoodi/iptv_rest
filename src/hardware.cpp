#include "hardware.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include <fstream>
#include <algorithm>
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
        BOOST_LOG_TRIVIAL(trace) << "Detect output tuner:" << list.size();
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
        BOOST_LOG_TRIVIAL(trace) << "Detect input tuner:" << list.size();
        return list;
    }
    const std::string detect_network()
    {
        return "";
    }
    const json scan_input_tuner(const std::string& tuner_json)
    {
        int num = 0;
        ostringstream cmd;
        json res = json::object();
        res["content"] = json::array();
        res["total"] = res["content"].size();
        try{
            json tuner = json::parse(tuner_json);
            if(tuner["_id"].is_null()){
                BOOST_LOG_TRIVIAL(error) << "Tuner is invalid:" << tuner_json;
                res["error"] = "Tuners in invalid";
                return res;
            }
            int _id = tuner["_id"];
            if(!boost::filesystem::exists("/dev/dvb/adapter"+
                        to_string(_id)+"/frontend0")){
                BOOST_LOG_TRIVIAL(error) << "Tuner Not Exists:" << _id;
                res["error"] = "Tuner not exists";
                return res;
            }
            auto cfg_file = "/tmp/scan_freq_"+to_string(_id);
            auto out_file = "/tmp/scan_chans_"+to_string(_id);
            ofstream freq(cfg_file);
            if(!freq.is_open()){
                BOOST_LOG_TRIVIAL(error) << "Can't open scan config file";
                return res;
            }
            if(tuner["is_dvbt"] == true){
                int frq = tuner["freq"];
                if(frq < 474000 || frq > 900000 ){
                    BOOST_LOG_TRIVIAL(error) << "Invalid tuner options";
                    res["error"] = "Invalid tuner option";
                    return res;
                }
                freq << "T " << tuner["freq"].get<int>() 
                     << "000 8MHz 2/3 NONE QAM64 8k 1/8 NONE";
            }else{
                int frq = tuner["freq"];
                string pol = tuner["pol"];
                int symrate = tuner["symrate"];
                string errrate = tuner["errrate"];
                if(frq < 9000 || frq > 13000 || pol == "" || symrate == 0 ){
                    BOOST_LOG_TRIVIAL(error) << "Invalid tuner options";
                    res["error"] = "Invalid tuner option";
                    return res;
                }
                freq << "S "<< frq <<"000 " << pol <<" "<< symrate
                     << "000 " << errrate;
            }
            freq.close();
            int sw = tuner["switch"].get<int>(); 
            cmd << "/opt/sms/bin/scan-s2 -o vdr -a " 
                << _id << " -s " 
                << sw - 1     // switch 0 .. 3 in scan tools
                << " " << cfg_file << " > " << out_file;

            Util::system(cmd.str());
            //scan VDR file 
            ifstream vdr_file(out_file);
            if(!vdr_file.is_open()){
                BOOST_LOG_TRIVIAL(error) << "Can't open scan vdr file";
                res["error"] = "Can't scan the tuner";
                return res;
            }
            string line;
            while( vdr_file.good() ){
                std::getline(vdr_file, line);
                int colons = std::count_if(line.begin(), line.end(), 
                        [](char c){ return c == ':'; });
                if(colons < 8) continue;
                json chan = json::object();
                boost::tokenizer<boost::char_separator<char>> 
                    tok(line, boost::char_separator(":"));
                auto it = tok.begin();
                auto pos = it->find(';');
                if(it->at(0) == '[') continue;
                chan["dvb_id"] = _id;
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
                BOOST_LOG_TRIVIAL(trace) << chan.dump(2);
                res["content"].push_back(chan);
                num++;
            }
        }catch(std::exception& e){
            BOOST_LOG_TRIVIAL(error) << "Exception:" << e.what();
        }
        res["total"] = num;
        if(num == 0) res["error"] = "Channel not found!";
        return res;
    }
    const std::string detect_os_kernel()
    {
        ifstream version("/proc/version");
        if(version.is_open()){
            string word;
            version >> word;
            version >> word;
            version >> word;
            return word;
        }
        return "";
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
                return line.substr(line.find(':')+2);
            }
        }
        return "";
    }
    const int detect_cpu_core_number()
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
        return num;
    }
    const std::string detect_motherboard()
    {
        string vendor = Util::get_file_content("/sys/devices/virtual/dmi/id/chassis_vendor");
        string name = Util::get_file_content("/sys/devices/virtual/dmi/id/product_name");
        return vendor + ":" + name;
    }
    const long detect_time()
    {
        BOOST_LOG_TRIVIAL(trace) << __func__;
        return time(NULL); 
    }
    const std::string detect_ip()
    { 
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
    const long detect_storage()
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
        return size*512;
    }
    const long detect_memory()
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
        return total;
    }
    const long detect_uptime()
    {
        ifstream d("/proc/uptime");
        float sz = 0;
        if(d.is_open()) d >> sz;
        return time(NULL) - sz; 
        /*
        time_t tm = time(NULL) - sz; 
        string t = ctime(&tm);
        t.pop_back();
        return t;
        */
    }
    const std::string detect_mmk_version()
    { 
        return Util::get_file_content("/opt/sms/www/VERSION");
    }
    const bool detect_internet()
    { 
        string out = Util::send_http_cmd("/", "89.221.87.227", "80", "head");
        BOOST_LOG_TRIVIAL(error) << "internet:" << out.size();
        return out.size() > 0;
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
        std::sort(interfaces.begin(), interfaces.end());
        return interfaces;
    }
}
