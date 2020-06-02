#include <iostream>
#include <vector>
namespace Hardware {
    const std::vector<std::pair<int,std::string>> detect_input_tuners();
    const std::vector<int> detect_output_tuners();
    const std::string detect_network();
    const std::string scan_input_tuner(const std::string&);
    const std::string detect_cpu_model();
    const std::string detect_cpu_core_number();
    const std::string detect_motherboard();
    const std::string detect_time();
    const std::string detect_ip();
    const std::string detect_storage();
    const std::string detect_memory();
    const std::string detect_uptime();
    const std::string detect_mmk_version();
    const std::string detect_internet();
    const std::vector<std::string> detect_interfaces();
}
