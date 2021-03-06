cmake_minimum_required(VERSION 3.10)
project(iptv_api)
#set(CMAKE_CXX_COMPILER  "/usr/bin/clang++-10")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions( 
                 -fdiagnostics-show-location=every-line
                 -DBOOST_LOG_DYN_LINK=1
                 -Wall
                 -DNDEBUG
                 #-g
                 )

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} 
    ${SRC_LIST} 
    )

target_link_libraries(${PROJECT_NAME} 
    /home/karim/src/served/lib/libserved.a
    -lpthread
    -ldl
    )
# Check Boost
find_package(Boost COMPONENTS system log log_setup REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )

set(CMAKE_MODULE_PATH /usr/local/lib/cmake )
find_package(LIBMONGOCXX REQUIRED)
target_link_libraries(${PROJECT_NAME} ${LIBMONGOCXX_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)
target_link_libraries(${PROJECT_NAME} ${CURLPP_LIBRARIES} )
target_include_directories(${PROJECT_NAME} PUBLIC ${CURLPP_INCLUDE_DIRS})


add_custom_target(copy ALL 
    COMMAND strip iptv_api && cp -f iptv_* /opt/sms/bin
    COMMENT "Copy to /opt/sms/bin"
    DEPENDS ${PROJECT_NAME}
    )
# Check served packege

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SERVED REQUIRED served )
#target_include_directories(${PROJECT_NAME} PUBLIC ${SERVED_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${SERVED_LIBRARIES})
#add_custom_command(TARGET ${PROJECT_NAME} COMMAND sh -c "./main")

#enable_testing()
#add_subdirectory(test)
