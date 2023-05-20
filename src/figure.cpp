#include <iostream>
#include "color.h"
#include "figure.h"

Figure::Figure(Color color, char symbol, bool replaceable):
        color(color), symbol(symbol), replaceable(replaceable) {}

Color Figure::GetColor() const {
    return color;
}

char Figure::GetSymbol() const {
    return symbol;
}

bool Figure::IsReplaceable() const {
    return replaceable;
}

// White figure has CAPITAL letter, black has lower-case letter.
std::ostream& operator<<(std::ostream& os, const Figure* figure) {
    char c = figure->symbol;
    if (figure->color == Black) {
        c = (char) std::tolower(c);
    }
    return os << c;
}
