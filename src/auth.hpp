#pragma once
#include <served/served.hpp>
#include <boost/filesystem.hpp>
#include "../third_party/json.hpp"
#include "config.hpp"

#define ERRORSEND(res, httpCode, errorCode, errorMessage)       \
    do{                                                         \
        json jerror;                                            \
        jerror["errorCode"] = errorCode;                        \
        jerror["errorMessage"] = errorMessage;                  \
        std::string result = jerror.dump(2);                    \
        res.set_header("Content-type", "application/json");     \
        res << result;                                          \
        res.set_status(httpCode);                               \
        LOG(error) << errorMessage;                             \
        return;                                                 \
    }while(false)  

#define CHECK_AUTH                                              \
    Mongo db;                                                  \
    do{                                                         \
       if(Util::check_auth(db, res, req) == false){             \
            ERRORSEND(res, 401, 1000, "Not Authorized!");       \
            return;                                             \
       }                                                        \
    }while(false)  


#define CHECK_PATH(path)                                        \
    do{                                                         \
        if(!boost::filesystem::exists(path)){                   \
            boost::filesystem::create_directory(path);          \
            LOG(trace) << "Create " << path;      \
        }                                                       \
    }while(false)  

#define GET_BODY_AS_j                                           \
        if(req.body().empty()){                                 \
            ERRORSEND(res, 400, 1001, "Body is Empty!");        \
        }                                                       \
        try{                                                    \
            j = json::parse(req.body());                        \
        }catch(...){                                            \
            ERRORSEND(res, 400, 1002, "Body is not valid json!"); \
        }                                                       \
        if(j.is_null()){                                        \
            ERRORSEND(res, 400, 1002, "Body is not valid json!"); \
        }                                                       \


#define CHECK_BODY_EXISTS_ID                                    \
    json j;                                                     \
    do{                                                         \
        GET_BODY_AS_j                                           \
        if( j.count("_id") == 0 ){                              \
            ERRORSEND(res, 400, 1003, "Json dosn't have _id!"); \
        }                                                       \
    }while(false)  

#define PUT_ID_COL(col)                                             \
    try{                                                            \
        CHECK_BODY_EXISTS_ID;                                       \
        int64_t id = Util::get_id_from_body_and_url(req);           \
        if(id < 0 ){                                                \
            ERRORSEND(res, 400, 1004, "Id not exist in body or url!");               \
        }                                                           \
        if(db.exists_id(col, id)){                              \
            db.replace_id(col, id, req.body());                 \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1005, "Record not exists!");        \
        }                                                           \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define PUT_ID1_COL(col)                                            \
    try{                                                            \
        CHECK_BODY_EXISTS_ID;                                       \
        db.insert_or_replace_id(col, 1, req.body());            \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define POST_ID_COL(col)                                            \
    json j;                                                         \
    try{                                                            \
        GET_BODY_AS_j                                               \
        int64_t _id = db.get_uniq_id();                            \
        j["_id"] = _id;                                             \
        db.insert(col, j.dump());                               \
        res.set_header("Content-Type", "application/json");         \
        res << "{ \"_id\":" + std::to_string(_id) + " }";           \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define DEL_ID_COL(col)                                             \
    int64_t id;                                                     \
    try{                                                            \
        if(!Util::get_id(req, id) ){                                \
            ERRORSEND(res, 400, 1006, "Id not exists in url!");     \
        }                                                           \
        if(id < USER_RECORD_BASE_ID){                                          \
            ERRORSEND(res, 400, 10036, "Not delete system record!");\
        }                                                           \
        if(!db.exists_id(col, id)){                             \
            ERRORSEND(res, 400, 1007, "Record not exists!");        \
        }                                                           \
        db.remove_id(col, id);                                  \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                                     \
    }do{}while(false)                       


#define GET_COL(col)                                             \
    try{                                                            \
        int64_t id;                                                     \
        res.set_header("Content-type", "application/json");         \
        if(Util::get_id(req, id)){                                 \
            res << db.find_id(col, id);                       \
        }else{                                                     \
            auto [from, to] = Util::req_range(req);                \
            const std::string parameters = Util::req_parameters(req); \
            res << db.find_filter_range(col,                    \
                parameters , from, to);                             \
        }                                                           \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define GET_ID1_COL(col)                                            \
    try{                                                            \
        std::string result;                                         \
        result = db.find_id(col, 1);                            \
        res.set_header("Content-type", "application/json");         \
        res << result;                                              \
        res.set_status(200);                                        \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define GET_FILE_PATH                                               \
        int64_t id;                                                     \
        if(!Util::get_id(req, id)){                                       \
            ERRORSEND(res, 400, 1010, "File id not exists in url!");          \
        }                                                           \
        std::string fname = Util::get_content_path(db, req, id);                   

#define SEND_ID_FILE                                                \
    try{                                                            \
        GET_FILE_PATH                                               \
        if(fname.empty()){                                            \
            ERRORSEND(res, 400, 1011, "Can't find content ID");     \
        }else if(!Util::send_file(res, req, fname)){                            \
            ERRORSEND(res, 400, 1012, "File not found: " + fname);  \
        }                                                           \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define RECV_ID_FILE                                                \
    try{                                                            \
        GET_FILE_PATH                                               \
        if(fname == ""){                                            \
            ERRORSEND(res, 400, 1013, "Can't find content ID");     \
        }else if(!Util::save_file(res, req, fname)){                \
            ERRORSEND(res, 400, 1014, "Can't save file: " + fname); \
        }                                                           \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define DEL_ID_FILE                                                  \
    try{                                                            \
        GET_FILE_PATH                                               \
        if(Util::remove_file(fname)){                         \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1015, "File not found!");           \
        }                                                           \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define SEND_FILE(name)                                             \
    try{                                                            \
        std::string fname = std::string(MEDIA_ROOT) + name;         \
        if(!Util::send_file(res, req, fname)){                            \
            ERRORSEND(res, 400, 1016, "File not found: " + fname);  \
        }                                                           \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

#define RECV_FILE(name)                                             \
    try{                                                            \
        std::string fname = std::string(MEDIA_ROOT) + name;         \
        if(!Util::save_file(res, req, fname)){                            \
            ERRORSEND(res, 400, 1017, "Can't save file: " + fname); \
        }                                                           \
    }catch(std::exception& e){                                      \
        LOG(error) << e.what();                       \
    }do{}while(false)                       

