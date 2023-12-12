#include "day04.h"

#include <scn/scn.h>

#include <algorithm>
#include <array>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cmath>
#include <sstream>
#include <string>


auto count_points(std::string_view input) -> std::size_t {
    std::size_t count {0};
    std::istringstream ss {std::string(input)};
    std::string line;

    while (std::getline(ss, line)) {
        auto wins = count_winning_cards_we_have(line);
        count += (wins == 0) ? 0 : std::pow(2, wins - 1);
    }

    return count;
}

auto count_winning_cards_we_have(const std::string& line) -> std::size_t {
    auto card = parse_card_line(line);
    std::size_t winning_cards_count {0};

    for (const auto& winning_number : card.winning_numbers) {
        if (card.numbers_we_have.contains(winning_number)) {
            winning_cards_count++;
        }
    }
    return winning_cards_count;
}

auto parse_card_line(const std::string& line) -> Card {
    std::size_t card_id;
    auto res = scn::scan(line, "Card {}: ", card_id);

    std::vector<std::string> numbers;
    boost::split(numbers, res.range_as_string_view(), boost::is_any_of("|"));

    const auto& winning_numbers_str = numbers[0];
    const auto& numbers_we_have_str = numbers[1];

    std::vector<std::string> winning_numbers_str_split, number_we_have_str_split;
    boost::split(
        winning_numbers_str_split, winning_numbers_str, boost::is_any_of(" "), boost::token_compress_on);
    boost::split(
        number_we_have_str_split, numbers_we_have_str, boost::is_any_of(" "), boost::token_compress_on);

    std::unordered_set<std::size_t> winning_numbers, numbers_we_have;

    std::for_each(winning_numbers_str_split.begin(),
                  winning_numbers_str_split.end(),
                  [&winning_numbers](const auto& num) {
                      if (!num.empty()) winning_numbers.insert(std::stoi(num));
                  });

    std::for_each(number_we_have_str_split.begin(),
                  number_we_have_str_split.end(),
                  [&numbers_we_have](const auto& num) {
                      if (!num.empty()) numbers_we_have.insert(std::stoi(num));
                  });

    return Card {.id = card_id, .winning_numbers = winning_numbers, .numbers_we_have = numbers_we_have};
}