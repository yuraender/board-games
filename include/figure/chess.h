#pragma once

#include "color.h"
#include "figure.h"
#include "position.h"

class King : public Figure {
    public:
    King(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};

class Queen : public Figure {
    public:
    Queen(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};

class Rook : public Figure {
    public:
    Rook(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};

class Bishop : public Figure {
    public:
    Bishop(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};

class Knight : public Figure {
    public:
    Knight(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};

class Pawn : public Figure {
    public:
    Pawn(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};
