#include <iostream>
#include <catch.hpp>
#include <served/served.hpp>
#include "../src/launcher.hpp"
#include "test_util.hpp"


TEST_CASE("Test of launcher_default_post", ""){
    served::response res;
    served::request  req;
    req.set_header("Authorization", "Basic dGVzdDp0ZXN0");
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
    served::response res;
    served::request  req;
    req.set_header("Authorization", "Basic dGVzdDp0ZXN0");

    launcher_default_get(res, req);

    REQUIRE(res.status() == 200);
    auto j = json::parse(get_body(res.to_buffer()));
    REQUIRE(j.size() > 10 );
    REQUIRE(j["launcher"] == "string");
}
TEST_CASE("Test of launcher_background_post", ""){
    served::response res;
    served::request  req;
    req.set_header("Authorization", "Basic dGVzdDp0ZXN0");
}

TEST_CASE("Test of launcher_background_get", ""){

}
