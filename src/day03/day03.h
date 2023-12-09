#pragma once

#include <cctype>
#include <cstddef>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

class Grid {
  public:
    Grid(std::string grid_text);
    Grid(std::string_view grid_text) : Grid(std::string(grid_text)) {}

    auto sum_non_symbols() -> std::size_t;
    auto sum_gear_ratios() -> std::size_t;

  private:
    auto at(std::size_t i, std::size_t j) const noexcept -> char;
    auto can_go_left(std::size_t j) const noexcept -> bool;
    auto can_go_right(std::size_t j) const noexcept -> bool;
    auto get_surrounding_numbers(std::size_t i, std::size_t j) const noexcept
        -> std::unordered_set<std::size_t>;
    auto search_at(std::size_t i, std::size_t j) const noexcept -> std::optional<std::size_t>;

    std::vector<std::string> _grid;
    std::vector<std::size_t> _numbers;
};