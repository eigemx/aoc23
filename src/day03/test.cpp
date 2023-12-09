#include <gtest/gtest.h>

#include "day03.h"

constexpr std::string_view TEST_INPUT = R"(467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..)";

TEST(PartOneTest, BasicAssertions) {
    Grid grid(TEST_INPUT);
    EXPECT_EQ(grid.sum_non_symbols(), 4361);
}

TEST(PartTwoTest, BasicAssertions) {
    Grid grid(TEST_INPUT);
    EXPECT_EQ(grid.sum_gear_ratios(), 467835);
}