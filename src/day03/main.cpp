#include <iostream>
#include <string_view>

#include "day03.h"
#include "input.h"

int main() {
    auto grid = Grid(INPUT);
    std::cout << "Part I: sum = " << grid.sum_non_symbols() << std::endl;
    std::cout << "Part II: sum = " << grid.sum_gear_ratios() << std::endl;
}