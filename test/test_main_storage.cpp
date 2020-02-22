#include <iostream>
#include <catch.hpp>
#include "../src/main_storage.hpp"

TEST_CASE("test of MainStorage","")
{
        return;
        MainStorage st;
        nlohmann::json j = st.getJson("configs","");
        REQUIRE(j.size() > 0);
        REQUIRE(j["login"].size() > 0 );
        REQUIRE(j["login"]["admin"].size() == 1);

        j["login"]["new_user"] = "mac";
        st.setJson("configs", "login", j["login"]);
        nlohmann::json j2 = st.getJson("configs","login");
        REQUIRE(j2["admin"].size() == 1);
}
