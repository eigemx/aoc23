#include <iostream>
#include <string_view>

#include "day03.h"
#include "input.h"

int main() {
    auto grid = Grid(INPUT);
    std::cout << grid.sum_non_symbols() << std::endl;
}