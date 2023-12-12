add_library(day03 day03.cpp)
add_executable(day03-main main.cpp)
target_link_libraries(day03-main day03)

find_package(GTest CONFIG REQUIRED)
add_executable(day03-test test.cpp day03.cpp)
target_link_libraries(day03-test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main day03)

gtest_discover_tests(day03-test)