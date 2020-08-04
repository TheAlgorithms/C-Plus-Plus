/*
 * @file
 * @brief [Heuristic local Search](https://en.wikipedia.org/wiki/Local_search_(optimization)) algorithm.
 * @details
 * The LS algorithm is the basis of many methods used for optimization problems.
 * Its system is based on the search for neighborhoods that obtain a better solution.
 * This exercise solves the n queens problem [https://en.wikipedia.org/wiki/Eight_queens_puzzle].
 * The rule of neighborhood applied in this file is first.improvement.
 * @author [dhernandezl](https://github.com/dhernandezl)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#define NREINAS 8 //The number of queens on the table is the same as the dimension of the chessboard.
				  // NREINAS 4; NREINAS 8; NREINAS 16
/**
 * function: initial_solution
 * Initialize a new solution, generating
 * random numbers with the maximum height of the board.
 * @returns a vector that will be the starting solution.
 */
std::vector<int> initial_solution() {
	std::vector<int> solution;
	srand(time(nullptr)); //reset srand
	for (size_t i = 0; i < NREINAS; i++)
	{
		solution.push_back(rand() % NREINAS + 1);
	}
	return solution;
}

/**
 * function: cost
 * Calculate the cost of the solution vector,
 * the optimal cost is h = 1. Read the 8 queens problem.
 * @param [in] solution_vector is a vector with the
 * column number where the queens are located on the board.
 * @returns the cost of the solution vector.
 */
int cost(std::vector<int> solution_vector) {
	int h = 0;
	std::vector<int> aux_sol;
	//sum column
	for (size_t i = 0; i < NREINAS; i++)
	{
		for (size_t j = i + 1; j < NREINAS; j++)
		{
			if (solution_vector[i] == solution_vector[j])
			{
				h++;
				break;
			}
		}
	}
	//sum diagonal
	for (size_t i = 0; i < NREINAS; i++)
	{
		aux_sol.push_back(solution_vector[i] - (i + 1));
	}
	for (size_t i = 0; i < NREINAS; i++)
	{
		for (size_t j = i + 1; j < NREINAS; j++)
		{
			if (aux_sol[i] == aux_sol[j])
			{
				h++;
				break;
			}
		}
	}
	aux_sol.clear();
	//sum inverse diagonal
	for (size_t i = 0; i < NREINAS; i++)
	{
		aux_sol.push_back(solution_vector[i] + (i + 1));
	}
	for (size_t i = 0; i < NREINAS; i++)
	{
		for (size_t j = i + 1; j < NREINAS; j++)
		{
			if (aux_sol[i] == aux_sol[j])
			{
				h++;
				break;
			}
		}
	}
	return h;
}

/**
 * function: neighbour
 * Generate a neighbor based on the current solution of
 * the problem. Read about neighborhoods in local search.
 * @param [in] solution_vector is a vector with the
 * column number where the queens are located on the board.
 * @returns a new vector similar to the one passed by parameter.
 */
std::vector<int> neighbour(std::vector<int> solution_vector) {
	srand(time(nullptr)); //reset srand
	int i = rand() % NREINAS + 1;
	srand(time(nullptr)); //reset srand
	int mov = (rand() % NREINAS + 1) - i;
	mov = (mov < 0) ? mov *= -1 : mov;
	mov = (mov == 0) ? mov = 1 : mov;
	solution_vector[i - 1] = mov;
	return solution_vector;
}

/**
 * function: print_solution
 * Prints the solution obtained on the chessboard in console.
 * @param [in] solution_vector is a vector with the
 * column number where the queens are located on the board.
 */
void print_solution(std::vector<int> solution_vector) {
	char chessboard[NREINAS][NREINAS] = {};
	for (int i = 0; i < NREINAS; i++)
	{
		chessboard[i][solution_vector[i] - 1] = 'Q';
	}
	for (int i = 0; i < NREINAS; i++)
	{
		for (int j = 0; j < NREINAS; j++)
		{
			if (chessboard[i][j] != 'Q')
			{
				std::cout << " _ ";
			}
			else { std::cout << " " << chessboard[i][j] << " ";}
		}
		std::cout << "\n";
	}
	std::cout << "\nSolucion: ";
	for (int x : solution_vector)
	{
		std::cout << x;
	}
	std::cout << "\nh:" << cost(solution_vector) << std::endl;
	std::cout << "\n";
}

/**
 * function: searchrepeat
 * Search for repeated neighbors (vector) to
 * ensure the generation of new neighbors.
 * @param [in] prob_neighbor is candidate to be a neighbor of the current solution.
 * @param [in] neighborhood is vector of generated neighbors contained in memory.
 */
inline bool searchrepeat(std::vector<int> prob_neighbor, const std::vector<std::vector<int>>& neighborhood) {
	return find(neighborhood.begin(), neighborhood.end(), prob_neighbor) != neighborhood.end();
}

/**
 * Main function
 * Heuristic Local Search - Rule first best neighbor
 * - s = generate initial solution
 * - while s not optimal local do{
 * -	s* = N(s) with f(s) < f(s*)
 * -	solution best of the neighbor
 * -	s = s*
 * -}
 *
 */
int main() {
	std::vector<int> init_solution = initial_solution();
	std::vector<int> neighbor_solution;
	std::vector<std::vector<int>> neighborhood;  //neighborhood of the current solution
	int number_neighbor = 10; //number of neighbors to generate
	int i = 0;
	do {
		while (searchrepeat(neighbor_solution = neighbour(init_solution), neighborhood)) {}
		neighborhood.push_back(neighbor_solution);
		if (cost(init_solution) > cost(neighbor_solution)){
			init_solution = neighbor_solution;
			i = 0;
			neighborhood.clear();
		}
		else { i++; }
	} while (i < number_neighbor);
	print_solution(init_solution);
	return 0;
}
