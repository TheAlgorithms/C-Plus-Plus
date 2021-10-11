/*C++ Program for array implementation of Binary Search Tree
The following LOGIC is used:
If i is the index of an element, then:
(For zero-indexed array)
        Index of left child = 2 * i
        Index of right child = (2 * i) + 1  */

#include <iostream>
#define SIZE 100 //Assuming the size of array to be 100

using namespace std;

//Creating all function prototypes needed
void create_bst(int a[], int index, int value); //For creating and inserting element in the Binary Search Tree
void print_decreasing(int a[], int index);      //For displaying the elements of BST in decreasing order
int search_element(int a[], int key);           //For searching an element in BST
void delete_element(int a[], int key);          //For deleting an element in BST

int main()
{
    int arr[SIZE];
    int data, del, key;
    char ch;

    //Initialising the array elements as (say) -1
    for (int i = 1; i < SIZE; i++)
        arr[i] = -1;

    cout << "Enter the no. of elements in the BST: ";
    int n;
    cin >> n;
    int j = 1;

    //Checking for entry of valid no. of elements
    if (n == 0)
    {
        cout << "Please enter a VALID size." << endl;
        return 0;
    }

    //Storing specified no. of elements in the array
    while (j <= n)
    {
        cout << "Enter a integer value: ";
        cin >> data;
        j++;
        create_bst(arr, 1, data);
    }

    //Printing the BST in decreasing order
    cout << "Decreasing output: " << endl;
    print_decreasing(arr, 1);
    cout << "\n"
         << endl;

    //Asking the user for deletion task and performing it accordingly
    cout << "Want to DELETE an element? Enter 'Y' or 'y' if Yes; or else any other key." << endl;
    cin >> ch;
    while (ch == 'y' || ch == 'Y') //To keep on deleting till the user wants
    {
        cout << "Enter element to be deleted: ";
        cin >> del;
        delete_element(arr, del);
        cout << "Enter 'Y' or 'y' to delete more elements; or else any other key." << endl;
        cin >> ch;
    }
    cout << endl;

    //Asking the user for searching task and performing it accordingly
    cout << "Want to SEARCH an element? Enter 'Y' or 'y' if Yes; or else any other key." << endl;
    cin >> ch;
    while (ch == 'y' || ch == 'Y') //To keep on searching till the user wants
    {
        cout << "Enter element to be searched: ";
        cin >> key;
        int c = search_element(arr, key);
        if (c == 0)
            cout << "Element not found." << endl;
        else
            cout << "Element found!!!" << endl;
        cout << endl;

        cout << "Enter 'Y' or 'y' to search more elements; or else any other key." << endl;
        cin >> ch;
    };

    return 0;
}

//Function definition for creation/insertion of BST
void create_bst(int a[], int index, int value)
{

    if (index >= SIZE)
    {
        cout << "Not enough space in array!!!" << endl;
        exit(0); //Terminate the program if there is not enough space in the array
    }
    else
    {
        if (a[index] == -1)
            a[index] = value;
        else
        {
            if (value < a[index])
                create_bst(a, index * 2, value); //For specifying index of left child
            else
                create_bst(a, (index * 2) + 1, value); //For specifying index of right child
        }
    }
}

//Function definition for searching in BST
int search_element(int a[], int key)
{
    int i;
    int c = 0;
    for (i = 1; i < SIZE; i++)
    {
        if (a[i] == key)
        {
            c++;
            break;
        }
    }
    return c;
}

//Function definition for deletion in BST
void delete_element(int a[], int key)
{
    //Searching performed initially to get the position of the specified element
    int c = search_element(a, key);

    for (int i = 1; i < SIZE; i++)
    {
        if (a[i] == key)
        {
            //-2 is assigned to enable the print_decreasing function skip it during printing
            a[i] = -2;
        }
    }

    //Displaying according message if element for deletion not present in array
    if (c == 0)
        cout << "Element not present in the array!!!" << endl;
    else
    {
        cout << "Output after deletion: " << endl;
        print_decreasing(a, 1);
        cout << endl;
    }
    cout << endl;
}

//Function definition for printing of BST in decreasing order
/*LOGIC: Printing the elements starting from the right most child to the left most child for decreasing order*/
void print_decreasing(int a[], int index)
{

    if (a[index] == -2) //Printing the elements after skipping the one to be deleted (Related to logic in delete_element function)
    {
        print_decreasing(a, (index * 2) + 1);
        print_decreasing(a, index * 2);
    }
    else if (a[index] != -1) //Normal printing when no deletion in involved
    {
        print_decreasing(a, (index * 2) + 1);
        cout << a[index] << " ";
        print_decreasing(a, index * 2);
    }
}
