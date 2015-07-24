project(boundaries)
cmake_minimum_required(VERSION 2.8)

add_library(boundaries boundaries.hpp)
set_target_properties(boundaries PROPERTIES LINKER_LANGUAGE CXX)

add_executable(main main.cpp)
target_link_libraries(main boundaries)