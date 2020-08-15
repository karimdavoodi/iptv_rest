#pragma once

#include <iostream>
#define  QUERY_SIZE 10
#define LOG(level) BOOST_LOG_TRIVIAL(level) << "[" << __func__ << ":" <<__LINE__ << "] " 

namespace Mongo {
    void fill_defauls();
    bool exists(const std::string col, const std::string filter);
    bool exists_id(const std::string col, int64_t id);
    bool insert(const std::string col, const std::string filter);
    bool insert_id(const std::string col, int64_t id, 
            const std::string doc);
    bool remove_mony(const std::string col, const std::string filter);
    bool remove_id(const std::string col, int64_t id);
    bool replace_id(const std::string col, int64_t id, 
            const std::string doc);
    bool insert_or_replace_id(const std::string col, int64_t id, 
            const std::string doc);
    bool replace(const std::string col, const std::string filter, 
            const std::string doc);
    int64_t get_uniq_id();
    bool update_id(const std::string col, int64_t id, const std::string doc);
    const std::string find_one(const std::string col, const std::string filter);
    const std::string find_mony(const std::string col, const std::string filter);
    const std::string find_id(const std::string col, int64_t id);
    const std::string find_range(const std::string col, 
            int begin = 0, int end = QUERY_SIZE);
    const std::string find_filter_range(const std::string col, 
            const std::string filter,
            int begin = 0, int end = QUERY_SIZE);
};
