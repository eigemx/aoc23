find_package(scn CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_library(day02 day02.cpp)
add_executable(day02-main main.cpp)

target_link_libraries(day02 scn::scn)
target_link_libraries(day02-main PRIVATE day02 fmt::fmt-header-only)

find_package(GTest CONFIG REQUIRED)
add_executable(day02-test test.cpp day02.cpp)
target_link_libraries(day02-test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main day02)

gtest_discover_tests(day02-test)