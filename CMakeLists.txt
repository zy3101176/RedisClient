cmake_minimum_required(VERSION 3.7)
project(RedisClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp redis_client.cpp redis_client.h)
add_executable(RedisClient ${SOURCE_FILES})
include_directories(/usr/local/include/hiredis/)
link_directories("/usr/local/lib/")
