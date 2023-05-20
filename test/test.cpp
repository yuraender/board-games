#include "board.cpp"
#include "eqp.cpp"
#include "figure.cpp"
#include "figure/chess.cpp"
#include "position.cpp"
#include "gtest/gtest.h"

TEST(EQP, ComboAmount) {
    Board board{};

    int amount = 0;
    int iterations = 0;
    EQP(board, 1,
        [](Board& b, int a) {},
        amount, iterations
    );

    switch (N) {
        case 1:
            ASSERT_EQ(amount, 1);
            break;
        case 2:
        case 3:
            ASSERT_EQ(amount, 0);
            break;
        case 4:
            ASSERT_EQ(amount, 2);
            break;
        case 5:
            ASSERT_EQ(amount, 10);
            break;
        case 6:
            ASSERT_EQ(amount, 4);
            break;
        case 7:
            ASSERT_EQ(amount, 40);
            break;
        case 8:
            ASSERT_EQ(amount, 92);
            break;
        case 9:
            ASSERT_EQ(amount, 352);
            break;
        case 10:
            ASSERT_EQ(amount, 724);
            break;
    }
}

TEST(Board, QueenAttack) {
    Board board{};
    Figure* figure = board.SetFigure(Position{'F', 5}, new Queen(White, true));
    ASSERT_FALSE(figure->CanAttack(Position{'F', 5}, Position{'B', 6}));
    ASSERT_FALSE(figure->CanAttack(Position{'F', 5}, Position{'H', 1}));
    ASSERT_TRUE(figure->CanAttack(Position{'F', 5}, Position{'C', 8}));
    ASSERT_TRUE(figure->CanAttack(Position{'F', 5}, Position{'A', 5}));
}

TEST(Board, BishopAttack) {
    Board board{};
    Figure* figure = board.SetFigure(Position{'B', 5}, new Bishop(White, true));
    ASSERT_FALSE(figure->CanAttack(Position{'B', 5}, Position{'C', 3}));
    ASSERT_TRUE(figure->CanAttack(Position{'B', 5}, Position{'E', 8}));
    ASSERT_FALSE(figure->CanAttack(Position{'B', 5}, Position{'F', 2}));
    ASSERT_TRUE(figure->CanAttack(Position{'B', 5}, Position{'A', 4}));
}

TEST(Board, PawnAttack) {
    Board board{};
    Figure* figure = board.SetFigure(Position{'E', 4}, new Pawn(Black, true));
    ASSERT_FALSE(figure->CanAttack(Position{'E', 4}, Position{'D', 5}));
    ASSERT_FALSE(figure->CanAttack(Position{'E', 4}, Position{'E', 5}));
    ASSERT_FALSE(figure->CanAttack(Position{'E', 4}, Position{'F', 5}));
    ASSERT_TRUE(figure->CanAttack(Position{'E', 4}, Position{'D', 3}));
}
