#include <iostream>
using namespace std;

struct Item
{
	int weight;
	int profit;
};

/*Function to calculate the weight per unit for the item passed to it as a parameter (Item x) and return it.
	Eg. if an item has profit= 10 and wright = 5, then the function will return 2(profit/weight)*/
float profitPerUnit(Item x)
{
	return (float)x.profit / (float)x.weight;
}

/*Partition function- Used by Quick sort function to find a pivot at which the array/ list can be divided into 
  sub- arrays/lists on  which the quick sort algo can again be applied. Study Quick Sort applicaion for comlete details and understanding.*/
int partition(Item arr[], int low, int high)
{
	Item pivot = arr[high]; // pivot
	int i = (low - 1);		// Index of smaller element

	for (int j = low; j < high; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (profitPerUnit(arr[j]) <= profitPerUnit(pivot))
		{
			i++; // increment index of smaller element
			Item temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	Item temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;
	return (i + 1);
}

//Quick sort function
void quickSort(Item arr[], int low, int high)
{
	if (low < high)
	{

		int p = partition(arr, low, high);

		quickSort(arr, low, p - 1);
		quickSort(arr, p + 1, high);
	}
}

int main()
{
	cout << "\nEnter the capacity of the knapsack : ";
	float capacity;
	cin >> capacity;
	cout << "\n Enter the number of Items : ";
	int n;
	cin >> n;
	Item itemArray[n]; 	//We are making an array of items. Each item will have a weight 
				//and a profit as it is a structure defined above. The size of array is the number
				//of items entered by the user.
	
	//Input weight and profit for each item.			
	for (int i = 0; i < n; i++)
	{
		cout << "\nEnter the weight and profit of item " << i + 1 << " : ";
		cin >> itemArray[i].weight;
		cin >> itemArray[i].profit;
	}
	
	/*Applying quick sort on the itemArray to arrange items in decreasing order of their profit per unit value.
	 Item with the highest profit per unit will come first in the array and will be picked first to be
	 added in the knapsack then following the successive order with the next max profit per unit item picked to be
	 added in the knapsack*/
	
	quickSort(itemArray, 0, n - 1);

	// show(itemArray, n);

	float maxProfit = 0;
	int i = n;
	while (capacity > 0 && --i >= 0)
	{
		if (capacity >= itemArray[i].weight) 	// runs when the weight of the item we are about to add in
							// knapsack is < capacity of knapsack left
		{
			maxProfit += itemArray[i].profit;
			capacity -= itemArray[i].weight;
			cout << "\n\t" << itemArray[i].weight << "\t" << itemArray[i].profit;
		}
		else	//runs when weight of the item we are about to add is > capacity of knapsack left.
		{
			maxProfit += profitPerUnit(itemArray[i]) * capacity; //calculating the profit of the part of the item
										//that can be added in the knapsack and adding 
										//  it in maxProfit
			cout << "\n\t" << capacity << "\t" << profitPerUnit(itemArray[i]) * capacity;
			capacity = 0;
			break;
		}
	}

	cout << "\nMax Profit : " << maxProfit;

	return 0;
}
