#include<stdio.h> 
#include<stdlib.h> 

struct Node 
{ 
	int value; 
	int row_position; 
	int column_postion; 
	struct Node *next; 
}; 

// Function to create new node 
void create_new_node(struct Node** start, int non_zero_element, 
					int row_index, int column_index ) 
{ 
	struct Node *temp, *r; 
	temp = *start; 
	if (temp == NULL) 
	{ 
		temp = (struct Node *) malloc (sizeof(struct Node)); 
		temp->value = non_zero_element; 
		temp->row_position = row_index; 
		temp->column_postion = column_index; 
		temp->next = NULL; 
		*start = temp; 

	} 
	else
	{ 
		while (temp->next != NULL) 
			temp = temp->next; 


		r = (struct Node *) malloc (sizeof(struct Node)); 
		r->value = non_zero_element; 
		r->row_position = row_index; 
		r->column_postion = column_index; 
		r->next = NULL; 
		temp->next = r; 

	} 
} 

// This function prints contents of linked list 
// starting from start 
void PrintList(struct Node* start) 
{ 
	struct Node *temp, *r, *s; 
	temp = r = s = start; 

	printf("row_position: "); 
	while(temp != NULL) 
	{ 

		printf("%d ", temp->row_position); 
		temp = temp->next; 
	} 
	printf("\n"); 

	printf("column_postion: "); 
	while(r != NULL) 
	{ 
		printf("%d ", r->column_postion); 
		r = r->next; 
	} 
	printf("\n"); 
	printf("Value: "); 
	while(s != NULL) 
	{ 
		printf("%d ", s->value); 
		s = s->next; 
	} 
	printf("\n"); 
} 


// Driver of the program 
int main() 
{ 
// Assume 4x5 sparse matrix 
	int sparseMatric[4][5] = 
	{ 
		{0 , 0 , 3 , 0 , 4 }, 
		{0 , 0 , 5 , 7 , 0 }, 
		{0 , 0 , 0 , 0 , 0 }, 
		{0 , 2 , 6 , 0 , 0 } 
	}; 

	/* Start with the empty list */
	struct Node* start = NULL; 

	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 5; j++) 

			// Pass only those values which are non - zero 
			if (sparseMatric[i][j] != 0) 
				create_new_node(&start, sparseMatric[i][j], i, j); 

	PrintList(start); 

	return 0; 
} 
