/*Quicksort is an efficient sorting algorithm , using an algorithm design paradigm based on multi-branched recursion, that is divide and conquer.*/

/*Below is an Implementation of Quick Sort where the First element is picked as Pivot*/
/*The below Code uses randomized system generated inputs(that is using srand(time(0)) and rand) and Sorts them in O(nlogn) time.*/

/*The key process in quickSort is partition(). Target of partitions is, given an array and an element x of array as pivot, put x at its correct position in sorted array and put all smaller elements (smaller than x) before x, and put all greater elements (greater than x) after x. All this should be done in linear time.*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
class QuickSort
{
    int n;
    int *arr;

public:
    QuickSort() {}
    QuickSort(int n)
    {
        this->n = n;
        arr = new int[n];
    }
    void input()
    {
        int n1, n2;
        cout << "Enter the range of elements : ";
        cin >> n1 >> n2;
        srand(time(0));
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = n1 + rand() % (n2 - n1 + 1);
        }
        return;
    }
    void Display()
    {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
    void swap(int *x, int *y) //Utility swap function.
    {
        *x = ((*x) * (*y)) / (*y = *x);
    }

    int partition(int *arr, int l, int h)
    {
        int pivot = arr[l];
        int i = l, j = h;
        do
        {
            do
            {
                i++;
            } while (arr[i] <= pivot);
            do
            {
                j--;
            } while (arr[j] > pivot);
            if (i < j)
            {
                swap(arr + i, arr + j);
            }
        } while (i < j);
        swap(arr + l, arr + j);
        return j;
    }
    void Sort(int l, int h)
    {
        if (l < h)
        {
            int p = partition(arr, l, h);
            Sort(l, p);
            Sort(p + 1, h);
        }
        return;
    }
    ~QuickSort() //to Deallocate memory upon Termination of Program.
    {
        delete[] arr;
    }
};

int main()
{
    int n;
    cout << "Enter the input array Size : ";
    cin >> n;
    QuickSort obj(n);
    obj.input(); //Randomized system generated Inputs assigned to the Dynamic Array.
    cout << "\nInput Array : ";
    obj.Display();
    obj.Sort(0, n);
    cout << "\nOutput Array : ";
    obj.Display();

    return 0;
    /*Output Example : 
        Enter the input array Size : 15
        Enter the range of elements : 30 50

    Input Array : 32 43 35 37 38 34 32 34 38 47 39 36 38 30 50

    Output Array : 30 32 32 34 34 35 36 37 38 38 38 39 43 47 50
    */
}
