#include <optional>

#include<string>

#include<tuple>

#include<regex>

#include"chess_game.h"

std::optional<std::array<int, 4>> get_input();

void play_game(chess_game* game)
{
    std::cout << "Starting Game!" << std::endl;
    std::cout << "(Input 'q' to Quit)" << std::endl;

    while (true) 
    {
        std::cout << std::endl;
        game->print_board();
        std::cout << std::endl;

        //print active players turn
        if (game->get_player())
        {
            std::cout << "White Player's Turn:" << std::endl;
        }
        else
        {
            std::cout << "Black Player's Turn:" << std::endl;
        }

        std::cout << "Enter your move in chess notation ex 'a4-b6':" << std::endl;

        //loop until successful move is made or quit
        while(true) {

            //call get input to handle input
            std::optional<std::array<int, 4>> input = get_input();
            std::cout<<"input received"<< std::endl;
            
            //if no input returned quit game
            if (!input) {
                std::cout << "Quitting Game" << std::endl;
                return;
            }
            // attempt to make move
            bool success = game->check_move((*input)[0],(*input)[1], (*input)[2], (*input)[3]);
            if(success){
                break;
            }
            else {
                std::cout << "the move was unsuccessful - try again" << std::endl;
            }
            break;
        }
        


        // game over condition -- a king is missing
        if (game->check_end()) {
            std::cout << "Quitting Game" << std::endl;
            return;
        }

        //check for check notify if a king is in check
        if (game->is_in_check()) {
            std::cout << "king is in check" << std::endl;
        }
        
        //next round
        game->pass_turn();
    }
}

// Returns array of coordinates, or null if 'q'
std::optional<std::array<int, 4>> get_input() {

    //loop until valid input received
    while(true) 
    {
        std::string input;
        getline(std::cin, input);
        if (input == "q") 
        {
            return std::nullopt;  // Return no value for quit
        }
        else
        {
            // Regular expression for chess notation (e.g., "a4-b4")
            std::regex notationPattern("^([a-h][1-8])-([a-h][1-8])$");
            std::smatch match_results;

            // Check if the input matches the pattern
            if (std::regex_match(input, match_results, notationPattern)) {
                //take the ascii character number, translate to an int
                int old_x = match_results.str(1)[0] - 'a' + 1;
                int old_y = match_results.str(1)[1] - '0';
                int new_x = match_results.str(2)[0] - 'a' + 1;
                int new_y = match_results.str(2)[1] - '0';

                return std::array{old_x, old_y, new_x, new_y};
            } else {
                std::cout << "invalid input - try again" << std::endl;
            }
        }
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