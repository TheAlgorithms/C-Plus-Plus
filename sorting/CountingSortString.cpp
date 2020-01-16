// C++ Program for counting sort
#include <iostream>

using namespace std;

void countSort(string arr)
{

    string output;

    int count[256], i;
    for (int i = 0; i < 256; i++)
        count[i] = 0;

    for (i = 0; arr[i]; ++i)
        ++count[arr[i]];

    for (i = 1; i <= 256; ++i)
        count[i] += count[i - 1];

    for (i = 0; arr[i]; ++i)
    {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    for (i = 0; arr[i]; ++i)
        arr[i] = output[i];

    cout << "Sorted character array is " << arr;
}

int main()
{
    string arr;
    cin >> arr;

    countSort(arr);

    return 0;
}
