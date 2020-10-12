#pragma once
#define SERVER  "mongodb://0.0.0.0:27017"
#define DB_NAME "iptv"
#define MAX_QUERY_LEN 100
#define USER_RECORD_BASE_ID 100000
#define LIVE_INPUT_TYPE_NETWORK 3 
#define MEDIA_ROOT "/opt/sms/www/iptv/media/"
#define LOG(level) BOOST_LOG_TRIVIAL(level) << \
                    "\033[0;32m[" << __func__ << ":" <<__LINE__ << "]\033[0m "
