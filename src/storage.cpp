#include <filesystem>
#include "auth.hpp"
#include "mongo_driver.hpp"
#include "util.hpp"
#include "storage.hpp"

void storage_setting_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID1_COL("storage_setting");
}
void storage_setting_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID1_COL("storage_setting");
}
void storage_contents_types_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("storage_contents_types");
}
void storage_contents_types_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_contents_types");
}
void storage_contents_types_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_contents_types");
}
void storage_contents_types_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_contents_types");
}
void storage_platforms_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("storage_platforms");
}
void storage_platforms_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_platforms");
}
void storage_platforms_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_platforms");
}
void storage_platforms_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_platforms");
}
void storage_categories_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("storage_categories");
}
void storage_categories_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_categories");
}
void storage_categories_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_categories");
}
void storage_categories_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_categories");
}
void storage_info_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("storage_info");
}
void storage_info_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_info");
}
void storage_info_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_info");
}
void storage_info_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_info");
}
void storage_media_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    SEND_ID_FILE(MEDIA_PATH, "media", ZIP);
}
void storage_media_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE(MEDIA_PATH, "media", ZIP);
}
void storage_media_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE(MEDIA_PATH, "media", ZIP);
}
void storage_media_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_FILE(MEDIA_PATH, "media", ZIP);
}
void storage_poster_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    SEND_ID_FILE(MEDIA_PATH, "poster", ZIP);
}
void storage_poster_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE(MEDIA_PATH, "poster", ZIP);
}
void storage_poster_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE(MEDIA_PATH, "poster", ZIP);
}
void storage_poster_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_FILE(MEDIA_PATH, "poster", ZIP);
}
void storage_subtitle_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    SEND_ID_FILE(MEDIA_PATH, "subtitle", ZIP);
}
void storage_subtitle_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE(MEDIA_PATH, "subtitle", ZIP);
}
void storage_subtitle_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    RECV_ID_FILE(MEDIA_PATH, "subtitle", ZIP);
}
void storage_subtitle_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_FILE(MEDIA_PATH, "subtitle", ZIP);
}
void storage_advertize_get(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    GET_ID_COL("storage_advertize");
}
void storage_advertize_put(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    PUT_ID_COL("storage_advertize");
}
void storage_advertize_post(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    POST_ID_COL("storage_advertize");
}
void storage_advertize_del(served::response &res, const served::request &req)
{
	CHECK_AUTH;
    DEL_ID_COL("storage_advertize");
}
