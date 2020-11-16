#pragma once

#include <exception>
#include <iostream>
#define  QUERY_SIZE 10
#include <mongocxx/client.hpp>
#include <mongocxx/pool.hpp>
#include "config.hpp"

class Mongo {
    private:
        bool db_valid;
        mongocxx::client client{mongocxx::uri{SERVER}};
        mongocxx::database db;
    public:
         Mongo(); 
         void fill_defauls() ;
         bool count(const std::string& col, const std::string& filter);
         bool exists(const std::string& col, const std::string& filter);
         bool exists_id(const std::string& col, int64_t id);
         bool insert(const std::string& col, const std::string& filter);
         bool remove_mony(const std::string& col, const std::string& filter);
         bool remove_id(const std::string& col, int64_t id);
         bool replace_id(const std::string& col, int64_t id,
                 const std::string& doc);
         bool insert_if_not_exists(const std::string& col,
                 const std::string& filter,
                 const std::string& doc);
         bool insert_or_replace_id(const std::string& col, int64_t id,
                 const std::string& doc);
         bool replace(const std::string& col, const std::string& filter,
                 const std::string& doc);
         int64_t get_uniq_id();
         bool update_id(const std::string& col, int64_t id, const std::string& doc);
         std::string find_one(const std::string& col, const std::string& filter);
         std::string find_mony(const std::string& col, const std::string& filter);
         std::string find_id(const std::string& col, int64_t id);
         std::string find_range(const std::string& col,
                 int begin = 0, int end = QUERY_SIZE);
         std::string find_filter_range(const std::string& col,
                 const std::string& filter,
                 int begin = 0, int end = QUERY_SIZE);
};
