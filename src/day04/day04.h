#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

struct Card {
    std::size_t id;
    std::unordered_set<std::size_t> winning_numbers, numbers_we_have;
};

auto count_points(std::string_view input) -> std::size_t;
auto count_winning_cards_we_have(const std::string& input) -> std::size_t;
auto parse_card_line(const std::string& line) -> Card;