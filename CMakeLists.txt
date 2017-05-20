cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set (appName MComp)

# The executable is the first parameter followed by all the source and header files
#add_executable (mcomp-client client.cpp loader.h loader.cpp sma.cpp sma.h)

add_executable(client client.cpp)
add_executable(server server.cpp)

add_library(lmcomp loader.h loader.cpp sma.cpp sma.h snapshot.cpp SHMessage.cpp SHMessage.h)
target_link_libraries(client lmcomp)
target_link_libraries(server lmcomp)

# Add configuration file
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mcomp.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})