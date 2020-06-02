#pragma once
#include <served/served.hpp>
#include <boost/filesystem.hpp>
#include "../third_party/json.hpp"

#define CHECK_AUTH                                                  \
    do{                                                             \
       BOOST_LOG_TRIVIAL(trace) << __func__ ;                       \
       if(Util::check_auth(req) == false){                                \
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
        std::string result = jerror.dump(4);                    \
        res.set_header("Content-type", "application/json");     \
        res << result;                                          \
        res.set_status(httpCode);                               \
        BOOST_LOG_TRIVIAL(trace) << "Error: " << errorMessage;  \
        return;                                                 \
    }while(false)  

#define CHECK_PATH(path)                                        \
    do{                                                         \
        if(!boost::filesystem::exists(path)){                   \
            boost::filesystem::create_directory(path);          \
            BOOST_LOG_TRIVIAL(trace) << "Create " << path;      \
        }                                                       \
    }while(false)  

#define GET_BODY_AS_j                                           \
        if(req.body().size() == 0){                             \
            ERRORSEND(res, 400, 1001, "No input!");             \
        }                                                       \
        auto j = json::parse(req.body());                       \
        if(j.is_null()){                                        \
            ERRORSEND(res, 400, 1001, "No valid input!");       \
        }                                                       \


#define CHECK_BODY_EXISTS_ID                                    \
    do{                                                         \
        GET_BODY_AS_j                                             \
        if( j.count("_id") == 0 ){                              \
            ERRORSEND(res, 400, 1002, "Invalid input JSON!");   \
        }                                                       \
    }while(false)  

#define PUT_ID_COL(col)                                             \
    try{                                                            \
        CHECK_BODY_EXISTS_ID;                                       \
        int id = Util::get_id_from_body_and_url(req);                     \
        if(id < 0 ){                                                \
            ERRORSEND(res, 400, 1002, "Invalid id!");               \
        }                                                           \
        if(Mongo::exists_id(col, id)){                              \
            Mongo::replace_id(col, id, req.body());              \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1003, "Exists, not insert!");       \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define PUT_ID1_COL(col)                                            \
    try{                                                            \
        CHECK_BODY_EXISTS_ID;                                       \
        Mongo::insert_or_replace_id(col, 1, req.body());            \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define POST_ID_COL(col)                                            \
    try{                                                            \
        GET_BODY_AS_j                                               \
        j["_id"] = Mongo::get_uniq_id();                            \
        Mongo::insert(col, j.dump());                               \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define POST_ID1_COL(col)                                           \
    try{                                                            \
        GET_BODY_AS_j                                               \
        j["_id"] = 1;                                               \
        Mongo::insert_or_replace_id(col, 1, j.dump());              \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define DEL_ID_COL(col)                                             \
    try{                                                            \
        int id;                                                     \
        if(!Util::get_id(req, id) ){                                      \
            ERRORSEND(res, 400, 1002, "Invalid id!");               \
        }                                                           \
        if(!Mongo::exists_id(col, id)){                             \
            ERRORSEND(res, 400, 1002, "Not remove, not exists by _id!");\
        }                                                           \
        Mongo::remove_id(col, id);                               \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define DEL_ID1_COL(col)                                            \
    try{                                                            \
        if(!Mongo::exists_id(col, 1)){                              \
            ERRORSEND(res, 400, 1002, "Not remove, not exists by id 1!");\
        }                                                           \
        Mongo::remove_id(col, 1);                                \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define GET_COL(col)                                             \
    try{                                                            \
        int id;                                                     \
        res.set_header("Content-type", "application/json");         \
        if(Util::get_id(req, id)){                                        \
            res << Mongo::find_id(col, id);                       \
        }else{                                                      \
            auto [from, to] = Util::req_range(req);                           \
            const std::string parameters = Util::req_parameters(req); \
            res << Mongo::find_filter_range(col,                       \
                parameters , from, to);      \
        }                                                           \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define GET_ID1_COL(col)                                            \
    try{                                                            \
        std::string result;                                         \
        result = Mongo::find_id(col, 1);                            \
        res.set_header("Content-type", "application/json");         \
        res << result;                                              \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define FILE_NAME_ID(path, prefix, postfix)                         \
        std::string id;                                             \
        if(!Util::get_id(req, id)){                                       \
            ERRORSEND(res, 400, 1003, "Invalid file id!");          \
        }                                                           \
        std::string fname = std::string(path) +                     \
                            prefix + "_" + id + postfix;          

#define GET_FILE_PATH                                               \
        int id;                                                     \
        if(!Util::get_id(req, id)){                                       \
            ERRORSEND(res, 400, 1003, "Invalid file id!");          \
        }                                                           \
        std::string fname = Util::get_content_path(req, id);                   

#define SEND_ID_FILE                                                \
    try{                                                            \
        GET_FILE_PATH                                               \
        if(!Util::send_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "File not found: " + fname);  \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define RECV_ID_FILE                                                \
    try{                                                            \
        GET_FILE_PATH                                               \
        if(!Util::save_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "Can't save file: " + fname); \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define DEL_ID_FILE                                                  \
    try{                                                            \
        GET_FILE_PATH                                               \
        if(boost::filesystem::exists(fname)){                         \
            boost::filesystem::remove(fname);                         \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1006, "File not found!");           \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define SEND_FILE(name)                                             \
    try{                                                            \
        std::string fname = std::string(MEDIA_ROOT) + name;         \
        if(!Util::send_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "File not found: " + fname);  \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define RECV_FILE(name)                                             \
    try{                                                            \
        std::string fname = std::string(MEDIA_ROOT) + name;         \
        if(!Util::save_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "Can't save file: " + fname); \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       

#define DEL_FILE(name)                             \
    try{                                                            \
        std::string fname = std::string(MEDIA_ROOT) + name;         \
        if(boost::filesystem::exists(fname)){                         \
            boost::filesystem::remove(fname);                         \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1006, "File not found!");           \
        }                                                           \
    }catch(std::exception& e){                                      \
        BOOST_LOG_TRIVIAL(error) << e.what();                       \
    }do{}while(false)                       
