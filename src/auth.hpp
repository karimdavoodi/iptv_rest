#pragma once
#include <served/served.hpp>
#include <boost/filesystem.hpp>
#include "../third_party/json.hpp"
#define PNG        ".png"
#define ZIP        ".zip"
#define ICON_PATH  "data/icons/"
#define MEDIA_PATH "data/media/"

#define CHECK_AUTH                                                  \
    do{                                                             \
       BOOST_LOG_TRIVIAL(trace) << __func__ ;                       \
       if(check_auth(req) == false){                                \
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
            Mongo::replace_by_id(col, id, req.body());              \
            BOOST_LOG_TRIVIAL(trace) << "Warning: replace id "<< id << " in " << col;  \
        }else{                                                      \
            Mongo::insert(col, req.body());                         \
        }                                                           \
        res.set_status(200);                                        \
    }while(false)                       

#define PUT_ID1_COL(col)                                            \
    do{                                                             \
        CHECK_BODY_ID;                                              \
        if(Mongo::exists_id(col, 1)){                               \
            Mongo::replace_by_id(col, 1, req.body());               \
            BOOST_LOG_TRIVIAL(trace) << "Warning: replace id 1 in " << col;  \
        }else{                                                      \
            Mongo::insert(col, req.body());                         \
        }                                                           \
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
            Mongo::insert(col, req.body());                         \
            BOOST_LOG_TRIVIAL(trace) << "Warning: insert id " << id << " in " << col;  \
        }else{                                                      \
            Mongo::replace_by_id(col, id, req.body());              \
        }                                                           \
        res.set_status(200);                                        \
    }while(false)                       

#define POST_ID1_COL(col)                                           \
    do{                                                             \
        CHECK_BODY_ID;                                              \
        if(!Mongo::exists_id(col, 1)){                              \
            Mongo::insert(col, req.body());                         \
            BOOST_LOG_TRIVIAL(trace) << "Warning: insert id 1 in " << col;  \
        }else{                                                      \
            Mongo::replace_by_id(col, 1, req.body());               \
        }                                                           \
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
        std::string result;                                         \
        if(get_id(req, id)){                                        \
            result = Mongo::find_id(col, id);                       \
        }else{                                                      \
            result = Mongo::find_id_range(col, from, to);           \
        }                                                           \
        res.set_header("Content-type", "application/json");         \
        res << result;                                              \
        res.set_status(200);                                        \
    }while(false)                       

#define GET_ID1_COL(col)                                            \
    do{                                                             \
        std::string result;                                         \
        result = Mongo::find_id(col, 1);                            \
        res.set_header("Content-type", "application/json");         \
        res << result;                                              \
        res.set_status(200);                                        \
    }while(false)                       

#define GET_TIME_ID_COL(col)                                        \
    do{                                                             \
        int id;                                                     \
        auto [from, to] = req_range(req);                           \
        auto stime = req.query.get("start-time");                  \
        auto etime = req.query.get("end-time");                    \
        if(stime.size() == 0 || etime.size() == 0){                 \
            ERRORSEND(res, 400, 1002, "Param 'start-time' or 'end-time' not exists!");\
        }                                                           \
        res << Mongo::find_time_id_range(col,                       \
                std::stol(stime), std::stol(etime), from, to);      \
        res.set_status(200);                                        \
    }while(false)                       

#define FILE_NAME_ID(path, prefix, postfix)                         \
        std::string id;                                             \
        if(!get_id(req, id)){                                       \
            ERRORSEND(res, 400, 1003, "Invalid file id!");          \
        }                                                           \
        std::string fname = std::string(path) +                     \
                            prefix + "_" + id + postfix;          

#define SEND_ID_FILE(path, prefix, postfix)                         \
    do{                                                             \
        FILE_NAME_ID(path, prefix, postfix)                         \
        if(!send_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "File not found: " + fname);  \
        }                                                           \
    }while(false)          

#define RECV_ID_FILE(path, prefix, postfix)                         \
    do{                                                             \
        FILE_NAME_ID(path, prefix, postfix)                         \
        CHECK_PATH(path);                                           \
        if(!save_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "Can't save file: " + fname); \
        }                                                           \
    }while(false)                       

#define DEL_ID_FILE(path, prefix, postfix)                          \
    do{                                                             \
        FILE_NAME_ID(path, prefix, postfix)                         \
        if(boost::filesystem::exists(fname)){                         \
            boost::filesystem::remove(fname);                         \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1006, "File not found!");           \
        }                                                           \
    }while(false)                       

#define FILE_NAME_ID_LANG(path, prefix, postfix)                    \
        std::string id;                                             \
        if(!get_id(req, id)){                                       \
            ERRORSEND(res, 400, 1003, "Invalid file id!");          \
        }                                                           \
        std::string lang = req.query.get("language");               \
        if(lang.size() < 1){                                        \
            ERRORSEND(res, 400, 1003, "Invalid lang id!");          \
        }                                                           \
        std::string fname = std::string(path) +                     \
                prefix + "_" + id + "_" + lang + postfix;             

#define SEND_ID_LANG_FILE(path, prefix, postfix)                    \
    do{                                                             \
        FILE_NAME_ID_LANG(path, prefix, postfix)                    \
        if(!send_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "File not found: " + fname);  \
        }                                                           \
    }while(false)          

#define RECV_ID_LANG_FILE(path, prefix, postfix)                    \
    do{                                                             \
        FILE_NAME_ID_LANG(path, prefix, postfix)                    \
        CHECK_PATH(path);                                           \
        if(!save_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "Can't save file: " + fname); \
        }                                                           \
    }while(false)                       

#define DEL_ID_LANG_FILE(path, prefix, postfix)                     \
    do{                                                             \
        FILE_NAME_ID_LANG(path, prefix, postfix)                    \
        if(boost::filesystem::exists(fname)){                         \
            boost::filesystem::remove(fname);                         \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1006, "File not found!");           \
        }                                                           \
    }while(false)                       

#define SEND_FILE(path, prefix, postfix)                            \
    do{                                                             \
        std::string fname = std::string(path) +                     \
                prefix + postfix;                                   \
        if(!send_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "File not found: " + fname);  \
        }                                                           \
    }while(false)          

#define RECV_FILE(path, prefix, postfix)                            \
    do{                                                             \
        std::string fname = std::string(path) +                     \
                prefix + postfix;                                   \
        CHECK_PATH(path);                                           \
        if(!save_file(res, req, fname)){                            \
            ERRORSEND(res, 403, 1004, "Can't save file: " + fname); \
        }                                                           \
    }while(false)                       

#define DEL_FILE(path, prefix, postfix)                             \
    do{                                                             \
        std::string fname = std::string(path) +                     \
                prefix + postfix;                                   \
        if(boost::filesystem::exists(fname)){                         \
            boost::filesystem::remove(fname);                         \
            res.set_status(200);                                    \
        }else{                                                      \
            ERRORSEND(res, 400, 1006, "File not found!");           \
        }                                                           \
    }while(false)                       
