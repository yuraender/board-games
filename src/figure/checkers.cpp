#include "color.h"
#include "exceptions.h"
#include "figure.h"
#include "figure/checkers.h"
#include "position.h"

Checker::Checker(Color color, bool replaceable):
        Figure(color, 'C', replaceable) {}

bool Checker::CanAttack(const Position& attacker, const Position& victim) const {
    throw UnsupportedOperationException();
}
