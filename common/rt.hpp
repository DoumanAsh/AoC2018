#pragma once

#include "time.hpp"

#include <type_traits>
#include <iostream>

namespace rt {

template <typename Fn1, typename Fn2, typename ResType1 = std::invoke_result_t<Fn1>, typename ResType2 = std::invoke_result_t<Fn2>>
int main(int argc, char * argv[], Fn1 part1, Fn2 part2) {
    static_assert(std::is_invocable<Fn1>::value, "Fn1 must be callable and accept no argument");
    static_assert(std::is_invocable<Fn2>::value, "Fn2 must be callable and accept no argument");

    static_assert(std::is_same<ResType1, int>::value, "Fn1 must return int");
    static_assert(std::is_same<ResType2, int>::value, "Fn2 must return int");

    if (argc < 2) {
        std::cerr << "Insufficient argument. Please specify part number\n";
        return 1;
    }

    std::cin >> (std::showpos);
    if (strncmp(argv[1], "1", 1) == 0) {
        return utils::measure(part1);
    } else if (strncmp(argv[1], "2", 1) == 0) {
        return utils::measure(part2);
    } else {
        std::cerr << "Unknown part '" << argv[1] << "'. Valid values: 1, 2\n";
        return 1;
    }

    return 0;
}

}
