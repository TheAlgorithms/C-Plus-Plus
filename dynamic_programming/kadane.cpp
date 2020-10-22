#include <iostream>
#include <climits>
#include <vector>
int maxSubArraySum(std::vector <int> a) 
{
    int max_so_far = INT_MIN, max_ending_here = 0;
    int size=a.size();
    for (int i = 0; i < size; i++) {
        max_ending_here = max_ending_here + a[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int main() {
    int n, i;
    std::cout << "Enter the number of elements \n";
    std::cin >> n;
    std::vector<int> a(n);  
    for (i = 0; i < n; i++) 
    {
        std::cin >> a[i];
    }
    std::cout << "Maximum contiguous sum is " << maxSubArraySum(a);;
    return 0;
}

