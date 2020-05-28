#include "hardware.hpp"
#include "util.hpp"
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>

using namespace std;

std::string Hardware::scan_input_tuner(const std::string& tuner_json)
{
    ostringstream cmd;
    json res = json::object();
    res["total"] = 0;
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
            freq << "T " << tuner["freq"] << "000 8MHz 2/3 NONE QAM64 8k 1/8 NONE";
        }else{
            freq << "S "<< tuner["freq"]<<"000 "<< tuner["pol"]
                <<" "<< tuner["symrate"]<< "000 " << tuner["errrate"];
        }
        freq.close();
        cmd << "/usr/bin/scan -o vdr -a " << tuner["_id"] << " -s " << tuner["switch"] 
            << " " << cfg_file << " > " << out_file;
        std::system(cmd.str().c_str());
        ifstream vdr_file(out_file);
        if(!vdr_file.is_open()){
            BOOST_LOG_TRIVIAL(error) << "Can't open scan vdr file";
            return res.dump();
        }
        string line;
        while( vdr_file >> line ){
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
            chan["sym"] = *(++it);  // 4
            ++it; ++it; ++it; ++it; 
            chan["scramble"]  = (it->at(0) == '0') ? false : true;
            chan["sid"]  = *(++it); //9
            chan["pol"]  = *(++it); //10
            res["content"].push_back(chan);
        }
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(error) << "Exception:" << e.what();
    }
    return res.dump();
}
