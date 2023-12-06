cmake_minimum_required(VERSION 3.11)

project (
  aoc23
  DESCRIPTION "Advent of Code 2023 in C++"
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_executable(day01 src/day01/day01.cpp)
