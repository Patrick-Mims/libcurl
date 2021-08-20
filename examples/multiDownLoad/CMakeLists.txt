cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

#set(HEADERS "include/curl/curl.h" "include/curl/multi.h")

add_executable(main src/main.c)

target_link_libraries(main -L/usr/local/lib -lcurl)

#-L/usr/local/lib -lcurl
