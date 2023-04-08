#ifndef BG_BOARD_H
#define BG_BOARD_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include "exceptions.h"

const int N = 8;
const std::vector<char> FILES = [] {
    std::vector<char> files{};
    for (char i = 'A'; i < 'A' + N; i++) {
        files.push_back(i);
    }
    return files;
}();

enum FigureType : char {
    King = 'K',
    Queen = 'Q',
    Rook = 'R',
    Bishop = 'B',
    Knight = 'N',
    Pawn = 'P',
    Empty = '\0'
};

enum Color {
    White, Black
};

struct Position {
    char file;
    int rank;

    Position(char file, int rank);

    bool operator<(const Position& position) const;
};

struct Figure {
    FigureType type;
    Color color;
    // Can be replaced while EQP or not.
    bool replaceable;

    // Checks whether if figure on specific position can attack another position.
    [[nodiscard]]
    bool CanAttack(const Position& attacker, const Position& victim) const;

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
};

struct Cell {
    Figure figure;
    Color color;

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

class Board {
    public:
    Board();

    // Gets figure on specific position of board.
    Figure& GetFigure(const Position& position);

    // Sets figure on specific position of board and returns it.
    Figure& SetFigure(const Position& position, FigureType type, Color color, bool replaceable = true);

    // Removes figure on specific position of board.
    void RemoveFigure(const Position& position);

    const Cell& operator[](const Position& position) const;

    std::map<Position, Cell>::iterator begin() noexcept {
        return cells.begin();
    }

    std::map<Position, Cell>::iterator end() noexcept {
        return cells.end();
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

    private:
    std::map<Position, Cell> cells;
};

#endif //BG_BOARD_H
