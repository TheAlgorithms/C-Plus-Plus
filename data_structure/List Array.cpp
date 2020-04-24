#include <iostream>
using namespace std;

struct list
{
	int data[50];
	int top = 0;
	bool isSorted = false;

	int BinarySearch(int *array, int first, int last, int x)
	{
		if (last < first)
		{
			return -1;
		}
		int mid = (first + last) / 2;
		if (array[mid] == x)
			return mid;
		else if (x < array[mid])
			return (BinarySearch(array, first, mid - 1, x));
		else if (x > array[mid])
			return (BinarySearch(array, mid + 1, last, x));
	}

	int LinarSearch(int *array, int x)
	{
		for (int i = 0; i < top; i++)
		{
			if (array[i] == x)
			{
				return i;
			}
		}

		return -1;
	}

	int Search(int x)
	{
		int pos = -1;

		if (isSorted)
		{
			pos = BinarySearch(data, 0, top - 1, x);
		}

		else
		{
			pos = LinarSearch(data, x);
		}

		if (pos != -1)
		{
			cout << "\nElement found at position : " << pos;
		}
		else
		{
			cout << "\nElement not found";
		}
		return pos;
	}

	void Sort()
	{
		int i, j, pos;
		for (i = 0; i < top; i++)
		{
			int min = data[i];
			for (j = i + 1; j < top; j++)
			{
				if (data[j] < min)
				{
					pos = j;
					min = data[pos];
				}
			}

			int temp = data[i];
			data[i] = data[pos];
			data[pos] = temp;
		}
		isSorted = true;
	}

	void insert(int x)
	{
		if (!isSorted)
		{

			if (top == 49)
			{
				cout << "\nOverflow";
			}
			else
			{
				data[top] = x;
				top++;
			}
		}

		else
		{
			int pos = 0;

			for (int i = 0; i < top - 1; i++)
			{
				if (data[i] <= x && x <= data[i + 1])
				{
					pos = i + 1;
					break;
				}
			}
			if (pos == 0)
			{
				pos = top - 1;
			}

			for (int i = top; i > pos; i--)
			{
				data[i] = data[i - 1];
			}
			top++;
			data[pos] = x;
		}
	}

	void Remove(int x)
	{
		int pos = Search(x);
		cout << "\n"
			 << data[pos] << " deleted";
		for (int i = pos; i < top; i++)
		{
			data[i] = data[i + 1];
		}
		top--;
	}

	void Show()
	{
		for (int i = 0; i < top; i++)
		{
			cout << data[i] << "\t";
		}
	}
};

int main()
{
	list L;
	int choice;
	int x;
	do
	{
		cout << "\n1.Insert";
		cout << "\n2.Delete";
		cout << "\n3.Search";
		cout << "\n4.Sort";
		cout << "\n5.Print";
		cout << "\n\nEnter Your Choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\nEnter the element to be inserted : ";
			cin >> x;
			L.insert(x);
			break;
		case 2:
			cout << "\nEnter the element to be removed : ";
			cin >> x;
			L.Remove(x);
			break;
		case 3:
			cout << "\nEnter the element to be searched : ";
			cin >> x;
			L.Search(x);
			break;
		case 4:
			L.Sort();
			break;
		case 5:
			L.Show();
			break;
		}
	} while (choice != 0);
	return 0;
}
