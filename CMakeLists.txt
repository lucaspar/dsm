cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set (appName MComp)
set_source_files_properties( snapshot.cpp PROPERTIES COMPILE_FLAGS "-fno-stack-protector" )

add_executable(client client.cpp)
add_executable(server server.cpp)
add_executable(snapshot snapshot.cpp)

add_library(lmcomp loader.h loader.cpp sma.cpp sma.h snapshot.cpp SHMessage.cpp SHMessage.h semun.h)
target_link_libraries(client lmcomp)
target_link_libraries(server lmcomp)
target_link_libraries(snapshot lmcomp)

# Add configuration file
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mcomp.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
