cmake_minimum_required(VERSION 3.9)

project(tests)
set(CMAKE_CXX_STANDARD 17)

include_directories("../include" "../src")

add_executable(test_vec test_vec.cpp)

add_test(NAME test_vec COMMAND test_vec)

add_executable(test_mat test_mat.cpp)

add_test(NAME test_mat COMMAND test_mat)