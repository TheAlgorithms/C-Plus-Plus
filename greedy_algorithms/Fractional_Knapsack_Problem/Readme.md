# Fractional Knapsack Problem Solver

This C++ program solves the Fractional Knapsack Problem using a greedy algorithm. It finds the most valuable combination of items to include in a knapsack without exceeding its weight capacity.

## Problem Description

In the Fractional Knapsack Problem, you are given a set of items, each with a weight and a value. You also have a knapsack with a maximum weight capacity. The goal is to determine the most valuable combination of items to include in the knapsack without exceeding its weight capacity.

## How It Works

The program uses a greedy approach by selecting items based on their value-to-weight ratio. It sorts the items by this ratio in decreasing order and adds items to the knapsack until its weight capacity is reached.

## Features

- Efficient greedy algorithm implementation
- Customizable item weights and values
- Calculates and displays the maximum value that can be placed in the knapsack

## Usage

1. Clone this repository to your local machine.


2. Compile the C++ code.


3. Run the program with your custom item weights and values and the knapsack's capacity.


4. The program will calculate and display the maximum value achievable in the knapsack.

## Example

Suppose you have the following items and a knapsack with a capacity of 50 units:

- Item 1: Weight 10 units, Value $60
- Item 2: Weight 20 units, Value $100
- Item 3: Weight 30 units, Value $120

Running the program with this data will result in the maximum value that can be placed in the knapsack.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Inspired by the Fractional Knapsack Problem in algorithms and optimization.


