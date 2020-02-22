cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Check Json Include file
include(CheckIncludeFile)
check_include_file("/usr/include/nlohmann/json.hpp" HAVE_JSON_HPP)
if(NOT ${HAVE_JSON_HPP})
  message( FATAL_ERROR "json.hpp Not Found" )
endif()


set(QT_QMAKE_EXECUTABLE "/usr/bin/qmake")

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} )

target_link_libraries(${PROJECT_NAME} pthread )
# Check Boost
find_package(Boost COMPONENTS system log REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )
add_definitions(-DBOOST_LOG_DYN_LINK=1)
# Check served packege
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERVED REQUIRED served )
target_include_directories(${PROJECT_NAME} PUBLIC ${SERVED_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SERVED_LIBRARIES})

enable_testing()
add_subdirectory(test)
