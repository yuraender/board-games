#pragma once
#pragma ide diagnostic ignored "misc-no-recursion"

#ifndef EQP_EQP_H
#define EQP_EQP_H

#include <iostream>
#include "board.h"

int amount = 0;
int iterations = 0;

bool Check(Board& board, const Position& nPos) {
    for (const auto& item : board.GetCells()) {
        if (item.second.figure.type != Empty
            && board.CanAttack(item.first, nPos)) {
            return false;
        }
    }
    return true;
}

bool EQP(Board& board, const int& rank = 1) {
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
            board.SetFigure(position, Queen, {});
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
