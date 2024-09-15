#include <iostream>
#include <array>
//#include "chess.h"
using namespace std;

//enum which represents each chess piece or empty
enum Piece { EMPTY=0, KING_WHITE, QUEEN_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE, PAWN_WHITE,
    KING_BLACK, QUEEN_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK, PAWN_BLACK
};

class ChessBoard {
  public:
    std::array<Piece, 64> chessBoard = {EMPTY};
    void setBoard();
    void printBoard();
    Piece getPiece(int); //returns piece in position
    void setPiece(int,int); //given position to given piece
    ChessBoard() {
        setBoard();
    }
};

//puts all pieces in their starting positions
void ChessBoard::setBoard(){
    //place white
    Piece whiteArray[8] = {
        ROOK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, KING_WHITE, QUEEN_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE
    };
    for (int i = 0; i<16; i++) {
        if (i<8) {
            chessBoard[i] = whiteArray[i];
        }
        else {
            chessBoard[i] = PAWN_WHITE;
        }
    }

    //place black
    Piece blackArray[8] = {
        ROOK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, QUEEN_BLACK, KING_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK
    };
    int j = 0;
    for (int i = 63; i>48; i--) {
        if (i>=56) {
            chessBoard[i] = PAWN_BLACK;
        }
        else {
            chessBoard[i] = blackArray[j];
            j++;
        }
    }

}
//returns the piece in specified position
Piece ChessBoard::getPiece(int pos) {
    return chessBoard[pos];
}

//moves piece from old position to new, sets old to NONE
void ChessBoard::setPiece(int oldPos,int newPos) {
    chessBoard[newPos] = chessBoard[oldPos];
    chessBoard[oldPos] = EMPTY;
}

//prints the chess board
void ChessBoard::printBoard(){
    for (int i = 0; i < 64; i++){
        cout << i << ":" << chessBoard[i] << " ";
    }
    cout << endl;
}


int main() {
    ChessBoard myBoard = ChessBoard();
    myBoard.printBoard();
    return 0;
} 