#pragma once
#include <iostream>
#include <vector>
#include "../third_party/json.hpp"
#include "mongo_driver.hpp"

namespace Hardware {
    std::vector<std::pair<int,std::string>> detect_input_tuners();
    std::vector<std::pair<int,std::string>> detect_output_tuners();
    std::string detect_network();
    const nlohmann::json scan_input_tuner(Mongo& db, const std::string&);
    const std::string detect_cpu_model();
    const int detect_cpu_core_number();
    const std::string detect_motherboard();
    const long detect_time();
    const std::string detect_ip(Mongo& db);
    const std::string detect_os_kernel();
    const long detect_storage();
    const long detect_memory();
    const long detect_uptime();
    const std::string detect_mmk_version();
    const bool detect_internet();
    const nlohmann::json detect_interfaces();
    void apply_network(nlohmann::json& net);
    void save_network(nlohmann::json& net);
    long file_date(const std::string& file_path);
}
