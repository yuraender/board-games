#pragma once
#pragma ide diagnostic ignored "misc-no-recursion"

#ifndef BG_EQP_H
#define BG_EQP_H

#include <iostream>
#include "board.h"

// Checks whether if non-empty figure can attack current queen.
bool Check(Board& board, const Position& victim);

// Eight queen puzzle function.
bool EQP(Board& board, int rank, int& amount, int& iterations);

#endif //BG_EQP_H
