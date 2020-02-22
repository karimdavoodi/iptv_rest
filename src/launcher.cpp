#include <iostream>
#include <iomanip>
#include <fstream>
#include "auth.hpp"
#include "launcher.hpp"

extern MainStorage st;
void launcher_default_get(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << "Start launcher_default_get";
    CHECK_AUTH;
    res << st.getJson("configs", "launcher_default").dump(4);
}
void launcher_default_post(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << "Start launcher_default_post";
    CHECK_AUTH;
    auto j = json::parse(req.body());
    st.setJson("configs", "launcher_default", j);
    res.set_status(200);
}
void launcher_background_get(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << "Start launcher_background_get";
    CHECK_AUTH;
}
void launcher_background_post(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << "Start launcher_background_post";
	CHECK_AUTH;
    if(req.header("Content-Type") != "application/x-www-form-urlencoded" ){
        res.set_status(403);
        return;
    }

    std::ofstream bg("conf/bg.png");
    if(bg.is_open()){
        bg.write(req.body().c_str(), req.body().size());
    }
    //res <<  "Content-Lengh" << req.header("Content-Length") << "\n";
    std::cout << "BODY:";
    for(int i=0; i<32; i++)
            std::cout << std::hex <<  std::setfill('0') << std::setw(2) << (0xff & (int)req.body()[i]) << ',';
    std::cout << std::endl << std::flush;
}
void launcher_logo(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_logo";
	CHECK_AUTH;
}
void launcher_make(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_make";
	CHECK_AUTH;
}
void launcher_make_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_make_id";
	CHECK_AUTH;
}
void launcher_arrange(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_arrange";
	CHECK_AUTH;
}
void launcher_arrange_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start launcher_arrange_id";
	CHECK_AUTH;
}
