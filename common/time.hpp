#pragma once

#include <iostream>
#include <type_traits>
#include <chrono>

namespace utils {

template <typename Fn, typename ResType = std::invoke_result_t<Fn>>
auto measure(Fn fn) -> ResType {
    static_assert(std::is_invocable<Fn>::value, "Fn must be callable and accept no argument");

    constexpr bool is_void = std::is_void<ResType>::value;

    typedef typename std::conditional<is_void, char, ResType>::type result_t;

    result_t result;

    const auto before = std::chrono::high_resolution_clock::now();
    if constexpr (is_void) {
        fn();
    } else {
        result = fn();
    }
    const auto after = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> timing = after - before;
    std::cout << "Execution time: " << timing.count() << "ms\n";

    if constexpr (is_void) {
        return;
    } else {
        return result;
    }
}

} //time
