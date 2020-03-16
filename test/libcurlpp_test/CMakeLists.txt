cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

project(test_api)

add_executable(${PROJECT_NAME} test_api.cpp )
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCURLPP REQUIRED curlpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBCURLPP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBCURLPP_LIBRARIES})

