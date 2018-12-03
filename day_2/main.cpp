#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cstring>

int part1() {
    int twos = 0;
    int threes = 0;

    for (std::string line; std::getline(std::cin, line);) {
        std::array<size_t, 256> freqs;
        freqs.fill(0);

        for (char character : line) {
            freqs[static_cast<size_t>(character)] += 1;
        }

        //Read carefully damn puzzle!
        //You need to count each once
        bool twos_done = false;
        bool threes_done = false;
        for (size_t idx = 0; idx < freqs.size(); idx++) {
            switch (freqs[idx]) {
                case 2:
                    if (!twos_done) {
                        twos++;
                        twos_done = true;

                        if (threes_done) goto part1_count_end;
                    }
                    break;
                case 3:
                    if (!threes_done) {
                        threes++;
                        threes_done = true;

                        if (twos_done) goto part1_count_end;
                    }
                    break;
                default:
                    break;
            }
        }

part1_count_end:
        continue;
    }

    std::cout << "Result(Part 1): " << twos * threes << "\n";

    return 0;
}

int part2() {
    std::vector<std::string> lines;
    for (std::string line; std::getline(std::cin, line);) {
        lines.emplace_back(std::move(line));
    }

    for (size_t idx = 0; idx < lines.size(); idx++) {
        const auto& current = lines[idx];
        const size_t current_size = current.size();

        for (size_t idx_next = idx + 1; idx_next < lines.size(); idx_next++) {
            std::string result;
            const auto& next = lines[idx_next];

            if (next.size() != current_size) continue;

            size_t wrong_num = 0;

            for (size_t char_idx = 0; char_idx < current_size; char_idx++) {
                if (current[char_idx] != next[char_idx]) {
                    wrong_num++;

                    if (wrong_num > 1) {
                        result.clear();
                        goto part2_next_end;
                    }
                } else {
                    result.push_back(current[char_idx]);
                }
            }

            std::cout << "Result(Part2): " << result.c_str() << "\n";
            goto part2_end;
part2_next_end:
            continue;
        }
    }

part2_end:
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
