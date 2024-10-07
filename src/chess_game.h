#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "chess_board.h"

#define WHITE (1)
#define BLACK (0)

class chess_game
{
private:
  chess_board board;
  bool current_player;

public:
  chess_game();

  void pass_turn();
  void print_board();
  bool get_player();
  bool check_move(int old_x, int old_y, int new_x, int new_y);
  bool is_in_check();
  void promote_pawn(int x, int y);
  bool check_end();
 
};

#endif