#include<string>

#include"chess_game.h"

void play_game(chess_game* game)
{
    std::cout << "Starting Game!" << std::endl;
    std:: cout << "(Input 'q' to Quit)" << std::endl;

    while (1) 
    {
        std::cout << std::endl;
        game->print_board();
        std::cout << std::endl;

        if (game->get_player())
        {
            std::cout << "White Player's Turn:" << std::endl;
            std::string input;
            getline(std::cin, input);
            if (input == "q") 
            {
                std::cout << "Quitting Game" << std::endl;
                break;
            }
            else
            {
                
            }

            // *** Cordinate handling needs to be expanded apon. Raw input string needs to be parsed and allocated to the array either here or in a seperate function: ***
            // std::array<int, 4> coordinates;
            // coordinates = get_input();
            // for (int i = 0; i<4;i++){
            //    std::cout << coordinates[i];
            // }
            std::cout << std::endl;
            game->pass_turn();
        }
        else
        {
            std::cout << "Black Player's Turn:" << std::endl;
            std::cout << "Game Over!" << std::endl;
            break;
        }
    }
}

// *** This needs to be expanded apon to handle, parse and sanitize output, needs to check for 'q' here: ***
std::string get_input() 
{
    std::string input;
    getline(std::cin, input);
    return input;
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