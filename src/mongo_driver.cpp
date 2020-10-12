/*
 *   TODO: implement transaction 
 *      like /home/karim/src/mongocxx/mongo-cxx-driver/examples/mongocxx/with_transaction.cpp
 *   TODO: implement bulk mode
 *      like examples/mongocxx/bulk_write.cpp
 * */
#include "mongo_driver.hpp"
#include <boost/log/trivial.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <exception>
#include <string>
#include "config.hpp"

namespace Mongo {
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::basic::kvp;
    static mongocxx::instance inst{};
    static mongocxx::pool pool{mongocxx::uri{SERVER}};
    void fill_defauls(){
        try{
            if(!exists_id("uniq_counter", 1)){
                insert("uniq_counter", R"({ "_id":1, "count":100000 })");
            }
        }catch(std::exception& e){
            std::cout << e.what() << '\n';
        }
    }
    bool count(const std::string& col_name, const std::string& doc)
    {
        auto client = pool.acquire();
        mongocxx::database db = (*client)[DB_NAME];
        return db[col_name].count_documents(bsoncxx::from_json(doc));
    }
    bool exists(const std::string& col_name, const std::string& doc)
    {
        auto client = pool.acquire();
        mongocxx::database db = (*client)[DB_NAME];
        //LOG(debug) << col_name << ":" << doc;
        auto result = db[col_name].count_documents(bsoncxx::from_json(doc));
        if(result > 0) return true;
        return false;
    }
    bool exists_id(const std::string& col_name, int64_t id)
    {
        auto client = pool.acquire();
        mongocxx::database db = (*client)[DB_NAME];
        //LOG(debug) << " col:"<< col_name << " id:" << id;
        auto result = db[col_name].count_documents(make_document(kvp("_id", id)));
        if(result > 0) return true;
        return false;
    }
    bool insert(const std::string& col, const std::string& doc)
    {
        LOG(debug) << " in col:" << col << " doc:" << doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto ret = db[col].insert_one(bsoncxx::from_json(doc));
            return ret.value().inserted_id().get_int64() >= 0;
        }catch(std::exception& e){
            LOG(error) << "Exception in " << __func__ << ":" << e.what();
            return false;
        }
    }
    bool remove_mony(const std::string& col, const std::string& doc)
    {
        LOG(debug) << "col:" << col << " doc:" << doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto ret = db[col].delete_many(bsoncxx::from_json(doc));
            return ret.value().deleted_count() > 0;
        }catch(std::exception& e){
            LOG(error) << "Exception in " << __func__ << ":" << e.what();
            return false;
        }
    }
    bool remove_id(const std::string& col, int64_t id)
    {
        LOG(debug) << "col:" << col << " id:" << id;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto ret = db[col].delete_one(make_document(kvp("_id", id)));
            return ret.value().deleted_count() > 0;
        }catch(std::exception& e){
            LOG(error) << "Exception in " << __func__ << ":" << e.what();
            return false;
        }
    }
    bool replace(const std::string& col, const std::string& filter, const std::string& doc)
    {
        LOG(debug) << "col:" << col << " filter:" << filter << " doc:"<< doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            
            auto ret = db[col].replace_one(bsoncxx::from_json(filter) ,
                    bsoncxx::from_json(doc));
            return ret.value().modified_count() > 0;
        }catch(std::exception& e){
            LOG(error) << e.what();
            return false;
        }
    }
    bool insert_if_not_exists(const std::string& col,
            const std::string& filter,
            const std::string& doc)
    {
        LOG(debug) << "col:" << col << " filter:" << filter << " doc:"<< doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            mongocxx::options::update options {};
            options.upsert(true);
            auto ret = db[col].update_one(
                    bsoncxx::from_json(filter),
                    make_document(kvp("$setOnInsert", 
                            bsoncxx::from_json(doc))),
                    options);
            return ret.value().modified_count() > 0;
        }catch(std::exception& e){
            LOG(error) << e.what() ;
        }
        return false;
    }
    bool insert_or_replace_id(const std::string& col, int64_t id,
            const std::string& doc)
    {
        LOG(debug) << "col:" << col << " id:" << id << " doc:"<< doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            mongocxx::options::replace options {};
            options.upsert(true);
            auto ret = db[col].replace_one(make_document(kvp("_id", id)) ,
                    bsoncxx::from_json(doc),
                    options);
            return ret.value().modified_count() > 0;
        }catch(std::exception& e){
            LOG(error) << e.what() ;
        }
        return false;
    }
    bool replace_id(const std::string& col, int64_t id, const std::string& doc)
    {
        LOG(debug) << "col:" << col << " id:" << id << " doc:"<< doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto ret = db[col].replace_one(make_document(kvp("_id", id)) ,
                    bsoncxx::from_json(doc));
            return ret.value().modified_count() > 0;
        }catch(std::exception& e){
            LOG(error) << e.what();
            return false;
        }
        return false;
    }
    bool update_id(const std::string& col, int64_t id, const std::string& doc)
    {
        LOG(debug) << "col:" << col << " id:" << id << " doc:"<< doc;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto ret = db[col].update_one(
                    make_document(kvp("_id", id)) ,
                    make_document(kvp("$set", bsoncxx::from_json(doc))));
            return ret.value().modified_count() > 0;
        }catch(std::exception& e){
            LOG(error) << e.what();
            return false;
        }
        return false;
    }
    std::string find_mony( const std::string& col, const std::string& doc)
    {
        try{
            //LOG(debug) << " col:" << col << " doc:" << doc;
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto result = db[col].find(bsoncxx::from_json(doc));
            std::string result_str;
            for(const auto& e : result){
                result_str += bsoncxx::to_json(e) + ","; 
            }
            if(!result_str.empty()) result_str.pop_back();
            return "[" + result_str + "]";
        }catch(std::exception& e){
            LOG(error) << e.what();
        }
        return "[]";
    }
    std::string find_one( const std::string& col, const std::string& doc)
    {
        try{
            //LOG(debug) << "col:" << col << " doc:" << doc;
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto result = db[col].find_one(bsoncxx::from_json(doc));
            if (result && !(result->view().empty())) {
                bsoncxx::document::view  v(result->view());
                return bsoncxx::to_json(v); 
            }
        }catch(std::exception& e){
            LOG(error) << e.what();
        }
        return "{}";
    }
    std::string find_id(const std::string& col, int64_t id)
    {
        //LOG(debug) << "col:" << col << " id:" << id;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            auto result = db[col].find_one(make_document(kvp("_id", id)));
            if (result && !(result->view().empty())) {
                bsoncxx::document::view  v(result->view());
                return bsoncxx::to_json(v); 
            }
        }catch(std::exception& e){
            LOG(error) << e.what();
        }
        return "{}";
    }
    int64_t get_uniq_id()
    {
        std::string col = "uniq_counter"; 
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            mongocxx::options::find_one_and_update options {};
            options.return_document(mongocxx::options::return_document::k_after);
            auto result = db[col].find_one_and_update(
                    make_document(kvp("_id", 1)),
                    make_document(kvp("$inc", make_document(kvp("count", 1)))),
                    options);
            if (result && !(result->view().empty())) {
                bsoncxx::document::view  v(result->view());
                auto type =  v["count"].type();
                int64_t newId;
                if(type == bsoncxx::type::k_double)      newId = v["count"].get_double();
                else if(type == bsoncxx::type::k_int64)  newId = v["count"].get_int64();
                else if(type == bsoncxx::type::k_int32)  newId = v["count"].get_int32();
                else{
                    LOG(error) << "Invalid type of 'count': " << bsoncxx::to_string(type);
                }
                LOG(debug) << "id:" << newId;
                return newId; 
            }else{
                LOG(error) << "faiel to get uniq id!";
            }
            return 1; 
        }catch(std::exception& e){
            LOG(error) << e.what();
            return 1;
        }
    }
    std::string find_range(const std::string& col, int begin, int end)
    {
        LOG(debug) << "col:" << col << 
            " begin:" << begin << " end:" << end;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            mongocxx::options::find options {};
            options.skip(begin);
            options.limit(end - begin + 1);
            bsoncxx::document::view  v;
            int total = db[col].count_documents(v);
            auto result = db[col].find(v, options);
            std::string result_str;
            for(auto e : result){
                result_str += bsoncxx::to_json(e) + ","; 
            }
            if(!result_str.empty()) result_str.pop_back();
            result_str =  "{ \"total\": " + std::to_string(total) + 
                ", \"content\":[" + result_str + "] }";
            return result_str;
        }catch(std::exception& e){
            LOG(error) <<  e.what();
            return R"({ "total": 0, "content":[] })";
        }
    }


    std::string find_filter_range(const std::string& col,
            const std::string& filter,
            int begin, int end)
    {
        LOG(debug) << " col:" << col <<" filter:" << filter
                   << " begin:" << begin << " end:" << end;
        try{
            auto client = pool.acquire();
            mongocxx::database db = (*client)[DB_NAME];
            int total = db[col].count_documents(bsoncxx::from_json(filter));

            mongocxx::options::find options {};
            if(begin >= 0){
                options.skip(begin);
                options.limit(end - begin + 1);
            }else{
                // get from end of collection
                begin = -1 * begin;
                int skip = total - begin;
                options.skip(skip >= 0 ? skip : 0);
                if(begin > MAX_QUERY_LEN )
                    options.limit(MAX_QUERY_LEN);
            }
            auto result = db[col].find( bsoncxx::from_json(filter),options);
            std::string result_str;
            for(auto e : result){
                result_str += bsoncxx::to_json(e) + ","; 
            }
            if(!result_str.empty())
                result_str.pop_back();
            return "{ \"total\": " + std::to_string(total) + 
                ",\"content\":[" + result_str + "] }";
        }catch(std::exception& e){
            LOG(error) << e.what();
            return R"({ "total": 0, "content":[] })";
        }
    }
}
