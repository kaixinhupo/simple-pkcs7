cmake_minimum_required(VERSION 3.10)

include_directories("$ENV{UCRT_HOME}/include")

add_executable(t test.c ../pkcs.c)

target_link_libraries(t cunit)

#add_test(NAME test_run COMMAND my_test)