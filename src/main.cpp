#include<string>
#include<tuple>
#include<regex>

#include"chess_game.h"

// Returns array of coordinates, or null if 'q'
std::array<int, 4> get_input() 
{
    std::array<int, 4> null_array = {-1, -1, -1, -1};

    // Loop until valid input received:
    while(true)
    {
        std::string input;
        getline(std::cin, input);
        if (input == "q") 
        {
            // Return no value for quit:
            return null_array;
        }
        else
        {
            // Regular expression for chess notation (e.g., "a4-b4"):
            std::regex notation_pattern("^([a-h][1-8])-([a-h][1-8])$");
            std::smatch match_results;

            // Check if the input matches the pattern:
            if (std::regex_match(input, match_results, notation_pattern)) 
            {
                // Translate ASCII to corresponding int:
                int old_x = match_results.str(1)[0] - 'a';
                int old_y = match_results.str(1)[1] - '0'-1;
                int new_x = match_results.str(2)[0] - 'a';
                int new_y = match_results.str(2)[1] - '0'-1;

                std::array<int, 4> result = {old_x, old_y, new_x, new_y};
                return result;
            }
            else
            {
                std::cout << "Re-enter your move in lowercase chess notation or 'q' to quit (ex: 'a4-b6'):" << std::endl;
            }
        }
    }
}

// Main game loop:
void play_game(chess_game* game)
{
    std::array<int, 4> null_array = {-1, -1, -1, -1};

    std::cout << "Starting Game!" << std::endl;
    std::cout << "(Input 'q' to Quit)" << std::endl;

    while (true) 
    {
        std::cout << std::endl;
        game->print_board();
        std::cout << std::endl;

        // Print active players turn:
        if (game->get_player())
        {
            std::cout << "White Player's Turn:" << std::endl;
        }
        else
        {
            std::cout << "Black Player's Turn:" << std::endl;
        }

        std::cout << "Enter your move in lowercase chess notation or 'q' to quit (ex: 'a4-b6'):" << std::endl;

        // Loop until successful move is made or quit
        while(true) 
        {
            // Call formatted input handler:
            std::array<int, 4> input = get_input();
            
            // If null input returned ('q' selection), exit game:
            if (input == null_array)
            {
                std::cout << "Quitting game!" << std::endl;
                return;
            }

            // Attempt to make move:
            if(game->make_move((input)[0],(input)[1], (input)[2], (input)[3]))
            {
                //continue
                break;
            }
            else 
            {
                //retry input
                std::cout << "Re-nter a valid move in lowercase chess notation or 'q' to quit (ex: 'a4-b6'):" << std::endl;
            }
        }
        
        // Check game over condition (eihter king missing):
        if (!game->check_end())
        {
            std::cout << "Quitting Game" << std::endl;
            return;
        }

        // Check for check:
        if (game->is_in_check()) {
            std::cout << "King is in Check!" << std::endl;
        }
        
        // End player turn;
        game->pass_turn();
    }
}

/*
// DEBUG MAIN
int main()
{
    chess_game game = chess_game();
    game.print_board();
    std::cout << game.board.get_piece(0,6);

    std::array<int, 4> input = get_input();
    input = to_array_space(input);
    std::cout << input[0] << std::endl;
    std::cout << input[1] << std::endl;
    std::cout << input[2] << std::endl;
    std::cout << input[3] << std::endl;
    
    return 0;
}
*/

int main()
{
    // Create Game:
    chess_game game = chess_game();

    // Play Game:
    play_game(&game);

    // End Game:
    return 0;
}
