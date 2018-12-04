#include "../common/rt.hpp"

#include <iostream>
#include <cstring>
#include <array>
#include <bitset>
#include <vector>
#include <algorithm>
#include <type_traits>

#include "claim.hpp"

enum class ClaimState: unsigned char {
    None = 0,
    Single,
    Multiple
};

ClaimState& operator++(ClaimState &self) {
    switch (self) {
        case ClaimState::None: self = ClaimState::Single; break;
        case ClaimState::Single: self = ClaimState::Multiple; break;
        case ClaimState::Multiple: self = ClaimState::Multiple; break;
    }

    return self;
}

ClaimState operator++(ClaimState &self, int) {
    ClaimState result = self;
    ++self;
    return result;
}

constexpr size_t FABRIC_INCHES = 1000;
using Fabric = std::array<std::array<ClaimState, FABRIC_INCHES>, FABRIC_INCHES>;

static Fabric FABRIC;

std::vector<Claim> get_claims() {
    std::vector<Claim> result;

    for (std::string line; std::getline(std::cin, line);) {
        auto claim = Claim::parse(line);

        if (!claim.has_value()) {
            std::cerr << "Invalid claim '" << line << "'\n";
            exit(1);
        }

        result.emplace_back(std::move(*claim));
    }

    return result;
}

template<typename Fn>
void for_each_claim(const std::vector<Claim>& claims, Fn cb) {
    for_each_claim(claims, cb, [](int) { return true; });
}


/**
 * Iterates over fabric state accordingly to claims.
 *
 * @param claims Obviously claims.
 * @param cb Callback to call on each state.
 * @param cb_end Callback to call when claim is ended. Return false to stop iteration.
 */
template<typename Fn, typename FnEnd>
void for_each_claim(const std::vector<Claim>& claims, Fn cb, FnEnd cb_end) {
    static_assert(std::is_invocable<Fn, ClaimState&>::value, "Fn must be callable and accept &ClaimState as argument");
    static_assert(std::is_invocable<FnEnd, int>::value, "Fn must be callable and accept int as argument");

    for (const auto& claim : claims) {
        size_t x = claim.coords.x + 1;
        size_t x_end = x + claim.size.x;
        for (; x < x_end; x++) {
            size_t y = claim.coords.y + 1;
            size_t y_end = y + claim.size.y;
            for (; y < y_end; y++) {
                cb(FABRIC[x][y]);
            }
        }

        if (!cb_end(claim.id)) {
            break;
        }
    }
}

int part1() {
    const auto claims = get_claims();
    for_each_claim(claims, [](ClaimState& state) { state++; });

    size_t overlap_size = 0;
    for (const auto& fabrics : FABRIC) {
        overlap_size += std::count_if(fabrics.cbegin(), fabrics.cend(), [](ClaimState state) { return state == ClaimState::Multiple; });
    }

    std::cout << "Result(Part1): " << overlap_size << "\n";

    return 0;
}

int part2() {
    const auto claims = get_claims();
    for_each_claim(claims, [](ClaimState& state) { state++; });

    size_t overlap_size = 0;
    for_each_claim(claims,
                   [&overlap_size](ClaimState& state) { overlap_size += static_cast<size_t>(state == ClaimState::Multiple); },
                   [&overlap_size](int id) {
                       if (overlap_size == 0) {
                           std::cout << "Result(Part2): " << id << "\n";
                           return false;
                       } else {
                           overlap_size = 0;
                           return true;
                       }
    });

    if (overlap_size != 0) {
        std::cout << "Result(Part2): ERROR CANNOT FIND!\n";
    }

    return 0;
}

int main(int argc, char * argv[]) {
    return rt::main(argc, argv, part1, part2);
}
