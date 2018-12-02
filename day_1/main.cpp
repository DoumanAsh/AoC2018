#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

int part1() {
    int freq = 0;
    int mod = 0;

    while (std::cin >> mod) {
        freq += mod;
    }

    if (std::cin.eof()) {
        std::cout << "Result(Part1): " << freq << "\n";
        return 0;
    } else {
        std::cerr << "Error parsing input\n";
        return 1;
    }
}

std::vector<int> get_freq_mods() {
    int mod;
    std::vector<int> result;

    while (std::cin >> mod) {
        result.push_back(mod);
    }

    if (std::cin.eof()) {
        return result;
    } else {
        std::cerr << "Error parsing input\n";
        exit(1);
    }
}

int part2() {
    int freq = 0;
    const auto mods = get_freq_mods();
    std::unordered_set<int> freq_set;
    freq_set.insert(0);

    for (;;) {
        for (auto mod : mods) {
            freq += mod;

            if (!freq_set.insert(freq).second) {
                std::cout << "Result(Part2): "  << freq << "\n";
                return 0;
            }
        }
    }
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
        std::cerr << "Unknown part '" << argv[1] << "'.Valid values: 1, 2\n";
        return 1;
    }
}
