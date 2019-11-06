#include <gtest/gtest.h> 	  			 	 
#include "SixMensMorrisBoard.h"

TEST(SixMensMorrisBoardTest, DefaultBoardTest){
    // Needs to test that default board is correct
    CSixMensMorrisBoard SixBoard = CSixMensMorrisBoard();
    EXPECT_EQ(
        SixBoard.ToString(),
        ">RU:6 RC:0  WU:6 WC:0\n"
        "o---------o---------o      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    o----o----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         o----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    o----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
    EXPECT_EQ(
        std::string(SixBoard),
        ">RU:6 RC:0  WU:6 WC:0\n"
        "o---------o---------o      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    o----o----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         o----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    o----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        EXPECT_EQ(SixBoard.PlayerAtPosition(i), SIX_MENS_MORRIS_EMPTY);
    }
}

TEST(SixMensMorrisBoardTest, SetBoardTest){
    // Needs to test that setting board is correcit
    // prepare set varivable.
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {2, 3};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[3] = positions[4] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[8] = positions[10] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[8] = previous[10] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    EXPECT_EQ(
        SixBoard.ToString(),
        " RU:2 RC:0 >WU:3 WC:0\n"
        "R---------R---------W      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    R----R----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         W----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    W----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
    EXPECT_EQ(
        std::string(SixBoard),
        " RU:2 RC:0 >WU:3 WC:0\n"
        "R---------R---------W      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    R----R----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         W----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    W----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
    EXPECT_EQ(SixBoard.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(SixBoard.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(SixBoard.PlayerAtPosition(1), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(SixBoard.PlayerAtPosition(3), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(SixBoard.PlayerAtPosition(4), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(SixBoard.PlayerAtPosition(2), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(SixBoard.PlayerAtPosition(8), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(SixBoard.PlayerAtPosition(10), SIX_MENS_MORRIS_PLAYER_W);
}

TEST(SixMensMorrisBoardTest, ResetBoardTest){
    // Needs to test that resetting to default board is correct
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {2, 3};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[3] = positions[4] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[8] = positions[10] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[8] = previous[10] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    // Resets the board back to initial setup.
    SixBoard.ResetBoard();
    // check board status.
    EXPECT_EQ(
        std::string(SixBoard),
        ">RU:6 RC:0  WU:6 WC:0\n"
        "o---------o---------o      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    o----o----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         o----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    o----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
}

TEST(SixMensMorrisBoardTest, PlacementTest){
    // Needs to test that normal placement is correct
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {2, 3};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[3] = positions[4] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[8] = positions[10] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[8] = previous[10] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    // Wrong player
    EXPECT_FALSE(SixBoard.Place('E', 9));
    EXPECT_FALSE(SixBoard.Place(SIX_MENS_MORRIS_PLAYER_R, 9));

    // Wrong Position
    EXPECT_FALSE(SixBoard.Place(SIX_MENS_MORRIS_PLAYER_W, 20));
    // Has Other Pieces.
    EXPECT_FALSE(SixBoard.Place(SIX_MENS_MORRIS_PLAYER_W, 0));
    EXPECT_FALSE(SixBoard.Place(SIX_MENS_MORRIS_PLAYER_W, 2));

    // Right Place
    EXPECT_TRUE(SixBoard.Place(SIX_MENS_MORRIS_PLAYER_W, 9));
    // Change to other player turn.
    EXPECT_EQ(SixBoard.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(
        std::string(SixBoard),
        ">RU:2 RC:0  WU:2 WC:0\n"
        "R---------R---------W      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    R----R----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         W----W\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    W----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
}

TEST(SixMensMorrisBoardTest, PlacementMillTest){
    // Needs to test that normal placement is correct
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {2, 3};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[2] = positions[5] = SIX_MENS_MORRIS_PLAYER_R;
    positions[3] = positions[8] = positions[10] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[3] = previous[8] = previous[10] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    // Place, get Mill
    EXPECT_TRUE(SixBoard.Place(SIX_MENS_MORRIS_PLAYER_W, 7));
    EXPECT_EQ(
        std::string(SixBoard),
        ">RU:2 RC:0  WU:2 WC:0\n"
        "R---------R---------R      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    W----o----R    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----W         W----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    W----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
    // if new mill, can Move.
    EXPECT_TRUE(SixBoard.CanRemove(SIX_MENS_MORRIS_PLAYER_W));
    EXPECT_TRUE(SixBoard.Remove(SIX_MENS_MORRIS_PLAYER_W, 0));
    // std::cout << SixBoard.ToString() << std::endl;
    EXPECT_EQ(
        std::string(SixBoard),
        ">RU:2 RC:0  WU:2 WC:1\n"
        "o---------R---------R      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    W----o----R    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----W         W----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    W----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );
}

TEST(SixMensMorrisBoardTest, MoveTest){
    // Needs to test that movement is correct
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {2, 0};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[3] = positions[4] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[8] = positions[10] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[8] = previous[10] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    // std::cout << SixBoard.ToString() << std::endl;
    // check differenc Position whether can move.
    EXPECT_TRUE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 0));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 1));
    EXPECT_TRUE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_W, 2));
    EXPECT_TRUE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 3));
    EXPECT_TRUE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 4));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 5));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 6));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 7));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 8));
    EXPECT_TRUE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_W, 8));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_W, 9));
    EXPECT_TRUE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_W, 10));

    // move test.
    EXPECT_FALSE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 6));
    EXPECT_FALSE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_W, 1, 6));
    EXPECT_FALSE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_W, 2, 0xF));
    EXPECT_TRUE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_W, 2, 9));
    EXPECT_EQ(SixBoard.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_FALSE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_W, 8, 0xC));
    // std::cout << SixBoard.ToString() << std::endl;
    EXPECT_EQ(
        std::string(SixBoard),
        ">RU:2 RC:3  WU:0 WC:0\n"
        "R---------R---------o      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    R----R----o    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         W----W\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    W----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------o---------o\n"
    );

}

