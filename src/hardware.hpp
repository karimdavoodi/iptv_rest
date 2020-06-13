#pragma onc;
#include <iostream>
#include <vector>
#include "../third_party/json.hpp"
namespace Hardware {
    const std::vector<std::pair<int,std::string>> detect_input_tuners();
    const std::vector<int> detect_output_tuners();
    const std::string detect_network();
    const nlohmann::json scan_input_tuner(const std::string&);
    const std::string detect_cpu_model();
    const int detect_cpu_core_number();
    const std::string detect_motherboard();
    const long detect_time();
    const std::string detect_ip();
    const std::string detect_os_kernel();
    const long detect_storage();
    const long detect_memory();
    const long detect_uptime();
    const std::string detect_mmk_version();
    const bool detect_internet();
    const std::vector<std::string> detect_interfaces();
}
