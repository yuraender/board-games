#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <stdexcept>
#include <windows.h>

const int N = 8;
char FILES[N];

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
            ch = std::tolower(ch);
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

    Figure GetFigure(Position position) {
        return cells[position].figure;
    }

    void SetFigure(Position position, FigureType type, Color color) {
        Figure figure{};
        figure.type = type;
        figure.color = color;
        cells[position].figure = figure;
    }

    //Проверяет только движение
    bool MoveFigure(Position pos, Position nPos) {
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

    void RemoveFigure(Position position) {
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

bool Check(Board& board, Position nPos) {
    for (int rank = 1; rank < N; rank++) {
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

int main() {
    //Set encoding to UTF-8 on Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    for (int i = 0; i < N; i++) {
        FILES[i] = (char) ('A' + i);
    }

    Board board = Board{};
    EQP(board);
//    board.Print();
    return 0;
}
