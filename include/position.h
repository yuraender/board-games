#pragma once

#include <vector>

const int N = 8;
const std::vector<char> FILES = [] {
    std::vector<char> files{};
    for (char i = 'A'; i < 'A' + N; i++) {
        files.push_back(i);
    }
    return files;
}();

struct Position {
    char file;
    int rank;

    Position(char file, int rank);

    bool operator<(const Position& position) const;
};
