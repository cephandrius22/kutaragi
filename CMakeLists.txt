cmake_minimum_required(VERSION 3.9)

set(CMAKE_DEBUG_POSTFIX d)

project(kutaragi)
set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)

add_executable(kutaragi src/main.cpp include/vec.h include/triangle.h include/matrix.h)
set_target_properties(kutaragi PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
# target_compile_options(kutaragi PUBLIC -Wall -Wextra -Wpedantic -Werror)


include_directories(${SDL2_INCLUDE_DIRS} include)
target_link_libraries(kutaragi ${SDL2_LIBRARIES})

enable_testing()
add_subdirectory(tests)
