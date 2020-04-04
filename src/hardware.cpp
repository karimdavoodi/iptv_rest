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
                    "is_dvbt": True, 
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
                    "is_dvbt": True, 
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
                        "name": string, 
                        "dvb_id": int, 
                        "is_dvbt": boolean, 
                        "sid": int, 
                        "aid": int, 
                        "vid": int,
                        "freq": int, 
                        "pol": int, 
                        "scramble": boolean, 
                        "symb": int
                    }
                 ]
            }
    )";
}
