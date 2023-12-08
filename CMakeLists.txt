cmake_minimum_required(VERSION 3.11)

project (
  aoc23
  DESCRIPTION "Advent of Code 2023 in C++20"
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(fmt CONFIG REQUIRED)
  
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# day 01
add_subdirectory(src/day01)

# day 02
add_subdirectory(src/day02)