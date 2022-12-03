#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <map>
#include <stdexcept>
#include <vector>
#include <windows.h>

using namespace std::chrono;

const int N = 7;
const std::vector<char> FILES = [] {
    std::vector<char> files{};
    for (char i = 'A'; i < 'A' + N; i++) {
        files.push_back(i);
    }
    return files;
}();

enum FigureType : char {
    King = 'K',
    Queen = 'Q',
    Rook = 'R',
    Bishop = 'B',
    Knight = 'N',
    Pawn = 'P',
    Empty = '\0'
};

enum Color {
    White, Black
};

struct Position {
    char file;
    int rank;

    Position(char file, int rank):
            file(file),
            rank(rank) {
        if (!std::count(std::begin(FILES), std::end(FILES), file) || rank < 1 || rank > N) {
            throw std::runtime_error("Incorrect position");
        }
    }

    bool operator<(const Position& position) const {
        return file < position.file || (file == position.file && rank < position.rank);
    }
};

struct Figure {
    FigureType type;
    Color color;

    void Print() const {
        char ch = type;
        if (color == Black) {
            ch = (char) std::tolower(ch);
        }
        std::cout << ch;
    }
};

struct Cell {
    Figure figure;
    Color color;

    void Print() const {
        if (figure.type != Empty) {
            figure.Print();
        } else {
            std::cout << (color == White ? ' ' : '*');
        }
    }
};

class Board {
    public:
    Board() {
        Initialize();
    }

    Figure GetFigure(const Position& position) {
        return cells[position].figure;
    }

    void SetFigure(const Position& position, FigureType type, Color color) {
        Figure figure{};
        figure.type = type;
        figure.color = color;
        cells[position].figure = figure;
    }

    //Проверяет только движение
    bool MoveFigure(const Position& pos, const Position& nPos) {
        Figure figure = GetFigure(pos);
        switch (figure.type) {
            case King:
                return std::abs(pos.file - nPos.file) <= 1 && std::abs(pos.rank - nPos.rank) <= 1;
            case Queen:
                return !(pos.file == nPos.file || pos.rank == nPos.rank
                         || std::abs(pos.file - nPos.file) == std::abs(pos.rank - nPos.rank));
            case Rook:
                return pos.file == nPos.file || pos.rank == nPos.rank;
            case Bishop:
                return std::abs(pos.file - nPos.file) == std::abs(pos.rank - nPos.rank);
            case Knight:
                return std::abs((pos.file - nPos.file) * (pos.rank - nPos.rank)) == 2;
            case Pawn:
                //TODO: Ест и ходит она по-разному, да и еще от цвета зависит
                return false;
            default:
                return true;
        }
    }

    void RemoveFigure(const Position& position) {
        SetFigure(position, Empty, {});
    }

    void Print() {
        for (int rank = N; rank >= 1; rank--) {
            std::cout << rank << ' ';
            for (const auto& file : FILES) {
                cells[Position{file, rank}].Print();
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "  ";
        for (const auto& file : FILES) {
            std::cout << file << ' ';
        }
    }

    private:
    std::map<Position, Cell> cells;

    void Initialize() {
        for (const auto& file : FILES) {
            for (int rank = 1; rank <= N; rank++) {
                Cell cell{};
                cell.color = (rank + file - FILES[0]) % 2 == 0 ? White : Black;
                cells[Position{file, rank}] = cell;
                RemoveFigure(Position{file, rank});
            }
        }
    }

//    void Reset() {
//        for (const auto& file : FILES) {
//            for (int rank = 1; rank <= N; rank++) {
//                RemoveFigure(Position{file, rank});
//            }
//        }
//    }
};

std::map<int, std::vector<char>> used;
int amount = 0;
int iterations = 0;

bool Check(Board& board, const Position& nPos) {
    for (int rank = 1; rank < nPos.rank; rank++) {
        for (const auto& file : FILES) {
            Position pos = Position{file, rank};
            if (!board.MoveFigure(pos, nPos)) {
                return false;
            }
        }
    }
    return true;
}

std::vector<char> GetFreeFiles(Board& board, int rank) {
    std::vector<char> files;
    for (const auto& file : FILES) {
        if (std::count(used[rank].begin(), used[rank].end(), file)) {
            continue;
        }
        if (Check(board, Position{file, rank})) {
            files.push_back(file);
        }
    }
    return files;
}

void EQP(Board& board) {
    for (int rank = 1; rank <= N;) {
        std::vector<char> freeFiles = GetFreeFiles(board, rank);
        if (freeFiles.empty()) {
            if (rank == 1) {
                break;
            }
            char previous = used[rank - 1].back();
            for (int i = rank; i < N; i++) {
                used[i] = {};
            }
            board.RemoveFigure(Position{previous, rank - 1});
            rank--;
            continue;
        }
        for (const auto& file : freeFiles) {
            used[rank].push_back(file);
            board.SetFigure(Position{file, rank}, Queen, {});
            rank++;
            break;
        }
        if (rank > N) {
            std::cout << "Комбинация #" << ++amount << '\n';
            board.Print();
            std::cout << "\n\n";
            for (int i = N; i > 1; i--) {
                board.RemoveFigure(Position{used[i].back(), i});
                if (!GetFreeFiles(board, i).empty()) {
                    rank = i;
                    break;
                }
                used[i] = {};
            }
        }
    }
}

bool EQPNew(Board& board, const int& rank = 1) {
    if (rank > N) {
        std::cout << "Комбинация #" << ++amount << '\n';
        board.Print();
        std::cout << "\n\n";
        return false;
    }
    for (const auto& file : FILES) {
        iterations++;
        Position position = Position{file, rank};
        if (Check(board, position)) {
            board.SetFigure(position, Queen, {});
            if (!EQPNew(board, rank + 1)) {
                board.RemoveFigure(position);
            }
        }
    }
    return false;
}

int main() {
    //Set encoding to UTF-8 on Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const auto time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    Board board = Board{};
//    EQP(board);
    EQPNew(board);
    std::cout << "Iterations: " << iterations << '\n';
    std::cout << "Time: "
              << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - time
              << "ms";
    return 0;
}
