#include <iostream>
#include <cstring>
#include <array>
#include <bitset>
#include <vector>

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
    ++result;
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

void set_fabric(const std::vector<Claim>& claims) noexcept {
    for (const auto& claim : claims) {
        for (size_t x = claim.coords.x + 1; x < claim.size.x; x++) {
            for (size_t y = claim.coords.y + 1; y < claim.size.y; y++) {
                FABRIC[x][y]++;
            }
        }
    }
}

int part1() {
    auto claims = get_claims();

    return 0;
}

int part2() {

    return 0;
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cerr << "Insufficient argument. Please specify part number\n";
        return 1;
    }

    std::cin >> (std::showpos);
    if (strncmp(argv[1], "1", 1) == 0) {
        return part1();
    } else if (strncmp(argv[1], "2", 1) == 0) {
        return part2();
    } else {
        std::cerr << "Unknown part '" << argv[1] << "'. Valid values: 1, 2\n";
        return 1;
    }
}
