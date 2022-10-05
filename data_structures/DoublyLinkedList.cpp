//#include<iostream>
//#include<algorithm>
//#include<utility>
//
//struct link
//{
//	int data;
//	link* next;
//	link* prev;
//};
//class DLL
//{
//	link* head;
//	link* tail;
//public:
//	DLL()
//	{
//		head = NULL;
//		tail = NULL;
//	}
//	void insertNode(int val)
//	{
//		link* newnode = new link;
//		
//		if (head == NULL)
//		{
//			newnode->data = val;
//			newnode->next = NULL;
//			newnode->prev = NULL;
//			head = newnode;
//			tail = head;
//		}
//		else
//		{
//			newnode->data = val;
//			newnode->prev = tail;
//			newnode->next = NULL;
//			tail->next = newnode;
//			tail = tail->next;
//		}
//
//	}
//	int getNode(int  n)
//	{
//		link* newnode = new link;
//		newnode = head;
//		int i = 0;
//		while (newnode != NULL)
//		{ 
//			if (i == n)
//			{
//				return newnode->data;
//
//			}
//			newnode->prev = newnode;
//			newnode = newnode->next;
//		}
//
//	}
//	void sort()
//	{
//		link* newnode = new link;
//		link* index = new link;
//	     if (head == NULL)
//			{
//
//				return;
//				
//			}
//
//		for ( newnode = head; newnode->next != NULL;newnode= newnode->next)
//		{
//			for (index = newnode->next; index != NULL; index= index->next)
//			{
//				if (newnode->data > index->data)
//				{
//					int  temp = newnode->data ;
//					newnode->data = index->data;
//					index->data = temp;
//					 
//				}
//			}
//		}
//	}
//
//	void display()
//	{
//		link* newnode = new link;
//		newnode = head;
//		while (newnode != NULL)
//		{
//
//			std::cout << newnode->data << " ";
//			newnode = newnode->next;
//		}
//
//
//	}
//	void reverse()
//	{
//
//		link* temp = NULL;
//		link* curr = this->head;
//
//		while (curr != NULL)
//		{
//			temp = curr->prev;
//			curr->prev = curr->next;
//			curr->next = temp;
//			curr = curr->prev;
//		}
//
//		if (temp != NULL)
//		{
//			this->head = temp->prev;
//		}
//
//	}
//
//
//};
//
//
//
//int main()
//{
//
//
//	DLL s;
//	s.insertNode(2);
//	s.insertNode(4);
//	s.insertNode(3);
//	s.insertNode(0);
//	s.insertNode(1);
//	s.display();
//	std::cout << std::endl;
//	s.reverse();
//	s.display();
//	
//
//	system("pause");
//	return 0;
//}