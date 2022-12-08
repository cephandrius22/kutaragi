
include_directories("../include" "../src")

add_executable(mytest test.cpp)

add_test(NAME mytest COMMAND mytest)