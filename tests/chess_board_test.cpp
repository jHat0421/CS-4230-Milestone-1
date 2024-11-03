#include <gtest/gtest.h>
#include "chess_board.h"

// Test T01: Decision Table - Move a piece to an empty square
TEST(ChessBoardTest, MoveToEmptySquare) {
    chess_board board;
    board.move_piece(0, 1, 0, 2);  // Move a white pawn from (0, 1) to (0, 2)
    EXPECT_EQ(board.get_piece(0, 2), PAWN_WHITE);  // Destination should now have the white pawn
    EXPECT_EQ(board.get_piece(0, 1), EMPTY);       // Original square should be empty
}

// Test T02: Pairwise Testing - Set and Get Piece after moving it
TEST(ChessBoardTest, SetAndGetPieceAfterMove) {
    chess_board board;
    board.set_piece(0, 4, QUEEN_WHITE);  // Place a white queen at (0, 4)
    board.move_piece(0, 4, 4, 4);        // Move the queen from (0, 4) to (4, 4)
    EXPECT_EQ(board.get_piece(4, 4), QUEEN_WHITE);  // New position should have the queen
    EXPECT_EQ(board.get_piece(0, 4), EMPTY);        // Original position should now be empty
}

// Test T03: State Transition - Ensure the square is empty after moving a piece
TEST(ChessBoardTest, SquareIsEmptyAfterMove) {
    chess_board board;
    board.move_piece(1, 1, 1, 2);  // Move a white pawn from (1, 1) to (1, 2)
    EXPECT_EQ(board.get_piece(1, 1), EMPTY);       // Original square should be empty
    EXPECT_EQ(board.get_piece(1, 2), PAWN_WHITE);  // New square should contain the white pawn
}

// Test T04: Use Case - Check Initial Board Setup
TEST(ChessBoardTest, CheckBoardInitialization) {
    chess_board board;
    EXPECT_EQ(board.get_piece(0, 0), ROOK_WHITE);   // White rook at bottom-left
    EXPECT_EQ(board.get_piece(7, 0), ROOK_WHITE);   // White rook at bottom-right
    EXPECT_EQ(board.get_piece(0, 7), ROOK_BLACK);   // Black rook at top-left
    EXPECT_EQ(board.get_piece(7, 7), ROOK_BLACK);   // Black rook at top-right
    // Additional assertions can be added to verify complete board initialization
}

// Test T05: Exploratory Testing - Check Printed Board Layout
TEST(ChessBoardTest, PrintInitialBoard) {
    chess_board board;
    testing::internal::CaptureStdout();
    board.print_board();
    std::string output = testing::internal::GetCapturedStdout();

    // Verify that rows and pieces are correctly represented in the printed board layout
    EXPECT_NE(output.find("8 | r | n | b | q | k | b | n | r |"), std::string::npos); // Top row for black pieces
    EXPECT_NE(output.find("7 | p | p | p | p | p | p | p | p |"), std::string::npos); // Row of black pawns
    EXPECT_NE(output.find("2 | P | P | P | P | P | P | P | P |"), std::string::npos); // Row of white pawns
    EXPECT_NE(output.find("1 | R | N | B | Q | K | B | N | R |"), std::string::npos); // Bottom row for white pieces

    // Verify that row and column labels appear as expected
    EXPECT_NE(output.find("     A   B   C   D   E   F   G   H"), std::string::npos); // Top and bottom column labels
}

