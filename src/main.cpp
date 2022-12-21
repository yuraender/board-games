#include <iostream>
#include <chrono>
#include "board.h"
#include "eqp.h"

using namespace std::chrono;

int main() {
    const auto time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    Board board = Board{};
    EQP(board);
    std::cout << "Iterations: " << iterations << '\n';
    std::cout << "Time: "
              << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - time
              << "ms";
    return 0;
}
