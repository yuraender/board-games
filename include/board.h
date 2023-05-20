#pragma once

#include <iostream>
#include <map>
#include "color.h"
#include "figure.h"
#include "position.h"

struct Cell {
    Figure* figure;
    Color color;

    Cell();

    Cell(Figure* figure, Color color);

    ~Cell();

    bool IsEmpty() const;

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

class Board {
    public:
    Board();

    // Gets figure on specific position of board.
    Figure* GetFigure(const Position& position);

    // Sets figure on specific position of board.
    Figure* SetFigure(const Position& position, Figure* figure);

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
