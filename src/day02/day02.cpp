#include "day02.h"

#include <scn/scn.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <vector>

auto Game::is_valid() const noexcept -> bool {
    return colors.red <= 12 && colors.green <= 13 && colors.blue <= 14;
}

auto Game::operator+(const Game& other) noexcept -> Game& {
    this->colors.red += other.colors.red;
    this->colors.green += other.colors.green;
    this->colors.blue += other.colors.blue;
    return *this;
}

auto parse_and_sum(std::string_view games) -> unsigned int {
    // parses a list of games entries and returns the sum of valid games.
    std::size_t sum {0};
    const char* it = games.begin();

    while (it != games.end()) {
        const char* line_end = std::find(it, games.end(), '\n');
        auto line = std::string_view(it, line_end);
        auto game = parse_game(line);

        if (game.is_valid()) {
            sum += game.id;
        }

        if (line_end == games.end()) {
            break;
        }

        it = line_end + 1;
    }
    return sum;
}

auto parse_game(std::string_view line) -> Game {
    Game game;
    auto result = scn::scan(line, "Game {}:", game.id);

    auto remaining_line = result.range_as_string_view();
    game = game + parse_sets(remaining_line);

    return game;
}

auto parse_sets(std::string_view sets_string) -> Game {
    Game game {};

    std::vector<std::string> sets;
    boost::split(sets, sets_string, boost::is_any_of(";"));

    for (const auto& set : sets) {
        game = game + parse_set(set);
    }

    return game;
}

auto parse_set(const std::string& set_str) -> Game {
    unsigned int red {}, green {}, blue {};
    std::vector<std::string> colors;

    boost::split(colors, set_str, boost::is_any_of(","));

    for (const auto& color_description : colors) {
        std::string color;
        unsigned int count {};
        auto result = scn::scan(color_description, "{} {}", count, color);

        if (color == "red") {
            red += count;
        } else if (color == "green") {
            green += count;
        } else {
            blue += count;
        }
    }
    return Game {.id = 0, .colors {.red = red, .green = green, .blue = blue}};
}