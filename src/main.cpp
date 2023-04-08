#include <iostream>
#include <chrono>
#include "board.h"
#include "eqp.h"

using namespace std::chrono;

int main() {
    try {
        const auto time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        Board board = Board{};
        int amount = 0;
        int iterations = 0;
        EQP(board, 1, amount, iterations);
        std::cout << "Iterations: " << iterations << '\n';
        std::cout << "Time: "
                  << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - time
                  << "ms\n";
    } catch (std::exception& ex) {
        std::cout << ex.what() << '\n';
    }
    return 0;
}
