    // file by SOHAM KULKARNI


# include <iostream>
# include <vector>
using namespace std;

void printArr(vector<int>a, int n) {

    for ( int i = 0; i<n; i++)

        cout << a[i] << " ";

    cout << endl;
}

void insertionSort(vector<int>&arr, int n) {

    for ( int i = 1; i<n; i++ ) {
        int temp = arr[i];
        int j;
        for ( j = i-1; j >= 0; j--)
        {
            if (arr[j] > temp)

                arr[j+1] = arr[j];
            
            else    break;
        }
        arr[j+1] = temp;
    }

}

int main () {

    vector<int> arr = {10,1,7,4,8,2,11};
    
    // arr.push_back(10);
    // arr.push_back(1);
    // arr.push_back(7);
    // arr.push_back(4);
    // // arr.push_back(8);
    // arr.push_back(2);
    // arr.push_back(11);

    printArr(arr, arr.size());
    insertionSort(arr,arr.size());
    printArr(arr, arr.size());

    
    return 0;
}
