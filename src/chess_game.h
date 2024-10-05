#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "chess_board.h"

#define WHITE (0)
#define BLACK (1)

class chess_game
{
private:
  chess_board board;
  bool current_player;

public:
  chess_game();

  void pass_turn();
  void print_board();
  bool check_move(int old_x, int old_y, int new_x, int new_y);
  // void get_move();
  //bool is_in_check();
};

#endif