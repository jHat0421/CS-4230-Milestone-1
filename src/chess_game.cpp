#include "chess_game.h"

bool is_white(Piece piece)
{
    return piece >= KING_WHITE && piece <= PAWN_WHITE;
}

bool is_black(Piece piece)
{
    return piece >= KING_BLACK && piece <= PAWN_BLACK;
}

bool is_path_clear(int old_x, int old_y, int new_x, int new_y, const chess_board& board)
{
    // Determine if the movement is vertical, horizontal, or diagonal
    int delta_x = new_x - old_x;
    int delta_y = new_y - old_y;

    // Horizontal movement
    if (delta_y == 0) 
    {
        int direction = (delta_x > 0) ? 1 : -1;  // Right or left
        for (int i = old_x + direction; i != new_x; i += direction) 
        {
            if (board.get_piece(i, old_y) != EMPTY) 
            {
                return false;  // A piece is blocking the path
            }
        }
    }
    // Vertical movement
    else if (delta_x == 0) 
    {
        int direction = (delta_y > 0) ? 1 : -1;  // Up or down
        for (int i = old_y + direction; i != new_y; i += direction) 
        {
            if (board.get_piece(old_x, i) != EMPTY) 
            {
                return false;  // A piece is blocking the path
            }
        }
    }
    // Diagonal movement
    else if (abs(delta_x) == abs(delta_y)) 
    {
        int direction_x = (delta_x > 0) ? 1 : -1;  // Right or left
        int direction_y = (delta_y > 0) ? 1 : -1;  // Up or down

        for (int i = 1; i < abs(delta_x); ++i) 
        {
            if (board.get_piece(old_x + i * direction_x, old_y + i * direction_y) != EMPTY) 
            {
                return false;  // A piece is blocking the diagonal path
            }
        }
    }
    // Knight's move, path-checking not needed, but it can't land on an occupied square
    else if ((abs(delta_x) == 2 && abs(delta_y) == 1) || (abs(delta_x) == 1 && abs(delta_y) == 2)) 
    {
        return board.get_piece(new_x, new_y) == EMPTY || 
               (is_white(board.get_piece(old_x, old_y)) != is_white(board.get_piece(new_x, new_y)));
    }

    return true;  // No pieces in the path
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
            return ((delta_x == 0 || delta_y == 0 || abs(delta_x) == abs(delta_y)) && is_path_clear(old_x, old_y, new_x, new_y, board));

        case ROOK_WHITE:
        case ROOK_BLACK:
            return ((delta_x == 0 || delta_y == 0) && is_path_clear(old_x, old_y, new_x, new_y, board));

        case BISHOP_WHITE:
        case BISHOP_BLACK:
            return (abs(delta_x) == abs(delta_y) && is_path_clear(old_x, old_y, new_x, new_y, board));

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

void chess_game::promote_pawn(int x, int y)
{
    Piece piece = board.get_piece(x,y);

    if (piece == PAWN_WHITE && x == 7)
    {
        board.set_piece(x,y,QUEEN_WHITE);
    }
    else if (piece == PAWN_BLACK && x == 0)
    {
        board.set_piece(x,y,QUEEN_BLACK);
    }
}