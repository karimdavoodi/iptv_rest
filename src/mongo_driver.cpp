#include "mongo_driver.hpp"
#include <exception>
#include <string>
#include <utility>
#include <mutex>
#define DB_NAME "iptv"
//#define SERVER  "mongodb://172.17.0.1:27017"  // in Docker
#define SERVER  "mongodb://0.0.0.0:27017"

static mongocxx::instance inst{};
static mongocxx::client client{mongocxx::uri{SERVER}};

using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;
std::mutex db_mutex;

void Mongo::fill_defauls(){
    try{
        if(!exists_id("uniq_counter", 1)){    
            insert("uniq_counter", "{ \"_id\":1, \"count\":1000 }");
        }
    }catch(std::exception& e){
        std::cout << e.what() << '\n';
    }
}
void Mongo::info()
{
    std::lock_guard<std::mutex> lo(db_mutex);
    
    BOOST_LOG_TRIVIAL(trace) << __func__ ;
    auto dbs = client.database("iptv");
    auto cols = dbs.list_collection_names();
    for(auto col : cols){
        std::cout << "col:" << col << '\n';
    }
}
bool Mongo::exists(const std::string col_name, const std::string doc)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    auto db = client[DB_NAME];     
    
    BOOST_LOG_TRIVIAL(trace) << __func__  << col_name << doc;
    auto result = db[col_name].count_documents(bsoncxx::from_json(doc));
    if(result > 0) return true;
    return false;
}
bool Mongo::exists_id(const std::string col_name, int id)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    BOOST_LOG_TRIVIAL(trace) << __func__ << " col:"<< col_name << " id:" << id;
    auto db = client[DB_NAME];     
    
    auto result = db[col_name].count_documents(make_document(kvp("_id", id)));
    if(result > 0) return true;
    return false;
}
bool Mongo::insert(const std::string col, const std::string doc)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    BOOST_LOG_TRIVIAL(trace) << __func__  << " in col:" << col << " doc:" << doc;
    try{
        auto dB = client[DB_NAME];
        auto ret = dB[col].insert_one(bsoncxx::from_json(doc));
        return ret.value().inserted_id().get_int64() >= 0;
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return false;
    }
}
bool Mongo::remove(const std::string col, const std::string doc)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    BOOST_LOG_TRIVIAL(trace) << __func__  << " from col:" << col << " doc:" << doc;
    try{
        auto dB = client[DB_NAME];
        auto ret = dB[col].delete_one(bsoncxx::from_json(doc));
        return ret.value().deleted_count() > 0;
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return false;
    }
}
bool Mongo::remove_by_id(const std::string col, int id)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    BOOST_LOG_TRIVIAL(trace) << __func__  << " from col:" << col << " id:" << id;
    try{
        auto dB = client[DB_NAME];
        auto ret = dB[col].delete_one(make_document(kvp("_id", id)));
        return ret.value().deleted_count() > 0;
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return false;
    }
}
bool Mongo::replace(const std::string col, const std::string filter, const std::string doc)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    BOOST_LOG_TRIVIAL(trace) << __func__  << " in col:" << col << " filter:" << filter;
    try{
        auto dB = client[DB_NAME];
        auto ret = dB[col].replace_one(bsoncxx::from_json(filter) ,bsoncxx::from_json(doc));
        return ret.value().modified_count() > 0;
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return false;
    }
}
bool Mongo::replace_by_id(const std::string col, int id, const std::string doc)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    BOOST_LOG_TRIVIAL(trace) << __func__ << " id:" << id;
    try{
        auto dB = client[DB_NAME];
        auto ret = dB[col].replace_one(make_document(kvp("_id", id)) ,
                                       bsoncxx::from_json(doc));
        return ret.value().modified_count() > 0;
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return false;
    }
    return false;
}
const std::string Mongo::find_one( const std::string col, const std::string doc)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    auto dB = client[DB_NAME];     
    
    try{
        BOOST_LOG_TRIVIAL(trace) << __func__  << " in col:" << col << " doc:" << doc;
        auto result = dB[col].find_one(bsoncxx::from_json(doc));
        if (result && !(result->view().empty())) {
            bsoncxx::document::view  v(result->view());
            return bsoncxx::to_json(v); 
        }
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
    }
    return "{}";
}
const std::string Mongo::find_id(const std::string col, int id)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    auto dB = client[DB_NAME];     
   
    BOOST_LOG_TRIVIAL(trace) << __func__  << " in col:" << col << " id:" << id;
    try{
        auto result = dB[col].find_one(make_document(kvp("_id", id)));
        if (result && !(result->view().empty())) {
            bsoncxx::document::view  v(result->view());
            return bsoncxx::to_json(v); 
        }
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
    }
    return "{}";
}
int Mongo::get_uniq_id()
{
    std::lock_guard<std::mutex> lo(db_mutex);
    auto dB = client[DB_NAME];     
    std::string col = "uniq_counter"; 
    int id = 1;
    BOOST_LOG_TRIVIAL(trace) << __func__ << " id:" << id;
    try{
        mongocxx::options::find_one_and_update options {};
        options.return_document(mongocxx::options::return_document::k_after);
        auto result = dB[col].find_one_and_update(
                make_document(kvp("_id", id)),
                make_document(kvp("$inc", make_document(kvp("count", 1)))),
                options);
        if (result && !(result->view().empty())) {
            bsoncxx::document::view  v(result->view());
            int newId = v["count"].get_int32(); 
            return newId; 
        }
        return 1; 

    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return 1;
    }
}
const std::string Mongo::find_range(const std::string col, int begin, int end)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    auto dB = client[DB_NAME];     
   
    BOOST_LOG_TRIVIAL(trace) << __func__  << " in col:" << col << 
        " begin:" << begin << " end:" << end;
    try{
        mongocxx::options::find options {};
        options.skip(begin>0 ? begin-1 : begin);
        options.limit(end - begin);
        bsoncxx::document::view  v;
        auto result = dB[col].find(v, options);
        std::string result_str = "";
        int total = 0;
        for(auto e : result){
            total++;
            result_str += bsoncxx::to_json(e) + ","; 
        }
        if(result_str.size() > 0)
            result_str.pop_back();
        result_str =  "{ \"total\": " + std::to_string(total) + 
                         ", \"content\":[" + result_str + "] }";
        return result_str;

    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return "{ \"total\": 0, \"content\":[] }";
    }
}
const std::string Mongo::find_filter_range(const std::string col, 
                                    const std::string filter,
                                    int begin, int end)
{
    std::lock_guard<std::mutex> lo(db_mutex);
    auto dB = client[DB_NAME];     
   
    BOOST_LOG_TRIVIAL(trace) << __func__ << " begin:" << begin << " end:" << end
                            << " col:" << col <<" filter:" << filter;
    try{
        mongocxx::options::find options {};
        options.skip(begin>0 ? begin-1 : begin);
        options.limit(end - begin);
        auto result = dB[col].find(bsoncxx::from_json(filter),options);
        std::string result_str = "";
        int total = 0;
        for(auto e : result){
            total++;
            result_str += bsoncxx::to_json(e) + ","; 
        }
        if(result_str.size() > 0)
            result_str.pop_back();
        return "{ \"total\": " + std::to_string(total) + 
                         ", \"content\":[" + result_str + "] }";
    }catch(std::exception& e){
        BOOST_LOG_TRIVIAL(trace) << "Exception:" << e.what() ;
        return "{ \"total\": 0, \"content\":[] }";
    }
}
