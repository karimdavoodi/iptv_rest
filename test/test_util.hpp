#pragma once 

#include <iostream>
#define INIT                                \
    served::response res;                   \
    served::request  req;                   \
    req.set_header("Authorization", "Basic dGVzdDp0ZXN0")

std::string get_body(const std::string header_and_body){

        if(size_t pos = header_and_body.find("\r\n\r\n");
          pos != std::string::npos){
            std::string body = header_and_body.substr(pos+4);
            return body;
        }
        return "";
}
