#include "board.h"
#include "eqp.h"

bool Check(Board& board, const Position& victim) {
    for (const auto& attacker : board) {
        Figure figure = attacker.second.figure;
        if (figure.type != Empty
            && figure.CanAttack(attacker.first, victim)) {
            return false;
        }
    }
    return true;
}

bool EQP(Board& board, int rank, int& amount, int& iterations) {
    // It continues up to the 8 queens, then prints combination.
    if (rank > N) {
        std::cout << "Combination #" << ++amount << '\n';
        std::cout << board;
        std::cout << "\n\n";
        return false;
    }
    for (const auto& file : FILES) {
        iterations++;
        Position position = Position{file, rank};
        if (board.GetFigure(position).replaceable && Check(board, position)) {
            // Puts queen on first empty non-attackable position.
            board.SetFigure(position, Queen, {});
            // If queen is placed, but on the next row queen cannot be placed
            // the last queen deletes and program moves to the previous rank.
            EQP(board, rank + 1, amount, iterations);
            board.RemoveFigure(position);
        }
    }
    return false;
}
