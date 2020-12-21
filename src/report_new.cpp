#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "report_new.hpp"
#include <chrono>
using namespace std;

void report_new_get(served::response &res, const served::request &req)
{
    json request;
    json response;

	// CHECK_AUTH;   // FIXME: uncomment for authentication
    
    // Get params 
    string sensoreType = req.params.get("sensoreType");
    string reportType  = req.params.get("reportType");
    // Get body
    try{
        request = json::parse(req.body());
    }catch(...){
        ERRORSEND(res, 401, 1000, "Body is not vaild json!");
    }
    // Generate Response
    response["tables"] = json::array();
    json table1;
    response["tables"].push_back(table1);
    // Send response
    res << response.dump(1);
}
