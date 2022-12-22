#pragma once

#ifndef EQP_BOARD_H
#define EQP_BOARD_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <stdexcept>

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

    Position(char file, int rank):
            file(file),
            rank(rank) {
        if (!std::count(std::begin(FILES), std::end(FILES), file) || rank < 1 || rank > N) {
            throw std::runtime_error("Incorrect position");
        }
    }

    bool operator<(const Position& position) const {
        return file < position.file || (file == position.file && rank < position.rank);
    }
};

struct Figure {
    FigureType type;
    Color color;
    // Can be or not overridden while EQP.
    bool override;

    // Prints figure.
    // White figure has CAPITAL letter, black has lower-case letter.
    void Print() const {
        char ch = type;
        if (color == Black) {
            ch = (char) std::tolower(ch);
        }
        std::cout << ch;
    }
};

struct Cell {
    Figure figure;
    Color color;

    // Prints cell.
    // White cell has no letter, black has asterisk letter.
    // If cell is not empty, letter of figure is used.
    void Print() const {
        if (figure.type != Empty) {
            figure.Print();
        } else {
            std::cout << (color == White ? ' ' : '*');
        }
    }
};

class Board {
    public:
    Board() {
        Initialize();
    }

    // Gets figure on specific position of board.
    Figure& GetFigure(const Position& position) {
        return cells[position].figure;
    }

    // Sets figure on specific position of board.
    void SetFigure(const Position& position, FigureType type, Color color, bool override = true) {
        Figure& figure = cells[position].figure;
        figure.type = type;
        figure.color = color;
        figure.override = override;
    }

    // Checks whether if figure on specific position can attack another position.
    bool CanAttack(const Position& pos, const Position& nPos) {
        Figure figure = GetFigure(pos);
        switch (figure.type) {
            case King:
                // In one square horizontally, vertically, or diagonally.
                return std::abs(pos.file - nPos.file) <= 1 && std::abs(pos.rank - nPos.rank) <= 1;
            case Queen:
                // In all squares horizontally, vertically, or diagonally.
                return pos.file == nPos.file || pos.rank == nPos.rank
                       || std::abs(pos.file - nPos.file) == std::abs(pos.rank - nPos.rank);
            case Rook:
                // In horizontal or vertical direction for all cells.
                return pos.file == nPos.file || pos.rank == nPos.rank;
            case Bishop:
                // In diagonal direction for all cells.
                return std::abs(pos.file - nPos.file) == std::abs(pos.rank - nPos.rank);
            case Knight:
                // In an "L-shape".
                // In two squares in any direction vertically followed by one square horizontally,
                // or two squares in any direction horizontally followed by one square vertically.
                return std::abs((pos.file - nPos.file) * (pos.rank - nPos.rank)) == 2;
            case Pawn:
                // In one square diagonally forward to the left or right.
                return pos.rank + (figure.color == White ? 1 : -1) == nPos.rank
                       && (pos.file - 1 == nPos.file || pos.file + 1 == nPos.file);
            default:
                return false;
        }
    }

    // Removes figure on specific position of board.
    void RemoveFigure(const Position& position) {
        SetFigure(position, Empty, {});
    }

    // Prints board.
    void Print() {
        for (int rank = N; rank >= 1; rank--) {
            std::cout << rank << ' ';
            for (const auto& file : FILES) {
                cells[Position{file, rank}].Print();
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "  ";
        for (const auto& file : FILES) {
            std::cout << file << ' ';
        }
    }

    std::map<Position, Cell>& GetCells() {
        return cells;
    }

    private:
    std::map<Position, Cell> cells;

    // Creates board with empty cells.
    void Initialize() {
        for (const auto& file : FILES) {
            for (int rank = 1; rank <= N; rank++) {
                Cell cell{};
                cell.color = (rank + file - FILES[0]) % 2 == 0 ? White : Black;
                cells[Position{file, rank}] = cell;
                RemoveFigure(Position{file, rank});
            }
        }
    }
};

#endif //EQP_BOARD_H
