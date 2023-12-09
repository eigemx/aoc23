#include "day03.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>

auto inline is_period(char ch) { return ch == '.'; }
auto inline is_symbol(char ch) { return !std::isdigit(ch) && !is_period(ch); }


Grid::Grid(std::string grid_text) {
    std::istringstream stream(grid_text);
    std::string line;

    while (std::getline(stream, line)) {
        _grid.push_back(line);
    }

#ifndef NDEBUG
    assert(_grid.size() > 0 && "No lines were read from input");

    auto len = _grid.begin()->size();
    assert(std::all_of(
               _grid.begin(), _grid.end(), [&len](const std::string& str) { return str.size() == len; }) &&
           "Not all lines have the same length!");

#endif
}

auto Grid::at(std::size_t i, std::size_t j) const -> char { return _grid[i][j]; }

auto Grid::can_go_left(std::size_t j) const -> bool { return j > 0; }
auto Grid::can_go_right(std::size_t j) const -> bool { return j < _grid.size() - 1; }


auto Grid::sum_non_symbols() -> std::size_t {
    const auto gsize = _grid.size();

    for (std::size_t i = 0; i < gsize; ++i) {
        for (std::size_t j = 0; j < gsize; ++j) {
            if (is_symbol(at(i, j))) {
                auto numbers = get_surrounding_numbers(i, j);
                std::copy(numbers.begin(), numbers.end(), std::inserter(_numbers, _numbers.end()));
            }
        }
    }
    return std::accumulate(_numbers.begin(), _numbers.end(), 0);
}

auto Grid::get_surrounding_numbers(std::size_t i, std::size_t j) const noexcept -> std::vector<std::size_t> {
    // we need to check in four directions (north, south, east, west) (if possible)
    // we also need to check diagonal neigbors to the symbol
    std::vector<std::size_t> numbers;

    auto north = search_at(i - 1, j);
    auto east = search_at(i, j + 1);
    auto south = search_at(i + 1, j);
    auto west = search_at(i, j - 1);

    auto north_east = search_at(i - 1, j + 1);
    auto north_west = search_at(i - 1, j - 1);
    auto south_east = search_at(i + 1, j + 1);
    auto south_west = search_at(i + 1, j - 1);

    const std::vector<std::optional<std::size_t>> optional_values {
        north, east, south, west, north_east, north_west, south_east, south_west};

    std::for_each(
        optional_values.begin(), optional_values.end(), [&numbers](const std::optional<std::size_t> opt) {
            if (opt.has_value()) {
                numbers.push_back(opt.value());
            };
        });

    return numbers;
}

auto Grid::search_at(std::size_t i, std::size_t j) const noexcept -> std::optional<std::size_t> {
    // check if any of the i and j combinations got us outside of the grid limits
    auto glen = _grid.size() - 1;
    if ((i < 0) || (j < 0) || (i > glen) || (j > glen)) return std::nullopt;
    if (!std::isdigit(at(i, j))) return std::nullopt;

    // we found a digit, but is it the start of the neighbor number?
    auto num_begin = j, num_end = j;
    while (can_go_left(num_begin) && std::isdigit(at(i, num_begin - 1))) --num_begin;
    while (can_go_right(num_end) && std::isdigit(at(i, num_end + 1))) ++num_end;

    return std::stoi(_grid[i].substr(num_begin, num_end - num_begin + 1));
}
