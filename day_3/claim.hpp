#pragma once

#include <cctype>
#include <optional>
#include <charconv>
#include <string_view>

struct Dimensions {
    size_t x;
    size_t y;

    static std::optional<const char*> parse_into(std::string_view text, char sep, Dimensions& result) {
        size_t cursor = 0;
        while (std::isdigit(static_cast<char>(text[cursor]))) cursor++;
        if (text[cursor] != sep) {
            return "Invalind format";
        }

        auto res = std::from_chars(text.data(), text.data() + cursor, result.x);

        if (res.ec == std::errc::invalid_argument) {
            return "Invalid X";
        } else if (res.ec == std::errc::result_out_of_range) {
            return "X is out of range";
        }

        cursor++;

        size_t start = cursor;
        while (std::isdigit(static_cast<char>(text[cursor]))) cursor++;

        res = std::from_chars(text.data() + start, text.data() + cursor, result.y);

        if (res.ec == std::errc::invalid_argument) {
            return "Invalid Y";
        } else if (res.ec == std::errc::result_out_of_range) {
            return "Y is out of range";
        }

        return std::nullopt;
    }
};

struct Claim {
    int id;
    Dimensions coords;
    Dimensions size;

    ///Parses claim as #1 @ 1,3: 4x4
    static std::optional<Claim> parse(const std::string& text) noexcept {
        constexpr char START_ID = '#';
        constexpr char START_COORD = '@';
        constexpr char COORD_SEP = ',';
        constexpr char START_SIZE = ':';
        constexpr char SIZE_SEP = 'x';

        Claim claim;

        size_t cursor = 0;

        //Taking shortcuts here, but you also need to make sure not to go out of string
        while (text[cursor] == ' ' || text[cursor] == '\t') cursor++;
        if (text[cursor] == '\0') {
            std::cerr << "Missing ID\n";
            return std::nullopt;
        }

        if (text[cursor] != START_ID) {
            std::cerr << "Missing #\n";
            return std::nullopt;
        }
        cursor++;

        {
            size_t start = cursor;
            while (std::isdigit(static_cast<char>(text[cursor]))) cursor++;

            auto res = std::from_chars(text.data() + start, text.data() + cursor, claim.id);

            if (res.ec == std::errc::invalid_argument) {
                std::cerr << "Invalid ID\n";
                return std::nullopt;
            } else if (res.ec == std::errc::result_out_of_range) {
                std::cerr << "ID is out of range\n";
                return std::nullopt;
            }
        }

        while (text[cursor] == ' ' || text[cursor] == '\t') cursor++;
        if (text[cursor] != START_COORD) {
            std::cerr << "Missing @\n";
            return std::nullopt;
        }
        cursor++;
        while (text[cursor] == ' ' || text[cursor] == '\t') cursor++;
        if (text[cursor] == '\0') {
            std::cerr << "Missing coordinates\n";
            return std::nullopt;
        }

        {
            size_t start = cursor;
            while (text[cursor] != START_SIZE) cursor++;
            std::string_view slice(text.data() + start, cursor - start);

            auto res = Dimensions::parse_into(slice, COORD_SEP, claim.coords);

            if (res.has_value()) {
                std::cerr << "Error while parsing coordinates: " << *res << "\n";
                return std::nullopt;
            }

            cursor++;
        }

        while (text[cursor] == ' ' || text[cursor] == '\t') cursor++;
        if (text[cursor] == '\0') {
            std::cerr << "Missing size\n";
            return std::nullopt;
        }

        std::string_view slice(text.data() + cursor, text.size() - cursor);

        auto res = Dimensions::parse_into(slice, SIZE_SEP, claim.size);

        if (res.has_value()) {
            std::cerr << "Error while parsing sizes: " << *res << "\n";
            return std::nullopt;
        }

        return claim;
    }
};
