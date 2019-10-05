#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000
void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
void copy(int *newcyl, int *oldcyl, int n)
{
	for (int i = 0; i < n; i++)
	{
		newcyl[i] = oldcyl[i];
	}
}
void calculateDistanceVector(int *distVect, int *cylinder, int initialHeadPointer, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (cylinder[i] != -1)
		{
			distVect[i] = abs(initialHeadPointer - cylinder[i]);
		}
		else
		{
			distVect[i] = MAX;
		}
	}
}
int findMinimum(int *a, int n)
{
	int min = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i] < a[min])
		{
			min = i;
		}
	}
	return min;
}
void sort(int *a, int n, int order)
{
	int swp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		swp = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[swp] > a[j] && order == 1)
			{
				swp = j;
			}
			else if (a[swp] < a[j] && order == -1)
			{
				swp = j;
			}
		}
		if (swp != i)
		{
			swap(&a[i], &a[swp]);
		}
	}
}
int main()
{
	int numberOfCylinders, overhead = 0, capacity;
	int initialHeadPointer, previousHeadPointer;
	int *cylinder;
	int choice;
	printf("\nEnter the capacity:");
	scanf("%d", &capacity);
	printf("\nEnter the number of cylinders:");
	scanf("%d", &numberOfCylinders);
	printf("\nEnter initial head pointer:");
	scanf("%d", &initialHeadPointer);
	cylinder = (int *)malloc(numberOfCylinders * sizeof(int));
	printf("\nEnter the cylinder numbers:");
	for (int i = 0; i < numberOfCylinders; i++)
	{
		scanf("%d", &cylinder[i]);
	}

	while (1)
	{
		printf("\n1.FCFS\n2.SSTF\n3.SCAN\n4.CSCAN\n5.LOOK\n6.CLOOK\n7.Exit\nEnter choice:");
		scanf("%d", &choice);
		if (choice == 1)
		{
			overhead = abs(initialHeadPointer - cylinder[0]);
			for (int i = 0; i < numberOfCylinders - 1; i++)
			{
				overhead += abs(cylinder[i] - cylinder[i + 1]);
			}
			printf("\nOverhead=%d", overhead);
		}
		else if (choice == 2)
		{
			int *lcylinder, overhead = 0, minIndex;
			int *distanceVector;
			int initialHeadPointerSSTF = initialHeadPointer;

			lcylinder = (int *)malloc(numberOfCylinders * sizeof(int));
			copy(lcylinder, cylinder, numberOfCylinders);

			distanceVector = (int *)malloc(numberOfCylinders * sizeof(int));
			sort(lcylinder, numberOfCylinders, 1);

			for (int i = 0; i < numberOfCylinders; i++)
			{
				calculateDistanceVector(distanceVector, lcylinder, initialHeadPointer, numberOfCylinders);
				minIndex = findMinimum(distanceVector, numberOfCylinders);
				overhead += abs(lcylinder[minIndex] - initialHeadPointerSSTF);
				initialHeadPointerSSTF = lcylinder[minIndex];
				lcylinder[minIndex] = -1;
			}
			printf("\nOverhead=%d", overhead);
			overhead = 0;
		}
		else if (choice == 3)
		{
			int *lcylinder;
			int headDirection, startIndex;
			lcylinder = (int *)malloc(numberOfCylinders * sizeof(int));
			copy(lcylinder, cylinder, numberOfCylinders);
			printf("\nEnter previous head pointer:");
			scanf("%d", &previousHeadPointer);

			headDirection = initialHeadPointer - previousHeadPointer;

			if (headDirection < 0)
			{
				sort(lcylinder, numberOfCylinders, -1);

				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] < initialHeadPointer)
					{
						startIndex = i;
						printf("\nInitial element:%d\n", lcylinder[startIndex]);
						break;
					}
				}
				overhead = abs(initialHeadPointer - lcylinder[startIndex]);
				overhead += lcylinder[numberOfCylinders - 1];
				overhead += abs(0 - lcylinder[startIndex - 1]);
			}
			else if (headDirection > 0)
			{
				sort(lcylinder, numberOfCylinders, 1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] > initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
				overhead = abs(initialHeadPointer - lcylinder[startIndex]);
				overhead += abs(lcylinder[numberOfCylinders - 1] - (capacity - 1));
				overhead += abs(capacity - 1 - lcylinder[startIndex - 1]);
			}
			for (int i = startIndex; i < numberOfCylinders - 1; i++)
			{
				overhead += abs(lcylinder[i] - lcylinder[i + 1]);
			}
			for (int i = startIndex - 1; i > 0; i--)
			{
				overhead += abs(lcylinder[i] - lcylinder[i - 1]);
			}
			printf("\nOverhead=%d", overhead);
		}
		else if (choice == 4)
		{
			int *lcylinder;
			int headDirection, startIndex;
			lcylinder = (int *)malloc(numberOfCylinders * sizeof(int));
			copy(lcylinder, cylinder, numberOfCylinders);
			printf("\nEnter previous head pointer:");
			scanf("%d", &previousHeadPointer);
			headDirection = initialHeadPointer - previousHeadPointer;

			if (headDirection < 0)
			{
				sort(lcylinder, numberOfCylinders, -1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] < initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
				overhead = abs(initialHeadPointer - lcylinder[startIndex]);
				//printf("\n%d-%d", initialHeadPointer, lcylinder[startIndex]);
				overhead += abs(lcylinder[numberOfCylinders - 1] - 0);
				//printf("\n%d-%d", lcylinder[numberOfCylinders - 1], 0);
				overhead += capacity - 1;
				//printf("\n%d-%d", capacity - 1, 0);
				overhead += abs(lcylinder[0] - (capacity - 1));
				//printf("\n%d-%d", lcylinder[0], capacity - 1);
			}
			else if (headDirection > 0)
			{
				sort(lcylinder, numberOfCylinders, 1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] > initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
				overhead = abs(initialHeadPointer - lcylinder[startIndex]);
				//printf("\n%d-%d", initialHeadPointer, lcylinder[startIndex]);
				overhead += abs(capacity - 1 - lcylinder[numberOfCylinders - 1]);
				//printf("\n%d-%d", capacity - 1, lcylinder[numberOfCylinders - 1]);
				overhead += capacity - 1;
				//printf("\n%d-%d", capacity - 1, 0);
				overhead += abs(lcylinder[0] - 0);
				//printf("\n%d-%d", lcylinder[0], 0);
			}
			for (int i = startIndex; i < numberOfCylinders - 1; i++)
			{
				overhead += abs(lcylinder[i] - lcylinder[i + 1]);
				//printf("\n%d-%d", lcylinder[i], lcylinder[i + 1]);
			}
			for (int i = 0; i < startIndex - 1; i++)
			{
				overhead += abs(lcylinder[i] - lcylinder[i + 1]);
				//printf("\n%d-%d", lcylinder[i], lcylinder[i + 1]);
			}
			printf("\nOverhead=%d", overhead);
		}
		else if (choice == 6)
		{
			int *lcylinder;
			int headDirection, startIndex;
			lcylinder = (int *)malloc(numberOfCylinders * sizeof(int));
			copy(lcylinder, cylinder, numberOfCylinders);
			printf("\nEnter the previous head pointer:");
			scanf("%d", &previousHeadPointer);
			headDirection = initialHeadPointer - previousHeadPointer;

			if (headDirection < 0)
			{
				sort(lcylinder, numberOfCylinders, -1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] < initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
			}
			else if (headDirection > 0)
			{
				sort(lcylinder, numberOfCylinders, 1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] > initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
			}
			overhead = abs(initialHeadPointer - lcylinder[startIndex]);
			for (int i = startIndex; i < numberOfCylinders - 1; i++)
			{
				overhead += abs(lcylinder[i] - lcylinder[i + 1]);
			}
			overhead += abs(lcylinder[numberOfCylinders - 1] - lcylinder[0]);
			for (int i = 0; i < startIndex - 1; i++)
			{
				overhead += abs(lcylinder[i] - lcylinder[i + 1]);
			}
			printf("\nOverhead=%d", overhead);
		}
		else if (choice == 5)
		{
			int *lcylinder;
			int headDirection, startIndex;
			lcylinder = (int *)malloc(numberOfCylinders * sizeof(int));
			copy(lcylinder, cylinder, numberOfCylinders);
			printf("\nEnter the previous head pointer:");
			scanf("%d", &previousHeadPointer);
			headDirection = initialHeadPointer - previousHeadPointer;
			if (headDirection < 0)
			{
				sort(lcylinder, numberOfCylinders, -1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] < initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
			}
			else if (headDirection > 0)
			{
				sort(lcylinder, numberOfCylinders, 1);
				for (int i = 0; i < numberOfCylinders; i++)
				{
					if (lcylinder[i] > initialHeadPointer)
					{
						startIndex = i;
						break;
					}
				}
			}
			overhead = abs(initialHeadPointer - lcylinder[startIndex]);
			for (int i = startIndex; i < numberOfCylinders - 1; i++)
			{
				overhead += abs(lcylinder[i] - lcylinder[i + 1]);
			}
			overhead += abs(lcylinder[numberOfCylinders - 1] - lcylinder[startIndex - 1]);
			for (int i = startIndex - 1; i > 0; i--)
			{
				overhead += abs(lcylinder[i] - lcylinder[i - 1]);
			}
			printf("\nOverhead=%d", overhead);
		}
		else if (choice == 7)
		{
			exit(0);
		}
	}

	return 0;
}
