#pragma ide diagnostic ignored "misc-no-recursion"

#include <functional>
#include "board.h"
#include "eqp.h"
#include "figure.h"
#include "figure/chess.h"
#include "position.h"

bool Check(Board& board, const Position& victim) {
    for (const auto& attacker : board) {
        Figure* figure = attacker.second.figure;
        if (!attacker.second.IsEmpty()
            && figure->CanAttack(attacker.first, victim)) {
            return false;
        }
    }
    return true;
}

bool EQP(Board& board, int rank, const std::function<void(Board&, int)>& print, int& amount, int& iterations) {
    // It continues up to the 8 queens, then prints combination.
    if (rank > N) {
        print(board, ++amount);
        return false;
    }
    for (const auto& file : FILES) {
        iterations++;
        Position position = Position{file, rank};
        Figure* figure = board.GetFigure(position);
        if ((figure == nullptr || figure->IsReplaceable())
            && Check(board, position)) {
            // Places queen on first empty non-attackable position.
            board.SetFigure(position, new Queen(White, true));
            // If queen is placed, but on the next row queen cannot be placed
            // the last queen deletes and program moves to the previous rank.
            EQP(board, rank + 1, print, amount, iterations);
            board.RemoveFigure(position);
        }
    }
    return false;
}
