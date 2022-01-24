cmake_minimum_required(VERSION 3.7...3.22)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(main VERSION 1.0 DESCRIPTION "CURL-QUEUE" LANGUAGES C)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set(SOURCE_FILES src/main.c)

add_library(curllib SHARED IMPORTED)
set_property(TARGET curllib PROPERTY IMPORTED_LOCATION "/usr/local/lib")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(main -lcurl)
