#include "hardware.hpp"
std::string Hardware::input_tuners()
{
    return R"( 
            {
                "total":1,
                "content":[    
                    {
                    "_id": 1,
                    "name": "", 
                    "is_dvbt": true, 
                    }
                 ]
            }
    )";
}

std::string Hardware::output_tuners()
{
    return R"( 
            {
                "total":1,
                "content":[    
                    {
                    "_id": 1,
                    "name": "", 
                    "is_dvbt": true, 
                    }
                 ]
            }
    )";
}
std::string Hardware::scan_input_tuner(const std::string& tuner_json)
{
    return R"( 
            {
                "total":1,
                "content":[    
                    {
                        "name": "string", 
                        "dvb_id": 1, 
                        "is_dvbt": true, 
                        "sid": 1, 
                        "aid": 1, 
                        "vid": 1,
                        "freq": 1, 
                        "pol": 1, 
                        "scramble": true, 
                        "symb": 1
                    }
                 ]
            }
    )";
}
