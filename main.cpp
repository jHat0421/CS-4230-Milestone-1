//#include <iostate>
#include "chess.h"
#include "chessBoard.cpp"
#include "chess.cpp"

using namespace std;

int main() {
    ChessBoard myBoard = ChessBoard();
    ChessGame game = ChessGame();
    myBoard.printBoard();
    return 0;
} 
