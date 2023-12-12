find_package(scn CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_library(day04 day04.cpp)
target_link_libraries(day04 PRIVATE scn::scn Boost::boost fmt::fmt-header-only)


add_executable(day04-main main.cpp)
target_link_libraries(day04-main day04 fmt::fmt-header-only)

find_package(GTest CONFIG REQUIRED)
add_executable(day04-test test.cpp)
target_link_libraries(day04-test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main day04)

gtest_discover_tests(day04-test)