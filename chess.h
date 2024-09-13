#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <string>

// Enum to represent different piece types
enum class ChessPiece { King, Queen, Rook, Bishop, Knight, Pawn, None };

// Enum to represent colors
enum class Color { White, Black, None };

// Class to represent a chess piece
class Piece {
  ChessPiece type;
  Color color;
}

//Class to represent chess board
class ChessBoard {
  public:
    void ChessBoard(div,med);
    Piece getPiece();
    void setPiece();
}

//Class to represent game logic
class ChessGame {
  private:

  public:
    ChessGame();
    Color currentPlayer; //Keeps track of current player
    void checkMove(); //Keep track of game logic
    void GetMove();
    void CheckCheck(); //Checks for check. 
}



#endif // CHESS_H
