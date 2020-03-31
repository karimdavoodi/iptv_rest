#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <served/served.hpp>
#include <csignal>
#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include "includes.hpp"
#include "mongo_driver.hpp"

#define PORT "8139"
#define THREADS 2
using namespace std;

#define DUMP_FILE "/tmp/iptv_rest.dump"
void signal_handler(int signum)
{
    signal(signum, SIG_DFL);
    //boost::stacktrace::safe_dump_to(DUMP_FILE);
    BOOST_LOG_TRIVIAL(info) << boost::stacktrace::stacktrace(); 
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
void test(served::response &res, const served::request &req)
{
    res << req.header("Authorization") << "\n";
    res << req.header("User-Agent")  << "\n";
    res << "Param:" << req.params.get("par") << "\n";
    res << "Query:" << req.query.get("id") << "\n";
    res << "Sourcs: " << req.source() << "\n";
    res << "Body:" << req.body() << "\n";
    res.set_status(200);

}
int main(int argc, char *argv[])
{
//    init_log();
    BOOST_LOG_TRIVIAL(info) << "Start Main";
    Mongo::fill_defauls();
    //signal(SIGSEGV, &signal_handler);
    //signal(SIGABRT, &signal_handler);
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

            BOOST_LOG_TRIVIAL(info) << "curl http://localhost:"<< PORT << "/{APIs}";
            served::net::server server("0.0.0.0", PORT, mux);
            server.run(); 
            break;
        }catch(std::exception& e){
            BOOST_LOG_TRIVIAL(info) << "Exception " << e.what();
        }catch(...){
            BOOST_LOG_TRIVIAL(info) << "unknown exception\n";
        }
    }
    return 0;

}
