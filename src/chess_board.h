#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include<iostream>
#include<array>

enum Piece
{ 
  EMPTY=0, KING_WHITE, QUEEN_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE, PAWN_WHITE,
  KING_BLACK, QUEEN_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK, PAWN_BLACK
};

class chess_board 
{
private:
  std::array<std::array<Piece, 8>, 8> board;

public:
  chess_board();
  Piece get_piece(int x, int y) const;
  void set_piece(int x, int y, Piece piece);
  void move_piece(int old_x, int old_y, int new_x, int new_y);
  void print_board();
};

#endif