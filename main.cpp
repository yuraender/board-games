#include <iostream>
#include <map>
#include <stdexcept>
#include <windows.h>

const int N = 8;
const char FILES[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

//Символ фигуры как ASCII
enum FigureType : char {

    KING = 'K',
    QUEEN = 'Q',
    ROOK = 'R',
    BISHOP = 'B',
    KNIGHT = 'N',
    PAWN = 'P',
    EMPTY = '\0'
};

enum Color {

    WHITE, BLACK
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

    bool Move(int row, int column, int newRow, int newColumn) {
        //TODO: написать алгоритм для проверки перемещения
        return false;
    }

    void Print() {
        char ch = type;
        if (color == BLACK) {
            ch = std::tolower(ch);
        }
        std::cout << ch;
    }
};

struct Cell {

    Figure figure;
    Color color;

    void Print() {
        if (figure.type != EMPTY) {
            figure.Print();
        } else {
            std::cout << (color == WHITE ? ' ' : '*');
        }
    }
};

struct Board {
    public:
    Board() {
        Initialize();
    }

    Figure SetFigure(Position position, FigureType type, Color color) {
        Figure figure{};
        figure.type = type;
        figure.color = color;
        cells[position].figure = figure;

        if (type != EMPTY) {
            //TODO: проверить, можно ли ставить (не убивается ли)
        }
        return figure;
    }

    void RemoveFigure(Position position) {
        SetFigure(position, EMPTY, {});
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
                cell.color = (rank + file - 'A') % 2 == 0 ? WHITE : BLACK;
                cells[Position{file, rank}] = cell;
                SetFigure(Position{file, rank}, EMPTY, {});
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
    board.SetFigure(Position{'E', 4}, QUEEN, WHITE);
    board.SetFigure(Position{'F', 6}, BISHOP, BLACK);
    board.SetFigure(Position{'A', 8}, KNIGHT, WHITE);

    board.Print();
    return 0;
}
