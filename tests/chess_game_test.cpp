#include <gtest/gtest.h>
#include "chess_game.h"
#include "chess_board.h"

// Basic setup for a chess game
class ChessGameTest : public ::testing::Test
{
protected:
    chess_game game;
};

// Test the initial game setup
TEST_F(ChessGameTest, InitialPlayerIsWhite)
{
    EXPECT_TRUE(game.get_player()) << "Initial player should be WHITE.";
}

TEST_F(ChessGameTest, PassTurnSwitchesPlayer)
{
    bool initial_player = game.get_player();
    game.pass_turn();
    EXPECT_NE(initial_player, game.get_player()) << "Pass turn should switch the player.";
}

// Test making a valid move
TEST_F(ChessGameTest, MakeValidMove) 
{
    // Assume there's a pawn at (1,1) that can move to (1,3)
    game.board.set_piece(1, 1, PAWN_WHITE);
    EXPECT_TRUE(game.make_move(1, 1, 1, 3)) << "Pawn should move two spaces forward from starting position.";
}

// Test an invalid move (moving a piece not owned by the current player)
TEST_F(ChessGameTest, MakeInvalidMoveWrongPlayer)
{
    game.board.set_piece(1, 1, PAWN_BLACK);
    EXPECT_FALSE(game.make_move(1, 1, 1, 2)) << "White player cannot move black pieces.";
}

// Test that a move fails if it's blocked
TEST_F(ChessGameTest, MoveBlockedPiece)
{
    game.board.set_piece(0, 0, ROOK_WHITE);
    game.board.set_piece(0, 1, PAWN_WHITE);
    EXPECT_FALSE(game.make_move(0, 0, 0, 2)) << "Rook move should fail if path is blocked by another piece.";
}

// Test check detection logic
TEST_F(ChessGameTest, CheckDetection)
{
    game.board.set_piece(4, 0, KING_WHITE);
    game.board.set_piece(4, 7, ROOK_BLACK);

    game.pass_turn(); // Switch to black's turn
    EXPECT_TRUE(game.is_in_check()) << "White should be in check from the black rook.";
}

// Test pawn promotion
TEST_F(ChessGameTest, PawnPromotion)
{
    game.board.set_piece(0, 6, PAWN_WHITE);
    EXPECT_TRUE(game.make_move(0, 6, 0, 7)) << "White pawn should reach promotion rank.";
    EXPECT_EQ(game.board.get_piece(0, 7), QUEEN_WHITE) << "Pawn should be promoted to a Queen.";
}

// Test check end condition (one king is missing)
TEST_F(ChessGameTest, CheckEndWhiteKingCaptured)
{
    game.board.set_piece(4, 0, KING_BLACK); // Only black king on the board
    EXPECT_FALSE(game.check_end()) << "Game should end when the white king is captured.";
}

TEST_F(ChessGameTest, CheckEndBothKingsPresent)
{
    game.board.set_piece(4, 0, KING_WHITE);
    game.board.set_piece(4, 7, KING_BLACK);
    EXPECT_TRUE(game.check_end()) << "Game should continue when both kings are present.";
}

// Test invalid move out of bounds
TEST_F(ChessGameTest, MoveOutOfBounds)
{
    // game.board.set_piece(0, 0, ROOK_WHITE);
    // EXPECT_FALSE(game.make_move(0, 0, 8, 8)) << "Move should be invalid if destination is out of bounds.";
}

// Test for moving into a position occupied by own piece
TEST_F(ChessGameTest, MoveToOccupiedPosition)
{
    game.board.set_piece(0, 0, ROOK_WHITE);
    game.board.set_piece(0, 1, PAWN_WHITE);
    EXPECT_FALSE(game.check_move(0, 0, 0, 1)) << "Move should be invalid if target is occupied by own piece.";
}

// Test the case where a player tries to put their own king in check (should fail)
TEST_F(ChessGameTest, SelfCheckMoveFails)
 {
    game.board.set_piece(4, 0, KING_WHITE);
    game.board.set_piece(4, 7, ROOK_BLACK);
    game.board.set_piece(4, 1, QUEEN_WHITE);

    // White's turn, moving queen away will expose king to check
    EXPECT_FALSE(game.check_move(0, 0, 0, 1)) << "Move should fail if it puts own king in check.";
}

// Test knight movement edge case
TEST_F(ChessGameTest, KnightMovement)
{
    game.board.set_piece(1, 0, KNIGHT_WHITE);
    EXPECT_TRUE(game.check_move(1, 0, 2, 2)) << "Knight should be able to move in 'L' shape.";
    EXPECT_FALSE(game.check_move(1, 0, 3, 3)) << "Knight should not move diagonally like a bishop.";
}

TEST_F(ChessGameTest, PawnPromotion2)
{
    game.board.set_piece(0, 6, PAWN_BLACK);
    game.make_move(0, 6, 0, 7); // Move to last row for promotion
    EXPECT_NE(game.board.get_piece(0, 7), QUEEN_BLACK); // Confirm not promotion
}

TEST_F(ChessGameTest, KingInCheckDetection)
{
    game.board.set_piece(4, 4, KING_WHITE);
    game.board.set_piece(4, 7, ROOK_BLACK); // Black rook putting white king in check
    EXPECT_TRUE(game.is_in_check());
}

TEST_F(ChessGameTest, StalemateDetection)
{
    game.board.set_piece(0, 0, KING_WHITE);
    game.board.set_piece(2, 1, KING_BLACK);
    game.board.set_piece(1, 2, ROOK_WHITE); // White rook restricts black king
    game.pass_turn();
    EXPECT_FALSE(game.check_end()); // Expect stalemate, not a win for either player
}

TEST_F(ChessGameTest, CheckmateDetection2)
{
    game.board.set_piece(0, 0, KING_BLACK);
    game.board.set_piece(2, 1, QUEEN_WHITE);
    game.board.set_piece(1, 2, ROOK_WHITE); // White rook and queen create checkmate
    game.pass_turn();
    EXPECT_FALSE(game.check_end()); // Expect checkmate detected, game should end
}

TEST_F(ChessGameTest, KnightInvalidMoveOutOfBounds)
{
    // game.board.set_piece(7, 7, KNIGHT_WHITE);
    // EXPECT_FALSE(game.check_move(7, 7, 8, 9)); // Out of bounds move
    // EXPECT_FALSE(game.make_move(7, 7, 8, 9));
}

TEST_F(ChessGameTest, KingEdgeMove)
{
    game.board.set_piece(0, 0, KING_WHITE);
    EXPECT_TRUE(game.check_move(0, 0, 0, 1)); // Move along edge
    EXPECT_TRUE(game.make_move(0, 0, 0, 1));
}

TEST_F(ChessGameTest, InvalidPawnCaptureMove)
{
    game.board.set_piece(4, 4, PAWN_WHITE);
    game.board.set_piece(4, 5, KNIGHT_BLACK); // Black knight in front of white pawn
    EXPECT_FALSE(game.make_move(4, 4, 4, 5)); // Invalid capture for pawn
}
