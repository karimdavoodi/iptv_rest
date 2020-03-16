/*

*/
#include <cstdlib>
#include <iostream>
#include <served/served.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "main_storage.hpp"
#include "includes.hpp"

#define PORT "8139"
#define THREADS 2
using namespace std;

MainStorage st;
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

    served::multiplexer mux;
    BOOST_LOG_TRIVIAL(info) << "Init Routes";
    //mux.handle("/test/{par}").get(test);
    #include "routes.hpp"

    BOOST_LOG_TRIVIAL(info) << "curl http://localhost:"<< PORT << "/{APIs}";
    
    served::net::server server("0.0.0.0", PORT, mux);
    server.run(THREADS); // Run with a pool of 10 threads.
    return 0;
}
