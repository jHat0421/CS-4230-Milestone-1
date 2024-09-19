#include <iostream>
#include <array>
#include "chess.h"
using namespace std;

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
    // check if new position is within board
    if (newPos < 0 && newPos > 63) {
        cout << "Invalid move: destination is outside the board!" << endl;
        return;
    }
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
