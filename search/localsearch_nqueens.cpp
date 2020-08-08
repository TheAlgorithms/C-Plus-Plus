/*
 * @file
 * @brief [Heuristic local Search](https://en.wikipedia.org/wiki/Local_search_(optimization)) algorithm.
 * @details
 * The LS algorithm is the basis of many methods used for optimization problems.
 * Its system is based on the search for neighborhoods that obtain a better solution.
 * This exercise solves the [n queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle) problem.
 * The rule of neighborhood applied in this file is first improvement.
 * @author [dhernandezl](https://github.com/dhernandezl)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

/** \namespace search
 *  \brief Heuristic local search algorithm.
 */
namespace search {
	/* \namespace localsearch
     * \brief Functions for [Heuristic local Search](https://en.wikipedia.org/wiki/Local_search_(optimization)) algorithm.
     */
	namespace localsearch {
		/**
		 * function: initial_solution
		 * Initialize a new solution, generating
		 * random numbers with the maximum height of the board.
		 * @param [in] nqueens is the number of queens to be placed on the chessboard.
		 * The number of queens is also the dimension of the chessboard
		 * @returns a vector that will be the starting solution.
		 */
		std::vector<int> initial_solution(int nqueens) {
			std::vector<int> solution;
			solution.resize(nqueens);
			for (auto &element : solution) {
				element = rand() % nqueens + 1;
			}
			return solution;
		}

		/**
		 * function: cost
		 * Calculate the number of pairs of queens that are attacked within the board,
		 * the optimal cost is h = 1. Read the 8 queens problem.
		 * @param [in] solution_vector is a vector with the
		 * column number where the queens are located on the board.
		 * @returns the cost of the solution vector.
		 */
		int cost(const std::vector<int> &solution_vector) {
			int h = 0;
			//sum column
			for (size_t i = 0; i < solution_vector.size(); i++) {
				for (size_t j = i + 1; j < solution_vector.size(); j++) {
					if (solution_vector[i] == solution_vector[j]) {
						h++;
						break;
					}
				}
			}
			//sum diagonal
			for (size_t i = 0; i < solution_vector.size(); i++) {
				for (size_t j = i + 1; j < solution_vector.size(); j++) {
					if ((solution_vector[i] - (i + 1))
							== (solution_vector[j] - (j + 1))) {
						h++;
						break;
					}
				}
			}
			//sum inverse diagonal
			for (size_t i = 0; i < solution_vector.size(); i++) {
				for (size_t j = i + 1; j < solution_vector.size(); j++) {
					if ((solution_vector[i] + (i + 1))
							== (solution_vector[j] + (j + 1))) {
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
			int64_t i = rand() % solution_vector.size() + 1;
			int64_t mov = (rand() % solution_vector.size() + 1);
			solution_vector[i - 1] = mov;
			return solution_vector;
		}

		/**
		 * function: print_solution
		 * Prints the solution obtained on the chessboard in console.
		 * @param [in] solution_vector is a vector with the
		 * column number where the queens are located on the board.
		 */
		void print_solution(const std::vector<int> &solution_vector) {
			for (int i = 0; i < solution_vector.size(); i++) {
				for (int j = 0; j < solution_vector.size(); j++) {
					if (j == solution_vector[i] - 1) {
						std::cout << " Q ";
					} else {
						std::cout << " _ ";
					}
				}
				std::cout << "\n";
			}

			std::cout << "\nSolucion: ";
			for (int x : solution_vector) {
				std::cout << x << " ";
			}
			std::cout << "\nCost:" << cost(solution_vector) << std::endl;
		}

		/**
		 * function: searchrepeat
		 * Search for repeated neighbors (vector) to
		 * ensure the generation of new neighbors.
		 * @param [in] prob_neighbor is candidate to be a neighbor of the current solution.
		 * @param [in] neighborhood is vector of generated neighbors contained in memory.
		 * @return true if value exists, if not false.
		 */
		inline bool searchrepeat(const std::vector<int> &prob_neighbor, const std::vector<std::vector<int>> &neighborhood) {
			return find(neighborhood.begin(), neighborhood.end(), prob_neighbor) != neighborhood.end();
		}
	} //namespace localsearch
} //namespace search

/**
 * Main function
 * Heuristic Local Search - Rule first best neighbor
 * - s = generate initial solution
 * - while s not optimal local do{
 * -	s* belongs neighbor(s) with cost(s*) < cost(s)
 * -	keep the neighboring solution if it has lower cost than the current one.
 * -	s = s*
 * -}
 *
 */
int main() {
	constexpr int nqueens = 8;  //The number of queens on the table is the same as the dimension of the chessboard.
					  	  	  	//nqueens = 4; nqueens = 8; nqueens = 16
	constexpr int number_neighbor = 10; //number of neighbors to generate
	std::vector<int> current_solution = search::localsearch::initial_solution(nqueens);
	std::vector<int> neighbor_solution;
	std::vector<std::vector<int>> neighborhood;  //neighborhood of the current solution
	int i = 0;
	do {
		while (search::localsearch::searchrepeat(neighbor_solution = search::localsearch::neighbour(current_solution), neighborhood)) {}
		neighborhood.push_back(neighbor_solution);
		if (search::localsearch::cost(neighbor_solution) < search::localsearch::cost(current_solution)){
			current_solution = neighbor_solution;
			i = 0;
			neighborhood.clear();
		}
		else { i++; }
	} while (i < number_neighbor);
	search::localsearch::print_solution(current_solution);
	return 0;
}
