project(RedisClient)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "-g -pthread")

include_directories(
        /usr/local/include
        /usr/include
)

link_directories(
        /usr/local/lib
        /usr/lib
)

set(EXECUTABLE_OUTPUT_PATH /home/zhu/RedisClient/bin)

add_subdirectory(src)