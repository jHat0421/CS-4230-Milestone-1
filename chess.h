#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <string>
#include <array>

//enum which represents each chess piece or empty
enum Piece { EMPTY=0, KING_WHITE, QUEEN_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE, PAWN_WHITE,
    KING_BLACK, QUEEN_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK, PAWN_BLACK
};

//Class to represent chess board
class ChessBoard {
  public:
    std::array<std::array<Piece, 8>, 8> chessBoard = {EMPTY};
    void setBoard();
    void printBoard();
    Piece getPiece(int x, int y); //returns piece in position
    void movePiece(int oldX, int oldY, int newX, int newY); //move piece from old position to new position
    ChessBoard() {
        setBoard();
    }
};

//Class to represent game logic
class ChessGame {
  private:

  public:
    ChessGame();
    bool currentPlayer; //Keeps track of current player
    bool checkMove(ChessBoard& board, int oldX, int oldY, int newX, int newY); //Keep track of game logic
    void getMove();
    bool isInCheck(); //Checks for check. 
};



#endif // CHESS_H
