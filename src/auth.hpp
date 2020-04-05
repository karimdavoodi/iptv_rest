#pragma once
#include <nlohmann/json.hpp>
#include <served/served.hpp>

#define CHECK_AUTH                                                  \
    do{                                                             \
       BOOST_LOG_TRIVIAL(trace) << __func__ ;                       \
       if(req.header("Authorization") != "Basic dGVzdDp0ZXN0"){     \
            res.set_status(401);                                    \
            BOOST_LOG_TRIVIAL(trace) << "Feild Auth";               \
            return;                                                 \
       }                                                            \
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

#define CHECK_PATH(path)                                        \
    do{                                                         \
        if(!std::filesystem::exists(path)){                     \
            std::filesystem::create_directory(path);            \
        }                                                       \
    }while(false)  

#define CHECK_BODY_ID                                           \
    do{                                                         \
        if(req.body().size() == 0){                             \
            ERRORSEND(res, 400, 1001, "No input!");             \
        }                                                       \
        auto j = json::parse(req.body());                       \
        if( j.count("_id") == 0 ){                              \
            ERRORSEND(res, 400, 1002, "Invalid input JSON!");   \
        }                                                       \
    }while(false)  


#define PUT_ID_COL(col)                                             \
    do{                                                             \
        CHECK_BODY_ID;                                              \
        int id = get_id_from_body_and_url(req);                     \
        if(id < 0 ){                                                \
            ERRORSEND(res, 400, 1002, "Invalid id!");               \
        }                                                           \
        if(Mongo::exists_id(col, id)){                              \
            ERRORSEND(res, 400, 1002, "Not insert, exists by _id!");\
        }                                                           \
        Mongo::insert(col, req.body());                             \
        res.set_status(200);                                        \
    }while(false)                       

#define PUT_ID1_COL(col)                                            \
    do{                                                             \
        CHECK_BODY_ID;                                              \
        if(Mongo::exists_id(col, 1)){                               \
            ERRORSEND(res, 400, 1002, "Not insert, exists id 1!");  \
        }                                                           \
        Mongo::insert(col, req.body());                             \
        res.set_status(200);                                        \
    }while(false)                       

#define POST_ID_COL(col)                                            \
    do{                                                             \
        CHECK_BODY_ID;                                               \
        int id = get_id_from_body_and_url(req);                     \
        if(id < 0 ){                                                \
            ERRORSEND(res, 400, 1002, "Invalid id!");               \
        }                                                           \
        if(!Mongo::exists_id(col, id)){                             \
            ERRORSEND(res, 400, 1002, "Not update, not exists by _id!");    \
        }                                                           \
        Mongo::replace_by_id(col, id, req.body());                  \
        res.set_status(200);                                        \
    }while(false)                       

#define POST_ID1_COL(col)                                           \
    do{                                                             \
        CHECK_BODY_ID;                                               \
        if(!Mongo::exists_id(col, 1)){                              \
            ERRORSEND(res, 400, 1002, "Not update, not exists by 1!");    \
        }                                                           \
        Mongo::replace_by_id(col, 1, req.body());                   \
        res.set_status(200);                                        \
    }while(false)                       

#define DEL_ID_COL(col)                                             \
    do{                                                             \
        int id;                                                     \
        if(!get_id(req, id) ){                                      \
            ERRORSEND(res, 400, 1002, "Invalid id!");               \
        }                                                           \
        if(!Mongo::exists_id(col, id)){                             \
            ERRORSEND(res, 400, 1002, "Not remove, not exists by _id!");\
        }                                                           \
        Mongo::remove_by_id(col, id);                               \
        res.set_status(200);                                        \
    }while(false)                       

#define DEL_ID1_COL(col)                                            \
    do{                                                             \
        if(!Mongo::exists_id(col, 1)){                              \
            ERRORSEND(res, 400, 1002, "Not remove, not exists by id 1!");\
        }                                                           \
        Mongo::remove_by_id(col, 1);                                \
        res.set_status(200);                                        \
    }while(false)                       

#define GET_ID_COL(col)                                             \
    do{                                                             \
        int id;                                                     \
        auto [from, to] = req_range(req);                           \
        if(get_id(req, id)){                                        \
            res << Mongo::find_id(col, id);                         \
        }else{                                                      \
            res << Mongo::find_id_range(col, from, to);             \
        }                                                           \
        res.set_status(200);                                        \
    }while(false)                       

#define GET_ID1_COL(col)                                            \
    do{                                                             \
        res << Mongo::find_id(col, 1);                              \
        res.set_status(200);                                        \
    }while(false)                       
