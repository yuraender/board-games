#pragma once

#include <functional>
#include "board.h"
#include "position.h"

// Checks whether if non-empty figure can attack current queen.
bool Check(Board& board, const Position& victim);

// Eight queen puzzle function.
bool EQP(Board& board, int rank, const std::function<void(Board&, int)>& print, int& amount, int& iterations);
