#include <fmt/core.h>

#include "day02.h"

int main() {
    auto parsed_games = parse_games(INPUT);
    fmt::print("Part I : Valid games count = {}\n", valid_games_count(parsed_games));
    fmt::print("Part II: Power set sum = {}\n", power_set_cubes(parsed_games));
}