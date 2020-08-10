#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "report.hpp"
#include "hardware.hpp"
using namespace std;
void status_information_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    try{                                                        
        json result = json::object();                                     
        json license = json::parse(Mongo::find_id("system_license", 1));      
        //LOG(trace) << license.dump(2);
        auto stat = Util::send_http_cmd("/service_stat");
        result["_id"] = 1; 
        result["Running"] = stat.find("True") != string::npos; 
        auto last_reset = Util::send_http_cmd("/last_reset");
        result["LastReset"] = last_reset.size()?
            last_reset.substr(last_reset.find("\n")):"";
        result["SystemIP"] = Hardware::detect_ip();
        result["SystemInternet"] = Hardware::detect_internet();
        result["Owner"] = license["license"]["General"]["Customer"];
        result["OwnerId"] = license["license"]["General"]["MMK_ID"];
        result["Serial"] = license["license"]["General"]["MMK_Serial"];
        result["LicenseExpire"] = license["license"]["General"]["Expire_Date"];
        result["LicenseDate"] = Hardware::file_date("/opt/sms/lic.bin");
        result["Version"] = Hardware::detect_mmk_version();
        result["CPU"] = Hardware::detect_cpu_model();
        result["Kernel"] = Hardware::detect_os_kernel();
        result["CoreNum"] = Hardware::detect_cpu_core_number();
        result["Memory"] = Hardware::detect_memory();
        result["Storage"] = Hardware::detect_storage();
        result["Model"] = Hardware::detect_motherboard();
        result["SystemDate"] = Hardware::detect_time();
        result["Uptime"] = Hardware::detect_uptime();
        result["Manufacturer"] = "Moojafzar";
        res.set_header("Content-type", "application/json");     
        res << result.dump(2);                                          
        res.set_status(200);                                    
    }catch(std::exception& e){                                  
        LOG(error) << e.what();                   
    }                       
}
void report_system_usage_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_system_usage");
}
void report_iptv_user_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_iptv_user");
}
void report_webui_user_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_webui_user");
}
void report_tuners_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_tuners");
}
void report_channels_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_channels");
}
void report_error_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_error");
}
void report_survey_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_survey");
}
void report_webui_state_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_COL("report_webui_state");
}
void report_webui_state_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("report_webui_state");
}
