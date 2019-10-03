// C++ Program for bogo sort
#include <iostream>
#include <algorithm>

using namespace std;

void bogoSort(string arr)
{

    bool ordered = false;

    while(ordered == false) {
    	random_shuffle(arr.begin(), arr.end());

    	ordered = true;
    	for(int i = 1; i < arr.size(); i++)
    		if(arr[i] < arr[i-1])
    			ordered = false;
    }

    cout << "Sorted character array is " << arr;
}

int main()
{
    string arr;
    cin >> arr;

    bogoSort(arr);

    return 0;
}
