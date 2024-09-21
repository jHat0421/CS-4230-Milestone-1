//#include <iostate>
#include "chess.cpp"
#include "chessBoard.cpp"

using namespace std;

int main() {
    ChessBoard myBoard = ChessBoard();
    myBoard.printBoard();
    cout << myBoard.getPiece(0,7);
    printf("♔");
    return 0;
} 
