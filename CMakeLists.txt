cmake_minimum_required(VERSION 3.10)

project (simple-pkcs7 C)

#gcc include
#include_directories("$ENV{UCRT_HOME}/include")

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pkcs.c
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/pkcs.h
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# test
#include(CTest)
#enable_testing()
#add_subdirectory(test)