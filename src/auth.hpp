#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>

#define CHECK_AUTH                                                  \
    do{                                                             \
       if(req.header("Authorization") != "Basic dGVzdDp0ZXN0"){     \
            res.set_status(401);                                    \
            BOOST_LOG_TRIVIAL(trace) << "Feild Auth";               \
            return;                                                 \
       }                                                            \
       BOOST_LOG_TRIVIAL(trace) << "Succed Auth";                   \
    }while(false)  

#define ERRORSEND(res, httpCode, errorCode, errorMessage)       \
    do{                                                         \
        json jerror;                                            \
        jerror["errorCode"] = errorCode;                        \
        jerror["errorMessage"] = errorMessage;                  \
        res << jerror.dump(4);                                  \
        res.set_status(httpCode);                               \
        BOOST_LOG_TRIVIAL(trace) << "Error: " << errorMessage;  \
        return;                                                 \
    }while(false)  
