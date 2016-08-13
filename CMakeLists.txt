cmake_minimum_required(VERSION 2.8.11)

project(countLines)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE countLines.cc Directory.cc)

if(WIN32)
    set(SOURCE ${SOURCE} XGetopt.cpp)
endif()

add_executable (countLines ${SOURCE})