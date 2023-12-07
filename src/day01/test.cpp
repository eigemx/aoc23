#include <gtest/gtest.h>

#include "day01.h"

constexpr std::string_view TEST_INPUT = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)"sv;

constexpr std::string_view TEST_INPUT2 = R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)"sv;

TEST(PartOneTest, BasicAssertions) { EXPECT_EQ(sum_numbers(TEST_INPUT, number_in_line_part_one), 142); }
TEST(PartTwoTest, BasicAssertions) { EXPECT_EQ(sum_numbers(TEST_INPUT2, number_in_line_part_two), 281); }
