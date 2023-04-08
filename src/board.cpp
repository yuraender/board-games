#include "board.h"
#include "exceptions.h"

Position::Position(char file, int rank):
        file(file),
        rank(rank) {
    if (!std::count(std::begin(FILES), std::end(FILES), file) || rank < 1 || rank > N) {
        throw IncorrectPositionException();
    }
}

bool Position::operator<(const Position& position) const {
    return file < position.file || (file == position.file && rank < position.rank);
}

// Checks whether if figure on specific position can attack another position.
bool Figure::CanAttack(const Position& attacker, const Position& victim) const {
    switch (type) {
        case King:
            // In one square horizontally, vertically, or diagonally.
            return std::abs(attacker.file - victim.file) <= 1 && std::abs(attacker.rank - victim.rank) <= 1;
        case Queen:
            // In all squares horizontally, vertically, or diagonally.
            return attacker.file == victim.file || attacker.rank == victim.rank
                   || std::abs(attacker.file - victim.file) == std::abs(attacker.rank - victim.rank);
        case Rook:
            // In horizontal or vertical direction for all cells.
            return attacker.file == victim.file || attacker.rank == victim.rank;
        case Bishop:
            // In diagonal direction for all cells.
            return std::abs(attacker.file - victim.file) == std::abs(attacker.rank - victim.rank);
        case Knight:
            // In an "L-shape".
            // In two squares in any direction vertically followed by one square horizontally,
            // or two squares in any direction horizontally followed by one square vertically.
            return std::abs((attacker.file - victim.file) * (attacker.rank - victim.rank)) == 2;
        case Pawn:
            // TODO:
            // In one square diagonally forward to the left or right.
            // En passant.
            //
            //return attacker.rank + (figure.color == White ? 1 : -1) == victim.rank
            //       && (attacker.file - 1 == victim.file || attacker.file + 1 == victim.file);
            throw UnsupportedOperationException();
        default:
            return false;
    }
}

// White figure has CAPITAL letter, black has lower-case letter.
std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    char ch = figure.type;
    if (figure.color == Black) {
        ch = (char) std::tolower(ch);
    }
    return os << ch;
}

// White cell has no letter, black has asterisk letter.
// If cell is not empty, letter of figure is used.
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    if (cell.figure.type != Empty) {
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

Figure& Board::GetFigure(const Position& position) {
    return cells[position].figure;
}

Figure& Board::SetFigure(const Position& position, FigureType type, Color color, bool replaceable) {
    Figure& figure = cells[position].figure;
    figure.type = type;
    figure.color = color;
    figure.replaceable = replaceable;
    return figure;
}

void Board::RemoveFigure(const Position& position) {
    SetFigure(position, Empty, {});
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
