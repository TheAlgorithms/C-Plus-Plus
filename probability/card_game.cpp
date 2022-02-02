/**
 * @file
 * @brief This is a simple card game
 * @details
 * This game is based off of https://www.codechef.com/problems/CARDS777 in which
 * the player chooses a set number of red cards, blue cards and tokens. The user
 * selects what color token they want and if that matches the color of the
 * randomly generated card, the player recieves a point and if it does not
 * match, the player gets no points. The games can happen until the player quits
 * or until they have played all of their turns which is the number of red cards
 * plus the number of blue cards. The token that is selected and the card that
 * is generated is tossed.
 * @author [Dhrubo Mondal](https://github.com/dhrubo28)
 */
#include <stdlib.h>

#include <iostream>
#include <string>

/**
 * @class card_game_class
 * @brief essentials for the game
 */

class card_game_class {
 private:
    int number_of_red_tokens;
    int number_of_blue_tokens;
    int number_of_turns;
    int random_number_generator;
    int point;
    int total_points;
    int total_number_of_turns;
    int turn_tracker;
    std::string token_choice;

 public:
    void card_game_function(int number_of_red_card, int number_of_blue_card,
                            int number_of_tokens);
};
/**
 * @brief where the game operates
 * @param param1 number of red card as selected by the player
 * @param param2 number of blue card as selected by the player
 * @param param3 number of tokens as selected by the player
 * @returns void
 */
void card_game_class::card_game_function(int number_of_red_card,
                                         int number_of_blue_card,
                                         int number_of_tokens) {
    point = 0;
    total_points = 0;
    number_of_red_tokens =
        number_of_tokens;  // the number of red tokens is the number of tokens
                           // selected by the player
    number_of_blue_tokens =
        number_of_red_card + number_of_blue_card -
        number_of_tokens;  // the number of blue tokens is the number of red
                           // cards plus the number of blue cards subtract the
                           // number of tokens
    random_number_generator =
        rand() %
        2;  // generates random numbers, 0 and 1 representing red card
            // and blue card respectively used for randomly generating the cards
    total_number_of_turns =
        number_of_red_card +
        number_of_blue_card;  // the number of turns the player can play is the
                              // number of red cards plus the number of blue
                              // cards
    std::cout << "You have " << number_of_red_card << " red cards, "
              << number_of_blue_card << " blue cards, " << number_of_red_tokens
              << " red tokens, and " << number_of_blue_tokens << " blue tokens."
              << std::endl;
    // as long as there are cards and tokens left, the players can play
    turn_tracker = 0;  // keeps tracks of which turn the player is playing
    while (turn_tracker < total_number_of_turns) {
        std::cout << "Choose the color of your token or quit. The option for "
                     "the token is "
                     "red or blue. You can quit with any letter or word other "
                     "than red or blue."
                  << std::endl;
        std::cin >> token_choice;
        if (token_choice == "red") {
            if (number_of_red_tokens > 0) {
                if (number_of_red_card > 0 && number_of_blue_card > 0) {
                    if (random_number_generator == 0) {
                        point = 1;
                        total_points = total_points + point;
                        number_of_red_card--;
                        std::cout << "You got a red card." << std::endl;
                        std::cout << "Your total points is " << total_points
                                  << std::endl;
                    } else {
                        number_of_blue_card--;
                        std::cout << "You got a blue card." << std::endl;
                        std::cout << "Your total points is " << total_points
                                  << std::endl;
                    }
                } else if (number_of_red_card > 0 && number_of_blue_card == 0) {
                    point = 1;
                    total_points = total_points + point;
                    number_of_red_card--;
                    std::cout << "You got a red card." << std::endl;
                    std::cout << "Your total points is " << total_points
                              << std::endl;
                } else if (number_of_red_card == 0 && number_of_blue_card > 0) {
                    std::cout << "You have no more red cards and have only "
                                 "blue cards."
                              << std::endl;
                    std::cout << "Your total points is " << total_points
                              << std::endl;
                }
                number_of_red_tokens--;
            } else {
                std::cout << "You have no more red tokens." << std::endl;
            }
        } else if (token_choice == "blue") {
            if (number_of_blue_tokens > 0) {
                if (number_of_blue_card > 0 && number_of_red_card > 0) {
                    if (random_number_generator == 1) {
                        point = 1;
                        total_points = total_points + point;
                        number_of_blue_card--;
                        std::cout << "You got a blue card." << std::endl;
                        std::cout << "Your total points is " << total_points
                                  << std::endl;
                    } else {
                        number_of_red_card--;
                        std::cout << "You got a red card." << std::endl;
                        std::cout << "Your total points is " << total_points
                                  << std::endl;
                    }
                } else if (number_of_blue_card > 0 && number_of_red_card == 0) {
                    point = 1;
                    total_points = total_points + point;
                    number_of_blue_card--;
                    std::cout << "You got a red card." << std::endl;
                    std::cout << "Your total points is " << total_points
                              << std::endl;
                } else if (number_of_blue_card == 0 && number_of_red_card > 0) {
                    std::cout << "You have no more blue cards and have only "
                                 "red cards."
                              << std::endl;
                    std::cout << "Your total points is " << total_points
                              << std::endl;
                }
                number_of_blue_tokens--;
            } else {
                std::cout << "You have no more blue tokens." << std::endl;
            }
        } else {
            break;
        }
        turn_tracker++;
    }

    std::cout << "Thank you for playing." << std::endl;
}
/**
 * @brief main function where the user selects the number of red cards, blue
 * cards and tokens
 * @returns 0 on exit
 */
int main() {
    int number_of_red_card = 0;
    int number_of_blue_card = 0;
    int number_of_tokens = 0;
    card_game_class card_game;

    std::cout
        << "Choose the number of red cards. The number must be one or greater."
        << std::endl;
    std::cin >> number_of_red_card;
    std::cout
        << "Choose the number of blue cards. The number must be one or greater."
        << std::endl;
    std::cin >> number_of_blue_card;
    std::cout
        << "Choose the number of tokens. The number must be one or greater."
        << std::endl;
    std::cin >> number_of_tokens;
    card_game.card_game_function(number_of_red_card, number_of_blue_card,
                                 number_of_tokens);
    return 0;
}