#pragma once
#pragma ide diagnostic ignored "misc-no-recursion"

#ifndef EQP_EQP_H
#define EQP_EQP_H

#include <iostream>
#include "board.h"

int amount = 0;
int iterations = 0;

// Checks whether if non-empty figure can attack current queen.
bool Check(Board& board, const Position& nPos) {
    for (const auto& item : board.GetCells()) {
        if (item.second.figure.type != Empty
            && board.CanAttack(item.first, nPos)) {
            return false;
        }
    }
    return true;
}

// Eight queen puzzle function.
bool EQP(Board& board, const int& rank = 1) {
    // It continues up to the 8 queens, then prints combination.
    if (rank > N) {
        std::cout << "Combination #" << ++amount << '\n';
        board.Print();
        std::cout << "\n\n";
        return false;
    }
    for (const auto& file : FILES) {
        iterations++;
        Position position = Position{file, rank};
        if (board.GetFigure(position).override && Check(board, position)) {
            // Puts queen on first empty non-attackable position.
            board.SetFigure(position, Queen, {});
            // If queen is placed, but on the next row queen cannot be placed
            // the last queen deletes and program moves to the previous rank.
            if (!EQP(board, rank + 1)) {
                board.RemoveFigure(position);
            } else {
                return true;
            }
        }
    }
    return false;
}

#endif //EQP_EQP_H
