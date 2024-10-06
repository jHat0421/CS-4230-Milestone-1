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
  //bool check_end(); //check board to make sure both kings are alive, true if one is missing, game over
  //bool try_move(); //execute move, true if success, false if fail
 
};

#endif