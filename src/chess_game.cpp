#include "chess_game.h"

bool is_path_clear(int old_x, int old_y, int new_x, int new_y)
{
    return true;
}

bool is_white(Piece piece)
{
    return piece >= KING_WHITE && piece <= PAWN_WHITE;
}

bool is_black(Piece piece)
{
    return piece >= KING_BLACK && piece <= PAWN_BLACK;
}

chess_game::chess_game()
{
    current_player = WHITE;
}

void chess_game::pass_turn()
{
    current_player = !current_player;
}

void chess_game::print_board()
{
    board.print_board();
}

bool chess_game::get_player()
{
    return current_player;
}

bool chess_game::check_move(int old_x, int old_y, int new_x, int new_y) 
{
    Piece piece = board.get_piece(old_x, old_y);
    Piece target = board.get_piece(new_x, new_y);

    if (piece == EMPTY) {
        std::cout << "Invalid move: No piece at the starting position." << std::endl;
        return false;
    }

    if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8) 
    {
        return false;
    }

    int delta_x = new_x - old_x;
    int delta_y = new_y - old_y;

    switch (piece) 
    {
        case KING_WHITE:
        case KING_BLACK:
            return (abs(delta_x) <= 1 && abs(delta_y) <= 1);

        case QUEEN_WHITE:
        case QUEEN_BLACK:
            return ((delta_x == 0 || delta_y == 0 || abs(delta_x) == abs(delta_y)) && is_path_clear(old_x, old_y, new_x, new_y));

        case ROOK_WHITE:
        case ROOK_BLACK:
            return ((delta_x == 0 || delta_y == 0) && is_path_clear(old_x, old_y, new_x, new_y));

        case BISHOP_WHITE:
        case BISHOP_BLACK:
            return (abs(delta_x) == abs(delta_y) && is_path_clear(old_x, old_y, new_x, new_y));

        case KNIGHT_WHITE:
        case KNIGHT_BLACK:
            return (abs(delta_x) == 2 && abs(delta_y) == 1) || (abs(delta_x) == 1 && abs(delta_y) == 2);

        case PAWN_WHITE:
            if (delta_y == 0 && board.get_piece(new_x, new_y) == EMPTY) 
            {
                if (old_x == 1 && delta_x == 2) return true;
                return (delta_x == 1);
            }
            else if (abs(delta_y) == 1 && delta_x == 1 && is_black(target)) 
            {
                return true;
            }
            return false;

        case PAWN_BLACK:
            if (delta_y == 0 && board.get_piece(new_x, new_y) == EMPTY) 
            {
                if (old_x == 6 && delta_x == -2) return true;
                return (delta_x == -1);
            }
            else if (abs(delta_y == 1 && delta_x == -1 && is_white(target))) 
            {
                return true;
            }
            return false;

        default:
            return false;
    }
}

bool chess_game::is_in_check() 
{
    int king_x = -1, king_y = -1;
    Piece king_piece = current_player ? KING_WHITE : KING_BLACK;

    // Find the current player's king on the board
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if (board.get_piece(i, j) == king_piece) 
            {
                king_x = i;
                king_y = j;
                break;
            }
        }
    }

    if (king_x == -1 || king_y == -1) 
    {
        std::cout << "Error: King not found on the board!" << std::endl;
        return false;
    }

    std::cout << "King found at (" << king_x << ", " << king_y << ")" << std::endl;

    // Check if any opponent's piece can move to the king's position
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            Piece opponent_piece = board.get_piece(i, j);

            // Skip empty squares and current player's pieces
            if (opponent_piece == EMPTY || (current_player && is_white(opponent_piece)) || (!current_player && is_black(opponent_piece))) 
            {
                continue;
            }

            // If any opponent piece can move to the king's position, the king is in check
            if (check_move(i, j, king_x, king_y)) 
            {
                std::cout << "King is in check by piece at (" << i << ", " << j << ")" << std::endl;
                return true;  // King is in check
            }
        }
    }

    std::cout << "King is not in check." << std::endl;
    return false;  // King is not in check
}