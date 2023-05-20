#pragma once

#include <iostream>
#include "color.h"
#include "position.h"

class Figure {
    public:
    Figure(Color color, char symbol, bool replaceable);

    // Checks whether if figure on specific position can attack another position.
    virtual bool CanAttack(const Position& attacker, const Position& victim) const {
        return false;
    }

    Color GetColor() const;

    char GetSymbol() const;

    bool IsReplaceable() const;

    friend std::ostream& operator<<(std::ostream& os, const Figure* figure);

    protected:
    Color color;
    bool replaceable;
    char symbol;
};
