#include "day01.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

// clang-format off
// prepare string representation of digits
std::vector<std::string> str_numbers = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "1",   "2",   "3",     "4",    "5",    "6",   "7",     "8",     "9"};

std::map<std::string, int> num_str_to_int{
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"1", 1},
    {"2", 2},   {"3", 3},     {"4", 4},     {"5", 5},    {"6", 6},
    {"7", 7},   {"8", 8},     {"9", 9}};
// clang-format on


// part I sum function
[[nodiscard]] inline auto sum_numbers(std::string_view text) -> unsigned int;

// part II
[[nodiscard]] inline auto sum_numbers_part_two(std::string_view text) -> unsigned int;
[[nodiscard]] inline auto number_in_line(std::string_view line) -> unsigned int;
[[nodiscard]] inline auto first_number_in_line(std::string_view line) -> std::pair<int, const char*>;
[[nodiscard]] inline auto check_if(std::string_view num, std::string_view line) -> bool;

auto sum_numbers(std::string_view text) -> unsigned int {
    std::size_t sum {0};
    const char* it = text.begin();

    while (it != text.end()) {
        std::size_t counter {0};
        std::size_t first_idx {0}, second_idx {0};
        const char *first = nullptr, *second = nullptr;

        while (!std::isdigit(*it)) {
            it++;
            counter++;
        }

        first = it;
        first_idx = counter;

        while (*it != '\n' && it != text.end()) {
            if (std::isdigit(*it)) {
                second = it;
                second_idx = counter;
            }
            it++;
            counter++;
        }
        sum += ((*first - '0') * 10) + (*second - '0');
    }

    return sum;
}

auto sum_numbers_part_two(std::string_view text) -> unsigned int {
    std::size_t sum {0};
    const char* it = text.begin();

    while (it != text.end()) {
        auto line_end = std::find(it, text.end(), '\n');
        auto line = std::string_view(it, line_end);

        if (line_end == text.end()) {
            sum += number_in_line(line);
            break;
        }
        sum += number_in_line(line);
        it = line_end + 1;
    }
    return sum;
}

auto number_in_line(std::string_view line) -> unsigned int {
    auto [first_num, itr] = first_number_in_line(line);

    if (itr == line.end()) {
        return (first_num * 10) + first_num;
    }

    unsigned int second_number = 0;
    for (;;) {
        auto [num, ptr] = first_number_in_line(std::string_view(itr, line.end()));
        if (num == 0 && ptr == line.end()) break;
        second_number = num;
        itr = ptr;
    }

    return (first_num * 10) + (second_number != 0 ? second_number : first_num);
}

auto first_number_in_line(std::string_view line) -> std::pair<int, const char*> {
    static char initials[] = {'o', 't', 'f', 's', 'e', 'n', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    auto line_end = line.end();
    auto first_occ = std::find_first_of(line.begin(), line_end, std::begin(initials), std::end(initials));

    if (first_occ == line_end) {
        // we did not find any of the digits first character in the line
        return std::make_pair(0, line_end);
    }

    char ch = *first_occ;

    // Part of the line where we found the first char occurence, to the line end
    std::string_view line_part {first_occ, line_end};

    if (std::isdigit(ch)) return std::make_pair(ch - '0', first_occ + 1);

    switch (ch) {
        case 'o': {
            if (check_if("one"sv, line_part)) return std::make_pair(1, first_occ + 2);
            break;
        }
        case 't': {
            if (check_if("two"sv, line_part)) return std::make_pair(2, first_occ + 2);
            if (check_if("three"sv, line_part)) return std::make_pair(3, first_occ + 4);
            break;
        }
        case 'f': {
            if (check_if("four"sv, line_part)) return std::make_pair(4, first_occ + 3);
            if (check_if("five"sv, line_part)) return std::make_pair(5, first_occ + 3);
            break;
        }
        case 's': {
            if (check_if("six"sv, line_part)) return std::make_pair(6, first_occ + 2);
            if (check_if("seven"sv, line_part)) return std::make_pair(7, first_occ + 4);
            break;
        }
        case 'e': {
            if (check_if("eight"sv, line_part)) return std::make_pair(8, first_occ + 4);
            break;
        }
        case 'n': {
            if (check_if("nine"sv, line_part)) return std::make_pair(9, first_occ + 3);
            break;
        }
    }
    return first_number_in_line(std::string_view(first_occ + 1, line.end()));
}

auto check_if(std::string_view num, std::string_view line) -> bool {
    if (line.size() < num.size()) return false;
    return line.substr(0, num.size()) == num;
}

int main() {
    std::cout << "Part I sum = " << sum_numbers(INPUT) << std::endl;
    std::cout << "Part II sum = " << sum_numbers_part_two(INPUT) << std::endl;
}