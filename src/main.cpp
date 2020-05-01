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
#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <served/status.hpp>
#include <thread>
#include "auth.hpp"
#include "includes.hpp"
#include "mongo_driver.hpp"


#define PORT "8139"
#define THREADS 1
using namespace std;

#define DUMP_FILE "/tmp/iptv_rest.dump"
void signal_handler(int signum)
{
    signal(signum, SIG_DFL);
    string fname = DUMP_FILE + to_string( rand()%10000 );
    boost::stacktrace::safe_dump_to(static_cast<const char*>(fname.c_str()));
    //BOOST_LOG_TRIVIAL(info) << boost::stacktrace::stacktrace(); 
    raise(SIGABRT);
}
void init_log(){
    /*
   static const std::string COMMON_FMT("[%TimeStamp%][%Severity%]:  %Message%");
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::format = COMMON_FMT,
        boost::log::keywords::auto_flush = true
    );
    */
#ifndef _DEBUG
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
#endif
}
int main(int argc, char *argv[])
{
    init_log();
    BOOST_LOG_TRIVIAL(info) << "Start Main";
    Mongo::fill_defauls();
    signal(SIGSEGV, &signal_handler);
    signal(SIGABRT, &signal_handler);
    /*
    if (boost::filesystem::exists(DUMP_FILE)) {
        std::ifstream ifs(DUMP_FILE);
        boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
        std::cout << "Previous run crashed:\n" << st << std::endl;
        ifs.close();
        boost::filesystem::remove(DUMP_FILE);
    }
    */

    while(true){
        try{
            served::multiplexer mux;
            BOOST_LOG_TRIVIAL(info) << "Init Routes";

            #include "routes.hpp"
            
            mux.handle("/help").get(mux.get_endpoint_list_handler_YAML());
            
            BOOST_LOG_TRIVIAL(info) << "curl http://localhost:"<< PORT << "/help";
            mux.use_after([](served::response& res, served::request& req){});
            mux.use_before([](served::response& res, served::request& req){
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
                    "https://amazing-gates-315ab5.netlify.app"
                    };
                    auto origin =  req.header("Origin");
                    for(auto& orig : valid_origins){
                        if(origin.find(orig) != string::npos){
                            res.set_header("Access-Control-Allow-Origin", origin);
                            res.set_header("Access-Control-Allow-Credentials","true");
                            res.set_header("Access-Control-Allow-Methods",
                                    "GET, POST, PUT, DELETE, OPTIONS");

                            res.set_header("Access-Control-Allow-Headers",
                                    "accept, authorization, cache-control, content-type, dnt, if-modified-since, keep-alive, origin, user-agent, x-requested-with");
 
                            break;
                        }
                    }
                    });

            served::net::server server("0.0.0.0", PORT, mux);
            server.run(THREADS); 
            break;
        }catch(std::exception& e){
            BOOST_LOG_TRIVIAL(info) << "Exception " << e.what();
        }catch(...){
            BOOST_LOG_TRIVIAL(info) << "unknown exception\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;

}
