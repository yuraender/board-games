#include <iostream>
#include <cmath>
#include <map>
#include <stdexcept>
#include <windows.h>

const int N = 8;
const char FILES[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

//Символ фигуры как ASCII
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
        if (file < 'A' || file > 'H' || rank < 1 || rank > 8) {
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

    bool Move(Position pos, Position nPos) {
        //TODO: написать алгоритм для проверки перемещения
        switch (type) {
            case King:
                return std::abs(pos.file - nPos.file) <= 1 && std::abs(pos.rank - nPos.rank) <= 1;
            case Queen:
                return false;
            case Rook:
                return pos.file == nPos.file || pos.rank == nPos.rank;
            case Bishop:
                return std::abs(pos.file - nPos.file) == std::abs(pos.rank - nPos.rank);
            case Knight:
                return false;
            case Pawn:
                return false;
            default:
                return false;
        }
    }

    void Print() {
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

    void Print() {
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

    void SetFigure(Position position, FigureType type, Color color) {
        Figure figure{};
        figure.type = type;
        figure.color = color;
        cells[position].figure = figure;

        if (type != Empty) {
            //TODO: проверить, можно ли ставить (не убивается ли)
        }
    }

    void RemoveFigure(Position position) {
        SetFigure(position, Empty, {});
    }

    void Print() {
        for (int rank = N; rank > 0; rank--) {
            std::cout << rank << ' ';
            for (const auto& file : FILES) {
                cells[Position{file, rank}].Print();
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "  A B C D E F G H";
    }

    private:
    std::map<Position, Cell> cells;

    void Initialize() {
        for (const auto& file : FILES) {
            for (int rank = 1; rank <= N; rank++) {
                Cell cell{};
                cell.color = (rank + file - 'A') % 2 == 0 ? White : Black;
                cells[Position{file, rank}] = cell;
                RemoveFigure(Position{file, rank});
            }
        }
    }

    void Reset() {
        for (const auto& file : FILES) {
            for (int rank = 1; rank <= N; rank++) {
                RemoveFigure(Position{file, rank});
            }
        }
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Board board = Board{};
    board.SetFigure(Position{'E', 4}, Queen, White);
    board.SetFigure(Position{'F', 6}, Bishop, Black);
    board.SetFigure(Position{'A', 8}, Knight, White);

    board.Print();
    return 0;
}
