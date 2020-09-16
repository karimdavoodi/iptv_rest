#include <fstream>
#include <algorithm>
#include <ios>
#include <time.h>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include "hardware.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"

using namespace std;
namespace Hardware {
    long file_date(const std::string file_path)
    {
        struct stat st;
        if(!stat(file_path.c_str(), &st)){
            return st.st_mtim.tv_sec;
        }
        return 0;
    }
    const std::vector<pair<int,string>> detect_output_tuners()
    {
        vector<pair<int,string>> list;
        try{
            for(int i=0; i<4; ++i){
                if(boost::filesystem::exists("/dev/tbsmod"+to_string(i))){
                    for(int j=0; j<5; ++j){
                        auto dev = "/dev/tbsmod" + to_string(i) + "/mod" + to_string(j);
                        if(boost::filesystem::exists(dev)){
                            list.push_back({1000 + i*100 + j, dev});
                        }
                    }
                }
            }
            // FIXME: conflict tuners index
            for(size_t i=0; i<32; ++i){
                auto dev = "/dev/usb-it950x"+to_string(i); 
                if(boost::filesystem::exists(dev)){
                    list.push_back({2000 + i, dev});
                }
            }
        }catch(std::exception& e){
            LOG(error) << e.what();
        }
        LOG(trace) << "Detect output tuner:" << list.size();
        return list;
    }
    const vector<pair<int,string>> detect_input_tuners()
    {
        vector<pair<int,string>> list;
        try{
            if(boost::filesystem::exists("/dev/dvb")){
                for(size_t i=0; i<64; ++i){
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
            LOG(error) << e.what();
        }
        LOG(trace) << "Detect input tuner:" << list.size();
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
        res["total"] = 0;
        try{
            json tuner = json::parse(tuner_json);
            if(tuner["_id"].is_null() || 
               !tuner["systemId"].is_number() ||
               !tuner["frequencyId"].is_number() ||
               !tuner["virtual"].is_boolean()){
                LOG(error) << "Tuner is invalid:" << tuner_json;
                res["error"] = "Tuners is invalid";
                return res;
            }
            if(tuner["virtual"]){
                LOG(error) << "Tuner is virtual:" << tuner_json;
                res["error"] = "Tuners is virtual";
                return res;
            }
            auto freq_rec = json::parse(Mongo::find_id("live_satellites_frequencies", 
                                        tuner["frequencyId"]));
            if(freq_rec["_id"].is_null() || freq_rec["parameters"].is_null()){
                LOG(error) << "Freq is invalid";
                res["error"] = "Frequency is invalid";
                return res;
            }
            int _id = tuner["systemId"]; 
            string parameters = freq_rec["parameters"];
            if(!boost::filesystem::exists("/dev/dvb/adapter"+
                        to_string(_id)+"/frontend0")){
                LOG(error) << "Tuner Not Exists:" << _id;
                res["error"] = "Tuner not exists";
                return res;
            }
            auto cfg_file = "/tmp/scan_freq_"+to_string(_id);
            auto out_file = "/tmp/scan_chans_"+to_string(_id);
            ofstream freq(cfg_file);
            if(!freq.is_open()){
                LOG(error) << "Can't open scan config file";
                return res;
            }
            freq << parameters;
            freq.close();
            int sw = tuner["diSEqC"]; 
            cmd << "/opt/sms/bin/scan-s2 -o vdr -a " 
                << _id << " -s " 
                << sw - 1     // switch 0 .. 3 in scan tools
                << " " << cfg_file << " > " << out_file;

            Util::system(cmd.str());
            //scan VDR file 
            ifstream vdr_file(out_file);
            if(!vdr_file.is_open()){
                LOG(error) << "Can't open scan vdr file";
                res["error"] = "Can't scan the tuner";
                return res;
            }
            int n = 1;
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
                chan["_id"]  = n++; 
                chan["name"] = (pos == string::npos) ? *it : it->substr(0,pos); 

                for(size_t i=0; i<8; ++i) 
                    ++it;
                
                chan["scrambled"]  = (it->at(0) == '0') ? false : true;
                chan["serviceId"]  = *(++it); //9
                chan["videoId"]  = 0; //TODO
                chan["audioId"]  = 0; //TODO
                //LOG(trace) << chan.dump(2);
                res["content"].push_back(chan);
                num++;
            }
        }catch(std::exception& e){
            LOG(error) << "Exception:" << e.what();
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
        LOG(trace) << __func__;
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
        LOG(trace) << __func__;
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
        LOG(trace) << __func__;
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
        LOG(trace) << __func__;
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
        LOG(trace) << __func__;
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
    }
    const std::string detect_mmk_version()
    { 
        return Util::get_file_content("/opt/sms/www/VERSION");
    }
    const bool detect_internet()
    { 
        try{
            return Util::test_internet_connection("195.146.59.198", "80");
        }catch(...){
            return false;
        }
    }
    const nlohmann::json detect_interfaces()
    {
        json nics = json::array();
        // Get Name of Interfaces
        for(const auto& path : boost::filesystem::directory_iterator("/sys/class/net/")){
            string link = boost::filesystem::read_symlink(path).string();
            if(link.find("devices/virtual/net/") == string::npos){
                json nic;
                nic["name"] = path.path().filename().string();
                nic["ip"] = "";
                nic["mask"] = "";
                nics.push_back(nic);
            }
        } 

        // Get IP Address 
        istringstream in { Util::shell_out("ip addr show") }; 
        string line;
        while(getline(in, line)){
        //  inet 192.168.43.154/24 brd 192.168.43.255 scope global dynamic noprefixroute wlo1
            if(line.find("inet ") == string::npos) continue;
            for(auto& nic : nics){
                string name = nic["name"];
                if(line.find(name) != string::npos){
                    istringstream line_in {line};
                    string addr;
                    line_in >> addr; line_in >> addr;
                    auto pos = addr.find("/");
                    if(pos == string::npos){
                        LOG(warning) << "Invalid ip addr:" << addr;
                        break;
                    }
                    nic["ip"]   = addr.substr(0, pos);
                    nic["mask"] = addr.substr(pos+1);
                    break;
                }
            }
        }
        
        LOG(trace) << "Find systen NIC:" << nics.size();
        return nics;
    }
    void convert_mask(string& mask)
    {
        if(mask == "255.255.255.255" ) mask = "32";
        else if(mask == "255.255.255.0" ) mask = "24";
        else if(mask == "255.255.0.0" ) mask = "16";
        else if(mask == "255.0.0.0" ) mask = "8";
        else{
            int one_count = 0;
            unsigned  n[4];
            std::sscanf(mask.c_str(), "%u.%u.%u.%u", &n[0], &n[1], &n[2], &n[3]);
            for(size_t i=0; i<4; ++i){
                for(size_t j=0; j<9; ++j){
                    if( ((n[i] >> j) & 0x01) == 1) one_count++;
                }
            }
            mask = to_string(one_count);
        } 
    }
    uint32_t net_addr(const string ip, const string mask)
    {
        uint32_t i_ip = 0;
        uint32_t i_mask = stoi(mask);
        inet_pton(AF_INET, ip.c_str(), &i_ip);
        i_ip = ntohl(i_ip);
        i_ip = i_ip >> (32 - i_mask);
        
        return i_ip;
    }
    void save_network(json& net)
    {
        string plan;
        plan = "network:\n"
                "    ethernets:\n";
        if(net["interfaces"].is_array()){
            for(auto& nic : net["interfaces"]){
                string name = nic["name"];
                string ip = nic["ip"];
                string mask = nic["mask"];
                if(!name.size() || !ip.size() || !mask.size()){
                    LOG(error) << "Invalid NIC fileds IP:" << ip 
                        << " mask:" << mask << " name:" << name;
                    continue;
                }
                if(mask.find(".") != string::npos){
                    convert_mask(mask);
                }
                plan += "        " + name + ":\n"
                        "            " + "addresses:\n"
                        "            - " + ip + "/" + mask + "\n";
                if(!net["gateway"].is_null()){
                    string gateway = net["gateway"];
                    if(net_addr(ip, mask) == net_addr(gateway, mask)){
                        plan += "            gateway4: " + gateway + "\n"; 
                        plan += "            nameservers:\n";
                        plan += "                addresses:\n";
                        plan += "                - " + net["dns"].get<string>() + "\n"; 
                    }else{
                        plan += "            nameservers: {}\n";
                    }
                }
            }
        }
        plan += "    version: 2\n";
        LOG(debug) << plan;
        for(const auto& file : boost::filesystem::directory_iterator("/etc/netplan")){
            string config_file = file.path().string();
            LOG(debug) << "Try to write net plan to " << config_file;
            if(plan.find("wlp") != string::npos){
                LOG(error) << "Not write in my system!";
                return; // NOT SAVE IN MY PC
            } 
            ofstream out_file(config_file);
            if(out_file.is_open()){
                out_file << plan;
                out_file.close();
                LOG(debug) << "Write net plan to " << config_file;
            }
            break;
        }

    // and add to /etc/netplan/01-network-manager-all.yaml
/*
 * Sample YAML in /etc/netplan/01-network-manager-all.yaml 
 network:
  ethernets:
    enp3s0f0:
      addresses:
      - 192.168.1.65/24
      nameservers: {}
    enp3s0f1:
      addresses:
      - 192.168.2.65/24
      gateway4: 192.168.2.1
      nameservers:
        addresses:
        - 1.1.1.1
        search:
        - 8.8.8.8
  version: 2

 
 * */
    }
    bool valid_command_string(const string cmd)
    {
        if(cmd.find("&") != string::npos || 
           cmd.find("|") != string::npos || 
           cmd.find(";") != string::npos ){
                LOG(error) << "Invalid command: " << cmd;
                return false;
        }
        return true;
    }
    void apply_network(json& net)
    {
        // Set Interfaces IP
        if(net["interfaces"].is_array()){
            for(auto& nic : net["interfaces"]){
                string name = nic["name"];
                string ip = nic["ip"];
                string mask = nic["mask"];
                if(mask.find(".") != string::npos){
                    convert_mask(mask);
                }
                if(!ip.size() || !name.size() || !mask.size()) continue;
                string cmd = "ip address flush dev " + name;
                Util::system(cmd); 
                cmd = "ip address add " + ip + "/" + mask +" dev " + name;  
                Util::system(cmd); 
            }
        }
        // Set Gateway
        string gw = net["gateway"];
        if(gw.size() > 0 ){
            string cmd = "/bin/ip route del default";
            Util::system(cmd);
            cmd = "/bin/ip route add default via "+ gw;
            Util::system(cmd);
        }
        // Set DNS ...
        string dns = net["dns"];
        if(dns.size() > 1){
            ofstream dnsf("/etc/resolv.conf");
            if(dnsf.is_open()){
                dnsf << "nameserver " << dns;
            }
        }

        // Set Static Routes
        for(auto route : net["staticRoute"].get<vector<string>>()){ 
            if(valid_command_string(route) && route.find(" via ") != string::npos){
                // route = "192.168.1.0/24 via 192.168.43.1"
                string cmd = "/bin/ip route add "  + string(route);
                Util::system(cmd);
            }
        }
        // Set Static iptabels t
        for(auto rule : net["firewallRule"].get<vector<string>>()){ 
            if(valid_command_string(rule)){
                string cmd = "/usr/sbin/iptables "  + string(rule);
                Util::system(cmd);
            }
        }
    }
}
