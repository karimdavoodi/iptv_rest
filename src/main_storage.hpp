#pragma once
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <boost/log/trivial.hpp>
using json = nlohmann::json;

class MainStorage {
    public:
        MainStorage();
        nlohmann::json getJson(std::string fileName, std::string section);
        void setJson(std::string fileName, std::string section, nlohmann::json js);
        ~MainStorage();
    private:
        nlohmann::json configs;
        nlohmann::json channels;
        nlohmann::json users;
        nlohmann::json license;
        nlohmann::json vod_users;
        std::mutex write_mutex;
};
