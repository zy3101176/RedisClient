project(RedisClient)
aux_source_directory(. SRC_LIST)
aux_source_directory(./dir SRC_DIR_LIST)
list(APPEND SRC_LIST ${SRC_DIR_LIST})
add_executable(RedisClient ${SRC_LIST})
target_link_libraries(RedisClient
libhiredis.so)
