#include <iostream>
#include <array>
#include "chess.h"

using namespace std;

// ChessGame constructor
ChessGame::ChessGame() {
    // Initialize the currentPlayer to true (White to move first)
    currentPlayer = true;
}

//checkMove helper function to determine if a piece is white
bool isWhite(Piece piece) {
    return piece >= KING_WHITE && piece <= PAWN_WHITE;
}

//checkMove helper function to determine if a piece is black
bool isBlack(Piece piece) {
    return piece >= KING_BLACK && piece <= PAWN_BLACK;
}

// The checkMove function that verifies if a move is valid
bool ChessGame::checkMove(ChessBoard& board, int oldX, int oldY, int newX, int newY) {

    // Get the piece at the current position
    Piece piece = board.getPiece(oldX, oldY);
    // Get the piece at the target location
    Piece target = board.getPiece(newX, newY);

    // Ensure a piece is at the start location
    if (piece == EMPTY) {
        cout << "Invalid move: No piece at the starting position." << endl;
        return false;
    }
    // Ensure move is within board boundaries
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        cout << "Invalid move: Out of bounds." << endl;
        return false;
    }

    int deltaX = newX - oldX;
    int deltaY = newY - oldY;

    //TODO: Check for pieces that are in the way
    switch (piece) {
        case KING_WHITE:
        case KING_BLACK:
            //Moves one square vertically, horizontally, or vertically
            if (abs(deltaX) <= 1 && abs(deltaY) <= 1) 
            {
                return true;
            }
            return false;

        case QUEEN_WHITE:
        case QUEEN_BLACK:
            // Queen moves like a rook or bishop
            if (oldX == newX || oldY == newY || abs(oldX - newX) == abs(oldY - newY)) 
            {
                return true;
            }
            return false;

        case ROOK_WHITE:
        case ROOK_BLACK:
            //Vertical/Horizontal movement
            if ((deltaX == 0 || deltaY == 0)) 
            {
                return true;
            }
            return false;

        case BISHOP_WHITE:
        case BISHOP_BLACK:
            //Diagonal move
            if (abs(deltaX) == abs(deltaY)) 
            {
                return true;
            }
            return false;

        case KNIGHT_WHITE:
        case KNIGHT_BLACK:
            //Up/Down 2, Left/Right 1 OR Up/Down 1, Left/Right 2
            if ((abs(deltaX) == 2 && abs(deltaY) == 1) || (abs(deltaX) == 1 && abs(deltaY) == 2)) 
            {
                return true;
            }
            return false;

        case PAWN_WHITE:
            //Move straight vertically
            if (deltaY == 0 && board.getPiece(newX, newY) == EMPTY) 
            {
                //Two squares
                if (oldX == 1 && deltaX == 2) 
                {
                    return true;
                }
                //One Square
                if (deltaX == 1) {
                    return true;
                }
                
            } 
            //Capture Piece
            else if (abs(deltaY) == 1 && deltaX == 1 && isBlack(target)) 
            {
                return true;
            }
            return false;

        case PAWN_BLACK:
            //Move straight vertically
            if (deltaY == 0 && board.getPiece(newX, newY) == EMPTY) 
            {
                //Two Squares
                if (oldX == 6 && deltaX == -2) 
                {
                    return true;
                }
                //One Square
                if (deltaX == -1) 
                {
                    return true;
                }
            } 
            //Caputre Piece
            else if (abs(deltaY) == 1 && deltaX == -1 && isWhite(target)) 
            {
                return true;
            }
            return false;

        default:
            return false;
    }
}

bool ChessGame::isInCheck(ChessBoard& board) {
    int kingX = -1, kingY = -1;
    Piece kingPiece = currentPlayer ? KING_WHITE : KING_BLACK;

    // Find the current player's king on the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getPiece(i, j) == kingPiece) {
                kingX = i;
                kingY = j;
                break;
            }
        }
    }

    if (kingX == -1 || kingY == -1) {
        cout << "Error: King not found on the board!" << endl;
        return false;
    }

    cout << "King found at (" << kingX << ", " << kingY << ")" << endl;

    // Check if any opponent's piece can move to the king's position
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece opponentPiece = board.getPiece(i, j);

            // Skip empty squares and current player's pieces
            if (opponentPiece == EMPTY || (currentPlayer && isWhite(opponentPiece)) || (!currentPlayer && isBlack(opponentPiece))) {
                continue;
            }

            // If any opponent piece can move to the king's position, the king is in check
            if (checkMove(board, i, j, kingX, kingY)) {
                cout << "King is in check by piece at (" << i << ", " << j << ")" << endl;
                return true;  // King is in check
            }
        }
    }

    cout << "King is not in check." << endl;
    return false;  // King is not in check
}