TEST(SixMensMorrisBoardTest, MoveMillTest){
    // Needs to test that movement creating a mill is correct with removal
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0, 0};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[3] = positions[5] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[8] = positions[0xE] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[8] = previous[0xE] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    // std::cout << SixBoard.ToString() << std::endl;
    EXPECT_TRUE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_W, 8, 9));
    EXPECT_TRUE(SixBoard.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 4));

    EXPECT_TRUE(SixBoard.CanRemove(SIX_MENS_MORRIS_PLAYER_R));
    EXPECT_FALSE(SixBoard.Remove(SIX_MENS_MORRIS_PLAYER_R, 8));
    EXPECT_TRUE(SixBoard.Remove(SIX_MENS_MORRIS_PLAYER_R, 9));
    // std::cout << SixBoard.ToString() << std::endl;
    EXPECT_EQ(
        std::string(SixBoard),
        " RU:0 RC:4 >WU:0 WC:2\n"
        "R---------o---------W      0---1---2\n"
        "|         |         |      | 3-4-5 |\n"
        "|         |         |      6-7   8-9\n"
        "|    R----R----R    |      | A-B-C |\n"
        "|    |         |    |      D---E---F\n"
        "|    |         |    |        LEGEND\n"
        "o----o         o----o\n"
        "|    |         |    |\n"
        "|    |         |    |\n"
        "|    o----o----o    |\n"
        "|         |         |\n"
        "|         |         |\n"
        "o---------W---------o\n"
    );
}
                                       
TEST(SixMensMorrisBoardTest, TwoPieceGameOverTest){
    CSixMensMorrisBoard SixEmptyBoard = CSixMensMorrisBoard();
    EXPECT_FALSE(SixEmptyBoard.GameOver());
    // Needs to test that game over is correct when only two pieces left
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0, 1};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[8] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[3] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[8] = previous[0xE] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_R, unplaced, positions, previous);
    EXPECT_TRUE(SixBoard.GameOver());
}

TEST(SixMensMorrisBoardTest, NoMoveGameOverTest){
    // Needs to test that game over is correct when no movement allowed
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0, 0};
    char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY};
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[4] = positions[8] = positions[0xF] = SIX_MENS_MORRIS_PLAYER_R;
    positions[1] = positions[2] = positions[9] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[4] = previous[8] = SIX_MENS_MORRIS_PLAYER_R;
    previous[1] = previous[2] = previous[9] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard SixBoard(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    EXPECT_TRUE(SixBoard.GameOver());

    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; ++i) {
        positions[i] = previous[i] = SIX_MENS_MORRIS_EMPTY;
    }
    positions[0] = positions[1] = positions[6] = positions[0xD] = SIX_MENS_MORRIS_PLAYER_R;
    positions[2] = positions[5] = positions[7] = positions[9] = positions[0xE] = SIX_MENS_MORRIS_PLAYER_W;
    previous[0] = previous[1] = previous[6] = SIX_MENS_MORRIS_PLAYER_R;
    previous[2] = previous[5] = previous[7] = previous[9] = previous[0xE] = SIX_MENS_MORRIS_PLAYER_W;
    CSixMensMorrisBoard noMove(SIX_MENS_MORRIS_PLAYER_W, unplaced, positions, previous);
    // std::cout << noMove.ToString() << std::endl;
    EXPECT_TRUE(noMove.Move(SIX_MENS_MORRIS_PLAYER_W, 5, 4));
    // std::cout << noMove.PlayerTurn() << std::endl;
    // std::cout << noMove.ToString() << std::endl;
    EXPECT_TRUE(noMove.GameOver());
}

TEST(SixMensMorrisBoardTest, BadParametersTest){
    // Needs to test that correct return upon bad parameters
    CSixMensMorrisBoard SixBoard = CSixMensMorrisBoard();
    EXPECT_EQ(SixBoard.PlayerAtPosition(-1), '\0');
    EXPECT_EQ(SixBoard.PlayerAtPosition(20), '\0');
    EXPECT_EQ(SixBoard.UnplacedPieces('E'), -1);
    EXPECT_EQ(SixBoard.UnplacedPieces('A'), -1);
    EXPECT_FALSE(SixBoard.CanMove('E', 10));
    EXPECT_FALSE(SixBoard.CanMove(SIX_MENS_MORRIS_PLAYER_R, 200));
    EXPECT_FALSE(SixBoard.Remove('e', 10));
    EXPECT_FALSE(SixBoard.Remove(SIX_MENS_MORRIS_PLAYER_R, 100));
}

