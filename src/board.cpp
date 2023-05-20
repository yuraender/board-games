#include "board.h"
#include "color.h"
#include "figure.h"
#include "position.h"

Cell::Cell():
        figure(nullptr), color(White) {}

Cell::Cell(Figure* figure, Color color):
        figure(figure), color(color) {}

Cell::~Cell() {
    delete figure;
}

bool Cell::IsEmpty() const {
    return figure == nullptr;
}

// White cell has no letter, black has asterisk letter.
// If cell is not empty, letter of figure is used.
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    if (!cell.IsEmpty()) {
        return os << cell.figure;
    } else {
        return os << (cell.color == White ? ' ' : '*');
    }
}

Board::Board() {
    for (const auto& file : FILES) {
        for (int rank = 1; rank <= N; rank++) {
            Cell cell{};
            cell.color = (rank + file - FILES[0]) % 2 == 0 ? White : Black;
            cells[Position{file, rank}] = cell;
            RemoveFigure(Position{file, rank});
        }
    }
}

Figure* Board::GetFigure(const Position& position) {
    return cells[position].figure;
}

Figure* Board::SetFigure(const Position& position, Figure* figure) {
    delete cells[position].figure;
    cells[position].figure = figure;
    return figure;
}

void Board::RemoveFigure(const Position& position) {
    SetFigure(position, nullptr);
}

const Cell& Board::operator[](const Position& position) const {
    return cells.at(position);
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for (int rank = N; rank >= 1; rank--) {
        os << rank << ' ';
        for (const auto& file : FILES) {
            os << board[Position{file, rank}] << ' ';
        }
        os << '\n';
    }
    os << "  ";
    for (const auto& file : FILES) {
        os << file << ' ';
    }
    return os;
}
