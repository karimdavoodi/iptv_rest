#include <iostream>
#include <fstream>
#include <catch.hpp>
#include <served/served.hpp>
#include "../src/launcher.hpp"
#include "test_util.hpp"
using namespace std;

TEST_CASE("Test of launcher_default_post", ""){
    INIT;
    std::string j = R"(
              {
                "id": "int",
                "launcher": "string",
                "fontFa": "string",
                "fontEn": "string",
                "language": "string",
                "welcomeEn": "string",
                "welcomeFa": "string",
                "welcomeAr": "string",
                "userEn": "string",
                "userFa": "string",
                "userAr": "string",
                "playWelcomeClip": "boolean",
                "uiStartup": "string",
                "unitName": "string",
                "clientHotspot": "string",
                "testUserId": "int",
                "defaultChannel": "string"
            }
             )";

    req.set_body(j);

    launcher_default_post(res, req);
    REQUIRE(res.status() == 200);
}

TEST_CASE("Test of launcher_default_get", ""){

    INIT;

    launcher_default_get(res, req);

    REQUIRE(res.status() == 200);
    auto j = json::parse(get_body(res.to_buffer()));
    REQUIRE(j.size() > 10 );
    REQUIRE(j["launcher"] == "string");
}
TEST_CASE("Test of launcher_background_post", ""){
    INIT;
    string buf = "Data\n";
    req.set_body(buf);
    req.set_header("Content-Type", "application/x-www-form-urlencoded" );
    req.set_header("Content-Lenght", to_string(buf.size()));
    launcher_background_post(res, req);
    REQUIRE(res.status() == 200 );
}

TEST_CASE("Test of launcher_background_get", ""){
    INIT;

    served::uri uri0;
    uri0.set_query("launcher=main");
    //uri0.set_URI("/launcher_background_get?launcher=main");
    req.set_destination(uri0);
    
    launcher_background_get(res, req);
    // TODO : implement query
    //REQUIRE(res.status() == 200 );
    //REQUIRE(res.body_size() == 4 );
}
