#include "day02.h"

#include <scn/scn.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>


auto inline is_possible_config(unsigned int red, unsigned int green, unsigned int blue) noexcept -> bool {
    bool color_count_check = (red <= 12) && (green <= 13) && (blue <= 14);
    bool cubes_count_check = (red + green + red) <= (12 + 13 + 14);
    return color_count_check && cubes_count_check;
}

auto parse_and_sum(std::string_view games) -> unsigned int {
    // parses a list of games entries and returns the sum of valid games.
    std::size_t sum {0};
    const char* it = games.begin();

    while (it != games.end()) {
        const char* line_end = std::find(it, games.end(), '\n');
        auto line = std::string_view(it, line_end);
        auto [id, is_possible] = is_game_possible(line);

        if (is_possible) sum += id;
        if (line_end == games.end()) break;

        it = line_end + 1;
    }
    return sum;
}

auto is_game_possible(std::string_view line) -> std::pair<unsigned int, bool> {
    unsigned int id;
    auto result = scn::scan(line, "Game {}:", id);
    auto remaining_line = result.range_as_string_view();
    bool is_possible = are_sets_possible(remaining_line);

    return std::make_pair(id, is_possible);
}

auto are_sets_possible(std::string_view sets_string) -> bool {
    std::vector<std::string> sets;
    boost::split(sets, sets_string, boost::is_any_of(";"));

    for (const auto& set : sets) {
        if (!is_set_possible(set)) {
            return false;
        }
    }

    return true;
}

auto is_set_possible(const std::string& set_str) -> bool {
    std::vector<std::string> colors;
    boost::split(colors, set_str, boost::is_any_of(","));

    for (const auto& color_description : colors) {
        std::string color;
        unsigned int count {}, r {}, g {}, b {};
        auto result = scn::scan(color_description, "{} {}", count, color);

        if (color == "red") {
            r += count;
        } else if (color == "green") {
            g += count;
        } else if (color == "blue") {
            b += count;
        } else {
            throw std::runtime_error("parse_set() got an unknown color!");
        }

        if (!is_possible_config(r, g, b)) {
            return false;
        }
    }

    return true;
}