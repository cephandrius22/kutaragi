
include_directories("../include" "../src")

add_executable(test_vec test_vec.cpp)

add_test(NAME test_vec COMMAND test_vec)