#include "chess_board.h"

chess_board::chess_board(): board
{
    {
        {ROOK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, QUEEN_BLACK, KING_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK},
        {PAWN_BLACK, PAWN_BLACK, PAWN_BLACK, PAWN_BLACK, PAWN_BLACK, PAWN_BLACK, PAWN_BLACK, PAWN_BLACK},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {PAWN_WHITE, PAWN_WHITE, PAWN_WHITE, PAWN_WHITE, PAWN_WHITE, PAWN_WHITE, PAWN_WHITE, PAWN_WHITE},
        {ROOK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, QUEEN_WHITE, KING_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE},
    }
} {}

Piece chess_board::get_piece(int x, int y) const
{
    return board[x][y];
}

void chess_board::set_piece(int x, int y, Piece piece) 
{
    board[x][y] = piece;
}

void chess_board::move_piece(int old_x, int old_y, int new_x, int new_y) 
{
    board[new_x][new_y] = board[old_x][old_y];
    board[old_x][old_y] = EMPTY;
}

void chess_board::print_board()
{
    std::array<char, 13> letters = {' ', 'K', 'Q', 'B', 'N', 'R', 'P', 'k', 'q', 'b', 'n', 'r', 'p'};
    
    std::cout << "     A   B   C   D   E   F   G   H  " << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << "   ---------------------------------" << std::endl;
        std::cout << " " << 8 - i << " | ";
        for (int j = 0; j < 8; j++)
        {
            std::cout << letters[board[i][j]];
            // std::cout << i << "," << j;
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << "   ---------------------------------" << std::endl << std::endl;
}