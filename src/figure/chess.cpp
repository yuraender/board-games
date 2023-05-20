#include "color.h"
#include "figure.h"
#include "figure/chess.h"
#include "position.h"

King::King(Color color, bool replaceable):
        Figure(color, 'K', replaceable) {}

bool King::CanAttack(const Position& attacker, const Position& victim) const {
    // In one square horizontally, vertically, or diagonally.
    return std::abs(attacker.file - victim.file) <= 1 && std::abs(attacker.rank - victim.rank) <= 1;
}

Queen::Queen(Color color, bool replaceable):
        Figure(color, 'Q', replaceable) {}

bool Queen::CanAttack(const Position& attacker, const Position& victim) const {
    // In all squares horizontally, vertically, or diagonally.
    return attacker.file == victim.file || attacker.rank == victim.rank
           || std::abs(attacker.file - victim.file) == std::abs(attacker.rank - victim.rank);
}

Rook::Rook(Color color, bool replaceable):
        Figure(color, 'R', replaceable) {}

bool Rook::CanAttack(const Position& attacker, const Position& victim) const {
    // In horizontal or vertical direction for all cells.
    return attacker.file == victim.file || attacker.rank == victim.rank;
}

Bishop::Bishop(Color color, bool replaceable):
        Figure(color, 'B', replaceable) {}

bool Bishop::CanAttack(const Position& attacker, const Position& victim) const {
    // In diagonal direction for all cells.
    return std::abs(attacker.file - victim.file) == std::abs(attacker.rank - victim.rank);
}

Knight::Knight(Color color, bool replaceable):
        Figure(color, 'N', replaceable) {}

bool Knight::CanAttack(const Position& attacker, const Position& victim) const {
    // In an "L-shape".
    // In two squares in any direction vertically followed by one square horizontally,
    // or two squares in any direction horizontally followed by one square vertically.
    return std::abs((attacker.file - victim.file) * (attacker.rank - victim.rank)) == 2;
}

Pawn::Pawn(Color color, bool replaceable):
        Figure(color, 'P', replaceable) {}

bool Pawn::CanAttack(const Position& attacker, const Position& victim) const {
    // In one square diagonally forward to the left or right.
    // TODO: En passant.
    return attacker.rank + (color == White ? 1 : -1) == victim.rank
           && (attacker.file - 1 == victim.file || attacker.file + 1 == victim.file);
}
