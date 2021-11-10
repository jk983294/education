cmake_minimum_required(VERSION 3.16)

project(education)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

SET(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall -Werror")
#SET(CMAKE_CXX_FLAGS "-std=c++17 -O3 -s -Wall -Werror")

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

include_directories(include)
include_directories(SYSTEM /opt/3rd/common/include)
include_directories(/opt/version/latest/ornate/include)

link_directories(/opt/3rd/common/lib)

add_subdirectory(src)