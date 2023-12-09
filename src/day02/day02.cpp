#include "day02.h"

#include <scn/scn.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <ios>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>


auto valid_games_count(const std::vector<Game> games) -> std::size_t {
    std::vector<Game> valid_games;
    std::copy_if(games.begin(), games.end(), std::back_insert_iterator(valid_games), [](const Game& game) {
        for (const auto& set : game.sets) {
            if (!is_possible_config(set.colors.red, set.colors.green, set.colors.blue)) {
                return false;
            }
        }
        return true;
    });

    std::size_t sum {};
    std::for_each(valid_games.begin(), valid_games.end(), [&sum](const Game& game) { sum += game.id; });

    return sum;
}

auto parse_games(std::string_view text) -> std::vector<Game> {
    std::vector<Game> games;
    std::istringstream stream(std::string(text), std::ios_base::in);
    std::string line;

    while (std::getline(stream, line)) {
        games.emplace_back(parse_game(line));
    }

    return games;
}

auto parse_game(std::string_view line) -> Game {
    unsigned int id;
    auto result = scn::scan(line, "Game {}:", id);
    auto remaining_line = result.range_as_string_view();
    auto sets = parse_sets(remaining_line);

    return Game {.id = id, .sets = sets};
}

auto parse_sets(std::string_view sets_string) -> std::vector<GameSet> {
    std::vector<std::string> sets_string_vec;
    std::vector<GameSet> parsed_sets;
    boost::split(sets_string_vec, sets_string, boost::is_any_of(";"));

    std::for_each(
        sets_string_vec.begin(), sets_string_vec.end(), [&parsed_sets](const std::string& set_string) {
            parsed_sets.push_back(parse_set(set_string));
        });

    return parsed_sets;
}


auto parse_set(const std::string& set_str) -> GameSet {
    GameSet set;
    std::vector<std::string> colors;
    boost::split(colors, set_str, boost::is_any_of(","));

    for (const auto& color_description : colors) {
        std::string color;
        unsigned int count {}, r {}, g {}, b {};
        auto result = scn::scan(color_description, "{} {}", count, color);

        if (color == "red") {
            set.colors.red += count;
        } else if (color == "green") {
            set.colors.green += count;
        } else if (color == "blue") {
            set.colors.blue += count;
        } else {
            throw std::runtime_error("parse_set() got an unknown color!");
        }
    }
    return set;
}

auto is_possible_config(unsigned int red, unsigned int green, unsigned int blue) noexcept -> bool {
    // checks if the given configuration constitutes a valid draw from the given configuration
    bool color_count_check = (red <= 12) && (green <= 13) && (blue <= 14);
    bool cubes_count_check = (red + green + red) <= (12 + 13 + 14);
    return color_count_check && cubes_count_check;
}

auto power_set_cubes(const std::vector<Game>& games) -> std::size_t {
    std::size_t sum {};
    for (const auto& game : games) {
        Colors max_colors = max_colors_in_game(game);
        sum += max_colors.red * max_colors.green * max_colors.blue;
    }

    return sum;
}

auto max_colors_in_game(const Game& game) -> Colors {
    auto max_red =
        std::max_element(game.sets.begin(), game.sets.end(), [](const GameSet& a, const GameSet& b) {
            return a.colors.red < b.colors.red;
        });

    auto max_green =
        std::max_element(game.sets.begin(), game.sets.end(), [](const GameSet& a, const GameSet& b) {
            return a.colors.green < b.colors.green;
        });

    auto max_blue =
        std::max_element(game.sets.begin(), game.sets.end(), [](const GameSet& a, const GameSet& b) {
            return a.colors.blue < b.colors.blue;
        });

    return Colors {
        .red = max_red->colors.red, .green = max_green->colors.green, .blue = max_blue->colors.blue};
}