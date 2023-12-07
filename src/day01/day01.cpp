#include "day01.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

auto sum_numbers(std::string_view text, HandlerFunc* func) -> unsigned int {
    std::size_t sum {0};
    const char* it = text.begin();

    while (it != text.end()) {
        auto line_end = std::find(it, text.end(), '\n');
        auto line = std::string_view(it, line_end);

        if (line_end == text.end()) {
            sum += func(line);
            break;
        }
        sum += func(line);
        it = line_end + 1;
    }
    return sum;
}

auto number_in_line_part_one(std::string_view line) -> unsigned int {
    auto first = std::find_if(line.begin(), line.end(), [](char ch) { return std::isdigit(ch); });
    if (first == line.end()) {
        std::cerr << "Couldn't find a number in " << line << std::endl;
        return 0;
    }

    auto second = std::find_if(line.rbegin(), line.rend(), [](char ch) { return std::isdigit(ch); });

    return (((*first) - '0') * 10) + ((*second) - '0');
}

auto number_in_line_part_two(std::string_view line) -> unsigned int {
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