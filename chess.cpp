#include <iostream>
#include <array>
#include "chess.h"

using namespace std;

// ChessGame constructor
ChessGame::ChessGame() {
    // Initialize the currentPlayer to true (White to move first)
    currentPlayer = true;
}

//checkMove helper function to check if the path between start and end for sliding pieces (rook, bishop, queen) is clear
bool isPathClear(ChessBoard& board, int oldX, int oldY, int newX, int newY) {
    int dx = (newX - oldX) > 0 ? 1 : ((newX - oldX) < 0 ? -1 : 0);
    int dy = (newY - oldY) > 0 ? 1 : ((newY - oldY) < 0 ? -1 : 0);
    
    int x = oldX + dx;
    int y = oldY + dy;

    while (x != newX || y != newY) {
        if (board.getPiece(x, y) != EMPTY) {
            return false;
        }
        x += dx;
        y += dy;
    }
    return true;
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

    //get piece at current position oldX and oldY. 
    Piece piece = board.getPiece(oldX, oldY);

    //get piece's target location at newX and newY. 
    Piece target = board.getPiece(newX, newY);

    //ensure a piece isn't at an empty space. 
    if (piece == EMPTY) {
        cout << "Invalid move: No piece at the starting position." << endl;
        return false;
    }
    // Check if the move is inside the board
    if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
        return false; // Out of bounds
    }

    int deltaX = newX - oldX;
    int deltaY = newY - oldY;

    switch (piece) {

        //Check King Movement
        case KING_WHITE:
        case KING_BLACK:
            // King moves one square in any direction
            return (abs(deltaX) <= 1 && abs(deltaY) <= 1);

        //Check Queen Movement
        case QUEEN_WHITE:
        case QUEEN_BLACK:
            // Queen moves like a rook or bishop
            if ((deltaX == 0 || deltaY == 0 || abs(deltaX) == abs(deltaY)) && isPathClear(board, oldX, oldY, newX, newY)) {
                return true;
            }
            return false;
        //Check Rook Movement
        case ROOK_WHITE:
        case ROOK_BLACK:
            // Rook moves in straight lines
            return ((deltaX == 0 || deltaY == 0) && isPathClear(board, oldX, oldY, newX, newY));

        //Check Bishop Movement
        case BISHOP_WHITE:
        case BISHOP_BLACK:
            // Bishop moves diagonally
            return (abs(deltaX) == abs(deltaY) && isPathClear(board, oldX, oldY, newX, newY));

        //Check Knight Movement
        case KNIGHT_WHITE:
        case KNIGHT_BLACK:
            // Knight moves in "L" shape: 2 in one direction and 1 in the other
            return (abs(deltaX) == 2 && abs(deltaY) == 1) || (abs(deltaX) == 1 && abs(deltaY) == 2);

        //Check White Pawn
        case PAWN_WHITE:
            // Pawn moves one step forward or two if it's the first move, and captures diagonally
            if (deltaY == 0 && board.getPiece(newX, newY) == EMPTY) {
                if (oldX == 1 && deltaX == 2) return true; // Two-step move for white pawns
                return (deltaX == 1); // Single step move for white pawns
            } else if (abs(deltaY) == 1 && deltaX == 1 && isBlack(target)) {
                return true; // Capture move for white pawns
            }
            return false;
        //Check Black Pawn
        case PAWN_BLACK:
            // Pawn moves one step forward or two if it's the first move, and captures diagonally
            if (deltaY == 0 && board.getPiece(newX, newY) == EMPTY) {
                if (oldX == 6 && deltaX == -2) return true; // Two-step move for black pawns
                return (deltaX == -1); // Single step move for black pawns
            } else if (abs(deltaY == 1 && deltaX == -1 && isWhite(target))) {
                return true; // Capture move for black pawns
            }
            return false;
        default:
            return false;
    }
}

void ChessGame::getMove(ChessBoard& board) 
{
    int oldX, oldY, newX, newY;
    bool moveValid = false;

    // Loop until a valid move is entered
    while (!moveValid) 
    {
        // Prompt the player for input
        cout << "Enter your move in the format oldX oldY newX newY: ";
        cin >> oldX >> oldY >> newX >> newY;

        // Validate the move using checkMove
        moveValid = checkMove(board, oldX, oldY, newX, newY);

        if (!moveValid) 
        {
            cout << "Invalid move. Please try again." << endl;
        }
    }

    // Perform the move on the board if valid
    board.movePiece(oldX, oldY, newX, newY);
    
    // Switch player after a valid move
    currentPlayer = !currentPlayer;
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
                return true;  // King is in check
            }
        }
    }
    return false;  // King is not in check
}

