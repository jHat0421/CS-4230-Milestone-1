#include<optional>
#include<string>
#include<tuple>
#include<regex>

#include"chess_game.h"

// Converts chess's standard bottom left origin grid to a top left origin grid:
std::array<int, 4> to_array_space(std::array<int, 4> input_coords) 
{
    std::array<int, 4> output_coords;
    
    // x-coordinates remain unchanged:
    output_coords[0] = input_coords[0];
    output_coords[2] = input_coords[2];

    // y-coordinates are inverted:
    output_coords[1] = 8 - input_coords[1];
    output_coords[3] = 8 - input_coords[3];

    return output_coords;
}

// Returns array of coordinates, or null if 'q'
std::optional<std::array<int, 4>> get_input() 
{
    // Loop until valid input received:
    while(true) 
    {
        std::string input;
        getline(std::cin, input);
        if (input == "q") 
        {
            // Return no value for quit:
            return std::nullopt;
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
                int old_x = match_results.str(1)[0] - 'a' + 1;
                int old_y = match_results.str(1)[1] - '0';
                int new_x = match_results.str(2)[0] - 'a' + 1;
                int new_y = match_results.str(2)[1] - '0';

                return std::array{old_x, old_y, new_x, new_y};
            }
            else 
            {
                std::cout << "Invalid input, please try again." << std::endl;
            }
        }
    }   
}

// Main game loop:
void play_game(chess_game* game)
{
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

        std::cout << "Enter your move in chess notation (ex: 'a4-b6'):" << std::endl;

        // Loop until successful move is made or quit
        while(true) 
        {
            // Call formatted input handler:
            std::optional<std::array<int, 4>> input = get_input();
            std::cout << "Input received." << std::endl;
            
            // If null input returned ('q' selection), exit game:
            if (!input) 
            {
                std::cout << "Quitting game." << std::endl;
                return;
            }

            // Attempt to make move:
            if(game->check_move((*input)[0],(*input)[1], (*input)[2], (*input)[3]))
            {
                break;
            }
            else 
            {
                std::cout << "Invalid move, please try again." << std::endl;
            }
            break;
        }
        
        // Check game over condition (eihter king missing):
        if (game->check_end()) 
        {
            std::cout << "Quitting Game" << std::endl;
            return;
        }

        // Check for check:
        if (game->is_in_check()) {
            std::cout << "king is in check" << std::endl;
        }
        
        // End player turn;
        game->pass_turn();
    }
}



int main()
{
    // Create Game:
    chess_game game = chess_game();

    // Play Game:
    play_game(&game);

    // End Game:
    return 0;
}