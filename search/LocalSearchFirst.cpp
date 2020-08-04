/*
 * LocalSearchFirst.cpp
 *
 *  Created on: 28 jul. 2020
 *      Author: DHL-SIS-ING
 */

#include "LocalSearchFirst.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <time.h>
#define NREINAS 16
#define t_neighbor 15
using namespace std;

vector<vector<int>> neighbour_sys;

void print_vector(vector<int> s) {
	for (int x : s) { printf("%d ", x); }
	printf("\n");
}

vector<int> initial_solution() {
	vector<int> solution;
	srand(time(NULL));
	for (size_t i = 0; i < NREINAS; i++)
	{
		solution.push_back(rand() % NREINAS + 1);
	}
	return solution;
}

int cost(vector<int> queens_sol) {
	int h = 0;
	vector<int> aux_sol;
	//sum column
	for (size_t i = 0; i < NREINAS; i++)
	{
		for (size_t j = i + 1; j < NREINAS; j++)
		{
			if (queens_sol[i] == queens_sol[j])
			{
				h++;
				break;
			}
		}
	}
	//sum diagonal
	for (size_t i = 0; i < NREINAS; i++)
	{
		aux_sol.push_back(queens_sol[i] - (i + 1));
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
		aux_sol.push_back(queens_sol[i] + (i + 1));
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

vector<int> neighbour(vector<int> init_sol) {
	srand(time(NULL));
	int i = rand() % NREINAS + 1;
	srand(time(NULL));
	int mov = (rand() % NREINAS + 1) - i;
	mov = (mov < 0) ? mov *= -1 : mov;
	mov = (mov == 0) ? mov = 1 : mov;
	init_sol[i - 1] = mov;
	return init_sol;
}

void print_solution(vector<int> s) {
	char table[NREINAS][NREINAS] = {};
	for (size_t i = 0; i < NREINAS; i++)
	{
		table[i][s[i] - 1] = 'Q';
	}
	for (size_t i = 0; i < NREINAS; i++)
	{
		for (size_t j = 0; j < NREINAS; j++)
		{
			if (table[i][j] != 'Q')
			{
				printf(" _ ");
			}
			else { printf(" %c ", table[i][j]); }
		}
		printf("\n");
	}
	printf("\nSolucion: ");
	for (int x : s)
	{
		printf("%d ", x);
	}
	printf("\nh: %d ", cost(s));
	printf("\n");
}

inline bool searchrepet(vector<int> q, const vector<vector<int>>& s) {
	return find(s.begin(), s.end(), q) != s.end();
}

int main() {
	vector<int> n_s;
	vector<int> s = initial_solution();
	printf("\nSolucion inicial: ");
	print_vector(s);
	printf("h: %d", cost(s));
	printf("\n");
	int i = 0;
	do {
		while (searchrepet(n_s = neighbour(s), neighbour_sys)) {}
		neighbour_sys.push_back(n_s);
		//printf("% d -", i);
		if (cost(s) > cost(n_s)){
			s = n_s;
			i = 0;
			print_vector(s);
			printf("h: %d", cost(s));
			printf("\n");
			neighbour_sys.clear();
		}
		else { i++; }
	} while (i < t_neighbor);
	printf("\n");
	print_solution(s);
	//system("pause");
	return 0;
}
