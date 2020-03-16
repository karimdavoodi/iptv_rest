#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

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
    if(req.body().size() == 0){
        ERRORSEND(res, 400, 1001, "No input!");
    }
    auto j = json::parse(req.body());
    if( j.count("launcher") == 0){
        ERRORSEND(res, 400, 1002, "Invalid input JSON!");
    }
    st.setJson("configs", "launcher_default", j);
    res.set_status(200);

}
void launcher_background_get(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << "Start launcher_background_get";
    CHECK_AUTH;
    std::string launcher_name = req.query.get("launcher");
    if(!std::filesystem::exists("conf/icon")){
        ERRORSEND(res, 400, 1003, "Path conf/icon not exists!");
    } 
    if(launcher_name.size() < 1 ){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }
    std::string bg_name = "conf/icon/background_" + launcher_name + ".png";
    std::ifstream bg(bg_name , std::ios_base::binary);
    if(bg.is_open()){
        res.set_body(std::string(
                    (std::istreambuf_iterator<char>(bg) ),
                    (std::istreambuf_iterator<char>()    )
                    ));
        res.set_header("Content-type", "image/png");
        res.set_header("Content-Lenght", std::to_string(res.body_size()));
        res.set_status(200);
    }else{
        ERRORSEND(res, 403, 1004, "background not found! " + bg_name);
    }
}
void launcher_background_post(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << "Start launcher_background_post";
    CHECK_AUTH;
    /*
    if(req.header("Content-Type").find("form") == std::string::npos){
        ERRORSEND(res, 400, 1005, "Invalid header type! " + req.header("Content-Type") );
    }
    */
    std::string launcher_name = req.query.get("launcher");
     
    if(launcher_name.size() < 1 ){
        ERRORSEND(res, 400, 1006, "Invalid launcher name!");
    }
     
    if(!std::filesystem::exists("conf/icon")){
        std::filesystem::create_directory("conf/icon");
    }

    BOOST_LOG_TRIVIAL(trace) << "Body size: " << req.body().size();
    std::string bg_name = "conf/icon/background_" + launcher_name + ".png";
    std::ofstream bg( bg_name, std::ios_base::binary);
    if(bg.is_open()){
        bg.write(req.body().c_str(), req.body().size());
        bg.close(); 
        res.set_status(200);
        BOOST_LOG_TRIVIAL(trace) << "Saved: " << bg_name;
    }else{
        ERRORSEND(res, 400, 1007, "Can't save image!" + bg_name);
    }
}
void launcher_logo_get(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << __func__ ;
    CHECK_AUTH;
    std::string launcher_name = req.query.get("launcher");
    std::string launcher_lang = req.query.get("language");

    if(!std::filesystem::exists("conf/icon")){
        ERRORSEND(res, 400, 1003, "Path conf/icon not exists!");
    } 
    if(launcher_name.size() < 1 ){
        ERRORSEND(res, 400, 1003, "Invalid launcher name!");
    }
    std::string logo_name = "conf/icon/logo_" + launcher_name + "_" + 
        launcher_lang + ".png";
    std::ifstream bg(logo_name, std::ios_base::binary);
    if(bg.is_open()){
        res.set_body(std::string(
                    (std::istreambuf_iterator<char>(bg) ),
                    (std::istreambuf_iterator<char>()    )
                    ));
        res.set_header("Content-type", "image/png");
        res.set_header("Content-Lenght", std::to_string(res.body_size()));
        res.set_status(200);
        BOOST_LOG_TRIVIAL(trace) << "Send: " << logo_name;
    }else{
        ERRORSEND(res, 403, 1004, "logo not found! " + logo_name);
    }
}
void launcher_logo_post(served::response &res, const served::request &req)
{
    BOOST_LOG_TRIVIAL(trace) << __func__ ;
    CHECK_AUTH;
    std::string launcher_name = req.query.get("launcher");
    std::string launcher_lang = req.query.get("language");
     
    if(launcher_name.size() < 1 || launcher_lang.size() < 1 ){
        ERRORSEND(res, 400, 1006, "Invalid launcher name or lang!");
    }
   
    if(!std::filesystem::exists("conf/icon")){
        std::filesystem::create_directory("conf/icon");
    }
    std::string logo_name = "conf/icon/logo_" + launcher_name + "_" + 
        launcher_lang + ".png";
    std::ofstream bg(logo_name, std::ios_base::binary);
    if(bg.is_open()){
        bg.write(req.body().c_str(), req.body().size());
        bg.close(); 
        res.set_status(200);
        BOOST_LOG_TRIVIAL(trace) << "Saved: " << logo_name;
    }else{
        ERRORSEND(res, 400, 1007, "Can't save image! " + logo_name);
    }
}

void launcher_make_get(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
	CHECK_AUTH;
}
void launcher_make_post(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
	CHECK_AUTH;
}
void launcher_make_put(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
	CHECK_AUTH;
}
void launcher_make_delete(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << __func__ ;
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
