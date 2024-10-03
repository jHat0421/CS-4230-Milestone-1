//#include <iostate>
#include "chess.h"
#include "chessBoard.cpp"
#include "chess.cpp"

using namespace std;

int main() {
    ChessBoard myBoard = ChessBoard();
    myBoard.printBoard();
    cout << myBoard.getPiece(0,7);
    printf("♔");
    return 0;
} 
