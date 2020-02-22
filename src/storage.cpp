#include "auth.hpp"
#include "storage.hpp"

extern MainStorage st;
void storage_setting(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_setting";
	CHECK_AUTH;
}
void storage_timeshift_setting(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_timeshift_setting";
	CHECK_AUTH;
}
void storage_timeshift_files(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_timeshift_files";
	CHECK_AUTH;
}
void storage_npvr_setting(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_npvr_setting";
	CHECK_AUTH;
}
void storage_npvr_files(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_npvr_files";
	CHECK_AUTH;
}
void storage_avod_import(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_avod_import";
	CHECK_AUTH;
}
void storage_avod_files(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_avod_files";
	CHECK_AUTH;
}
void storage_audio_book_import(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_audio_book_import";
	CHECK_AUTH;
}
void storage_audio_book_files(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_audio_book_files";
	CHECK_AUTH;
}
void storage_book_import(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_book_import";
	CHECK_AUTH;
}
void storage_book_files(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_book_files";
	CHECK_AUTH;
}
void storage_advertize_import(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_advertize_import";
	CHECK_AUTH;
}
void storage_advertize_files(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_advertize_files";
	CHECK_AUTH;
}
void storage_advertize_files_id(served::response &res, const served::request &req)
{
	BOOST_LOG_TRIVIAL(trace) << "Start storage_advertize_files_id";
	CHECK_AUTH;
}
