add_library(day01 day01.cpp)
add_executable(day01-main main.cpp)
target_link_libraries(day01-main PRIVATE day01 fmt::fmt-header-only)

find_package(GTest CONFIG REQUIRED)
add_executable(day01-test test.cpp day01.cpp)
target_link_libraries(day01-test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main day01)

enable_testing()
include(GoogleTest)
gtest_discover_tests(day01-test)