#pragma onc;

#include <iostream>
#include <boost/log/trivial.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/options/client.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#define  QUERY_SIZE 10


class Mongo {
    public:
        static void fill_defauls();
        static bool exists(const std::string col, const std::string filter);
        static bool exists_id(const std::string col, int id);
        static bool insert(const std::string col, const std::string filter);
        static bool remove(const std::string col, const std::string filter);
        static bool remove_by_id(const std::string col, int id);
        static bool replace_by_id(const std::string col, int id, 
                                    const std::string doc);
        static bool replace(const std::string col, const std::string filter, 
                                    const std::string doc);
        static int get_uniq_id();
        static const std::string find_one(const std::string col, const std::string filter);
        static const std::string find_id(const std::string col, int id);
        static const std::string find_range(const std::string col, 
                                    int begin = 0, int end = QUERY_SIZE);
        static const std::string find_filter_range(const std::string col, 
                                    const std::string filter,
                                    int begin = 0, int end = QUERY_SIZE);
        static void info();
};
