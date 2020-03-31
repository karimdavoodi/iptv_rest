#include <iostream>
#include <nlohmann/json.hpp>

int main()
{
    nlohmann::json j2 = {
        { "name", "ali"},
        { "age", 17}
    };

    nlohmann::json j3 = {
        { "name1", "ali"},
        { "age1", 17}
    };
    j2["arr_make"] = nlohmann::json::array();

    //j2.push_back("wefse");
    j2["arr_make"].push_back(j3);
    j2["arr_make"].push_back(j3);
    
    
    std::cout << j2.dump(4);
}
