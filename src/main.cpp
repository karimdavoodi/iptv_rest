#include <chrono>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <served/methods.hpp>
#include <served/request.hpp>
#include <served/response.hpp>
#include <served/served.hpp>
#include <csignal>
#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/current_process_name.hpp>
#include <served/status.hpp>
#include <thread>
#include <tuple>
#include "auth.hpp"
#include "util.hpp"
#include "hardware.hpp"
#include "includes.hpp"
#include "mongo_driver.hpp"

#define PORT "8139"
#define THREADS 4
using namespace std;

void init_log(int argc, char* argv[]);
void do_before_api(served::response& res, 
        const served::request& req);
void get_users_access_list(served::response& res, 
        const served::request& req,
        served::multiplexer& mux);

int main(int argc, char *argv[])
{
    string port = (argc == 2) ? argv[1] : PORT;
    init_log(argc, argv);
    if( geteuid() != 0 ){
        LOG(error) << "Must run by root";
        return -1;
    }
    string s;
    
    LOG(info) << "Start Main "; 
    Mongo::fill_defauls();
    try{
        served::multiplexer mux;
        
        // Add ALL APIs to multiplexer
        #include "routes.hpp"

        // Only for test parameters
        mux.handle("/test").get(Util::test); 

        // List API
        mux.handle("/system/users_accesslist")
            .get([&](served::response& res, 
                     const served::request& req){
                    get_users_access_list(res, req, mux);
                });

        // Call BEFORE any API
        mux.use_before(do_before_api);

        // Call AFTER any API (for debugging)
        mux.use_after([&](served::response& res, 
                          served::request& req){
                if(argc == 2)  // debug mode
                    LOG(trace) << "RESULT:\n" <<  res.to_buffer();
                });

        LOG(info) << "Listen on:" << port;
        served::net::server server("0.0.0.0", port, mux);
        server.run(THREADS); 
    }catch(std::exception& e){
        LOG(error) << "Exception " << e.what();
    }catch(...){
        LOG(error) << "unknown exception\n";
    }
    return 0;
}
void get_users_access_list(served::response& res, 
                           const served::request& req,
                           served::multiplexer& mux)
{
    using nlohmann::json;
    res.set_header("Content-Type", "application/json");
    json j = json::object();
    
    auto endpoint_list = mux.get_endpoint_list();
    for ( const auto & endpoint : endpoint_list ){
        j[endpoint.first] = json::array();
        for ( const auto & method : std::get<1>(endpoint.second) ){
            j[endpoint.first].push_back(method);
        }
    }
    
    res << j.dump(2);
    res.set_status(200);

}
void do_before_api(served::response& res, const served::request& req)
{
    LOG(trace) << "URL:" << req.url().URI();
    if(req.method() != served::method::OPTIONS){
        res.set_status(served::status_4XX::NOT_FOUND);  
    }else{
        res.set_header("Allow", "GET, POST, PUT, DELETE");
    }
    // Date header
    auto now1 = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now1);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), 
            "%a, %d %b %Y %H:%M:%S %Z");
    res.set_header("Date", ss.str());
    // CORS header
    vector<string> valid_origins = {
        "http://localhost:8000",
        "http://localhost:8081",
        "http://iptv2.moojafzar.com",
        "http://91.98.142.60:4443",
        "https://amazing-gates-315ab5.netlify.app"
    };
    auto origin =  req.header("Origin");
    // FIXME: enable CORS controlling
    //for(auto& orig : valid_origins){
    //    if(origin.find(orig) != string::npos){
    res.set_header("Access-Control-Allow-Origin", origin);
    res.set_header("Access-Control-Allow-Credentials","true");
    res.set_header("Access-Control-Allow-Methods",
            "GET, POST, PUT, DELETE, OPTIONS");

    res.set_header("Access-Control-Allow-Headers",
            "accept, authorization, cache-control, content-type, dnt, if-modified-since, keep-alive, origin, user-agent, x-requested-with");
    //        break;
    //    }
    //}
}

void init_log(int argc, char* argv[]){
    namespace logging = boost::log;
    namespace keywords = boost::log::keywords;
    namespace attrs = boost::log::attributes;
    logging::add_common_attributes();
    logging::core::get()->add_global_attribute(
            "Process", attrs::current_process_name());
    auto log_out = (argc == 2) ? "/dev/stdout" : "/tmp/iptv_api.log";
    logging::add_file_log
        (
         keywords::file_name = log_out,
         keywords::format = "%TimeStamp% %Process% %ThreadID% %Severity%: %Message%",
         keywords::auto_flush = true,
         keywords::open_mode = std::ios_base::app
         //%TimeStamp% %Process% %ThreadID% %Severity% %LineID% %Message%"     
        );
    logging::core::get()->set_filter
        (
         logging::trivial::severity >= logging::trivial::trace
        );
}
