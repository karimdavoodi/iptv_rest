cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(QT_QMAKE_EXECUTABLE "/usr/bin/qmake")

file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")
list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")
project(test_api)
add_test(api ${PROJECT_NAME})
aux_source_directory(. TEST_LIST)
add_executable(${PROJECT_NAME} ${TEST_LIST} ${SRCS} )
target_link_libraries(${PROJECT_NAME} pthread )
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )

# Check served packege
find_package(PkgConfig REQUIRED)
pkg_check_modules(SERVED REQUIRED served )
target_include_directories(${PROJECT_NAME} PUBLIC ${SERVED_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SERVED_LIBRARIES})
