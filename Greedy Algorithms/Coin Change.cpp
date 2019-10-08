#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::sort;

int main() {
	// This vector stores the denominations that will be asked after
	// asking the initial balance.
	vector<unsigned long long> denominations;

	// We first ask for available balance.
	cout << "Initial balance: ";
	
	// Store this balance to balance variable.
	// Note the unsigned long long type. 
	// We are only working with positive and whole numbers (usually).
	unsigned long long balance;
	cin >> balance;

	// We keep pushing denominations to the vector
	// until 0 is inputted.

	cout << "Enter the denominations (end the input with 0)." << endl;
	cout << "Ex: 5 20 1 28 9 0 will be interpreted as "
		<< "1, 5, 9, 20, and 28 as the denominations." << endl;

	cout << "> ";

	unsigned long long denom;
	while (true) {
		// We keep asking for denomination until the user inputted 0.
		cin >> denom;
		if (denom > 0) {
			denominations.push_back(denom);
		} else {
			break; // input is finished because 0 is inputted.
		}
	}
	
	// There is no guarantee that the input is sorted. So we sort it first.
	sort(denominations.begin(), denominations.end());

	// There is no guarantee that a solution will exist.
	// So we will save our coin exchange values and only
	// print the exchanges if the balance hit exactly 0.
	
	vector<unsigned long long> amount;

	for (int i = denominations.size()-1; i >= 0; --i) {
		// What is the maximum number of coins
		// that can be exchanged for current balance?
		// That amount is pushed into the amount vector.
		amount.push_back(balance/denominations.at(i));

		// The remainder then is set to the balance variable
		// because the exchange has been done.
		balance %= denominations.at(i);
	}

	if (balance == 0) {
		cout << "Exchange is done without any remainder. Results: "
			<< endl;
	} else {
		cout << "Exchange is done with a remainder of " << balance
			<< ". Results: " << endl;
	}

	for (int i = 0; i < amount.size(); ++i) {
		cout << amount.at(i) << " of " 
			<< denominations.at(denominations.size()-1-i) 
			<< " coins." << endl;
	}

	// Note that greedy method does not always produce 
	// an optimal solution (meaning it won't always use 
	// the least number of coins. If we want to ensure such 
	// thing, we could use DP to solve the problem.
	
	return 0;
}
