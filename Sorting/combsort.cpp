//Kind of better version of Bubble sort.
//While Bubble sort is comparering adjacent value, Combsort is using gap larger than 1
//Best case: O(n)
//Worst case: O(n ^ 2)

#include <iostream>

using namespace std;

int a[100005];
int n;

int FindNextGap(int x)
{
    x = (x * 10) / 13;

    return max(1, x);
}

void CombSort(int a[], int l, int r)
{
    //Init gap
    int gap = n;

    //Initialize swapped as true to make sure that loop runs
    bool swapped = true;

    //Keep running until gap = 1 or none elements were swapped
    while (gap != 1 || swapped)
    {
        //Find next gap
        gap = FindNextGap(gap);

        swapped = false;

        // Compare all elements with current gap
        for (int i = l; i <= r - gap; ++i)
        {
            if (a[i] > a[i + gap])
            {
                swap(a[i], a[i + gap]);
                swapped = true;
            }
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    CombSort(a, 1, n);

    for (int i = 1; i <= n; ++i)
        cout << a[i] << ' ';
    return 0;
}
