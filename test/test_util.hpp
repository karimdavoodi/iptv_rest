#ifndef TEST_UTIL_HPP
#define TEST_UTIL_HPP
#include <iostream>

std::string get_body(const std::string header_and_body){

        if(size_t pos = header_and_body.find("\r\n\r\n");
          pos != std::string::npos){
            std::string body = header_and_body.substr(pos+4);
            return body;
        }
        return "";
}
#endif // TEST_UTIL_HPP
