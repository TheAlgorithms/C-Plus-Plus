#include <iostream>
#include <vector>

std::vector<int> primes(int max) {
    max++;
    std::vector<int> vec;
    std::vector<bool> numbers(max, false);
    for (int i = 2; i < max; i++) {   //To check till the given input
        if (!numbers[i]) {
            for (int j = i; j < max; j = j+i)
                numbers[j] = true;
            vec.push_back(i); //To push the value to vector
        }
    }
    return vec; //returning the vector
}
//Driver function
int main() {
    std::cout << "Calculate primes up to:\n>> ";
    int n;
    std::cin >> n; //To take the input
    std::vector<int> ans = primes(n); //Function call
    for (int i = 0; i < ans.size(); i++)
        std::cout << ans[i] << ' ';
    std::cout << std::endl;
}
