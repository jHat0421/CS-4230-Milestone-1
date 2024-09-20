#include <iostream>
#include <array>
#include "chess.h"
using namespace std;

//puts all pieces in their starting positions
void ChessBoard::setBoard(){
    cout << "Setting board" << endl;

    //place white
    chessBoard[0] = {ROOK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, KING_WHITE, QUEEN_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE};
    for (int i = 0; i<8; i++) 
    {
        chessBoard[1][i] = PAWN_WHITE;
    }

    //place black
    chessBoard[7] = {ROOK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, KING_BLACK, QUEEN_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK};
    for (int i = 0; i<8; i++) 
    {
        chessBoard[6][i] = PAWN_BLACK;
    }
}

//returns the piece in specified position
Piece ChessBoard::getPiece(int x, int y) {
    return chessBoard[x][y];
}

//moves piece from old position to new, sets old to NONE
void ChessBoard::movePiece(int oldX, int oldY, int newX, int newY) {
    // check if new position is within board
    chessBoard[newX][newY] = chessBoard[oldX][oldY];
    chessBoard[oldX][oldY] = EMPTY;
}

//prints the chess board
void ChessBoard::printBoard(){
    for (int i = 7; i>=0; i--) {
        for (int j = 7; j>=0; j--) {
            cout << chessBoard[i][j];
        }
        cout << endl;
    }
}
