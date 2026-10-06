/*
 This is a simple Stone, Papers Scissors game, which uses
 a 'random' for generating random inputs, maps to store
 conditions and a basic game loop. 

 The bot and user must compete each other in the game. First to win 3 games wins!
 */


#include <iostream>
#include <random>
#include <vector>
#include <map>

int generateMove() {
				static std::random_device rd;
				static std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dist(1, 3);

				return dist(gen);
}

int main() {				
				std::map<std::vector<int>, int> conditions = {	
								// Win conditions for Bot.
								{{1, 2}, -1},
								{{2, 3}, -1},
								{{3, 1}, -1},

								// Win conditions for user.
								{{2, 1}, 1},
								{{3, 2}, 1},
								{{1, 3}, 1}
				};	
				int user_points, bot_points = 0;
				
				while (user_points < 3 && bot_points > -3) {
								int user_input;

								std::cout << "Choose your decision!\n1. Stone\n2. Paper\n3. Scissors\nChoose: ";
								
								std::cin >> user_input;
								if (user_input > 3 || user_input < 1) {
												std::cout << "Please enter a valid move.\n";
												continue;
								}
								int bot_move = generateMove();

								std::cout << "Bot Chose: " << bot_move << "\n";
								if (bot_move == user_input) {
												std::cout << "A Draw!\n";
												continue;
								}
								std::vector<int> moves(2);

								moves[0] = user_input; moves[1] = bot_move;

								int result = conditions[moves];
								if (result > 0) {user_points++; std::cout << "Your point!\n";} 
								else if (result < 0) {bot_points--; std::cout << "Bot's point!\n";}
				}
				if (bot_points == -3) {
								std::cout << "The Bot wins! Better luck Next time!\n";
				} else if (user_points == 3) {
								std::cout << "You Won! Congrats!\n";
				}
}
