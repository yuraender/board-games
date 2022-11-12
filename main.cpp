#include <iostream>
#include <windows.h>

const int N = 8;

//Символ фигуры как ASCII
enum FigureType : char {

    KING = 'K',
    QUEEN = 'Q',
    ROOK = 'R',
    BISHOP = 'B',
    KNIGHT = 'N',
    PAWN = 'P',
    EMPTY = ' '
};

enum Color {

    WHITE, BLACK
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

    void SetFigure(int row, int column, FigureType type, Color color) {
        Figure figure{};
        figure.type = type;
        figure.color = color;
        cells[row][column].figure = figure;

        //TODO: проверить, можно ли ставить (не убивается ли)
    }

    void Print() {
        for (int row = N - 1; row >= 0; row--) {
            std::cout << row + 1 << ' ';
            for (int column = 0; column < N; column++) {
                cells[row][column].Print();
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "  A B C D E F G H";
    }

    private:
    //TODO: переделать на А5, E3 и т.д. (map)
    Cell cells[N][N];

    void Initialize() {
        Color color = BLACK;
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                Cell cell{};
                cell.color = color;
                cells[row][column] = cell;
                SetFigure(row, column, EMPTY, {});

                if (column != N - 1) {
                    color = color == WHITE ? BLACK : WHITE;
                }
            }
        }
    }

    void Reset() {
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                SetFigure(row, column, EMPTY, {});
            }
        }
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Board board = Board{};
//    board.SetFigure(3, 4, QUEEN, WHITE);
//    board.SetFigure(5, 5, BISHOP, BLACK);
//    board.SetFigure(7, 0, KNIGHT, WHITE);
    board.Print();
    return 0;
}
