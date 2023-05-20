#pragma once

#include "color.h"
#include "figure.h"
#include "position.h"

class Checker : public Figure {
    public:
    Checker(Color color, bool replaceable);

    bool CanAttack(const Position& attacker, const Position& victim) const override;
};
