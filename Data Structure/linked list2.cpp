#include <iostream> 
using namespace std;
class Node
{
public:
	Node(int=0) ;
	void setData(int);
	int getData() const;
	void setNextPtr( Node *);
	Node* getNextPtr () const;
private:
    Node* nextPtr;
    int data;
};

class List
{
public:
	List ();
	~List ();
	void insertAtFront();
	void insertAtBack();
	int insertAtPos();
	void removeFromFront();
	void removeFromBack();
	int removeFromPos();
	void sort();
    int	 search();
    int update();
    void reverse();
	void display() const;
	bool isEmpty ()const;
	int size () const;
private:
	Node *firstPtr; //pointer to Back
	Node *lastPtr; //pointer to Front

};
Node::Node(int data)
{
	setData(data);
	nextPtr = 0;
	
}
void Node::setData( int data)
{
	this->data = data;
}
int Node::getData() const
{
	return data;
}
Node* Node:: getNextPtr() const
{
	return nextPtr;
}
void Node::setNextPtr( Node * nodePtr)
{
	this->nextPtr = nodePtr;
}
///////////////////////////////////////////////////////////////////////////////////////

List::List(): firstPtr(0), lastPtr(0)
{
	
}
List::~List()
{
	
	if ( isEmpty())
	{
		Node *currentPtr = firstPtr;
		Node *tempPtr;
		//free memory
		while ( currentPtr != 0)
		{
			tempPtr = currentPtr;
			cout<<tempPtr->getData()   <<'\n';
			currentPtr = currentPtr->getNextPtr();
			delete tempPtr;
		}
		//
		
	}

}

void List::insertAtBack ()
{
	Node* newNode = new Node(10);
	int data;
	
	cout<<"Enter Data\n";
	cin>>data;
	newNode->setData(data);
	if ( isEmpty())
	{
		firstPtr= lastPtr= newNode;
		

	}
	else
	{
		newNode->setNextPtr(firstPtr);
		firstPtr = newNode;
	}
}
void List::insertAtFront()
{
	Node *newNode = new Node();
	int data;

	cout<<"Enter Data\n";
	cin>>data;
	newNode->setData(data);
	if ( isEmpty())
	{
		firstPtr= lastPtr= newNode;
		

	}
	else
	{
		lastPtr-> setNextPtr(newNode);
		lastPtr = newNode;
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Insert at pos
int List::insertAtPos()
{
	
	Node *currentPtr;
	Node *tempPtr;
	Node *newNode = new Node();
	int pos;
	int data;
	int i = 0;
	cout<<"Enter Data\n";
	cin>> data;
	newNode->setData(data);
	cout<<"What is the node position you want to insert at?\n";
	cin>> pos;
	if ( pos <0 ) 
	{
		cout<< "Out of index\n";
		return -1;
		
	}
	if ( pos == 0)
	{
		if ( firstPtr == 0)
		{
			firstPtr =  lastPtr = newNode;
			newNode->setNextPtr(0);
		}
			
		else
		newNode->setNextPtr (firstPtr);
		firstPtr = newNode;
	}
	else
	{
		currentPtr = firstPtr;
		while ( i < pos && currentPtr !=0 )
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->getNextPtr();
				i++;
		}
		if (i < pos && currentPtr == 0)
		{
			cout<<"out of index\n";
			return -1;
		}
		tempPtr->setNextPtr(newNode);
		newNode->setNextPtr(currentPtr);
		
		if (i == pos && currentPtr == 0)
		{
			lastPtr = newNode;
		}
		
	
	}
	return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::removeFromBack()
{
	Node *currentPtr =firstPtr;;
	if (isEmpty())
	{
		cout<<"The list is empty \n"<<endl;
	}
	else
	{
		if (firstPtr == lastPtr )
			firstPtr = lastPtr = 0;
		else
			firstPtr = firstPtr->getNextPtr();
		}

		delete currentPtr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::removeFromFront()
{


	Node *currentPtr =firstPtr;
	Node *temp;
	if (isEmpty())
	{
		cout<<"The list is empty \n"<<endl;
	}
	else
	{
		if (firstPtr == lastPtr )
			firstPtr = lastPtr = 0;
		else
		{
			//trversing the link list
			while ( currentPtr != lastPtr)
			{
				temp = currentPtr;
				currentPtr = currentPtr->getNextPtr();
			}

			lastPtr = temp;
			temp->setNextPtr(0);
		}
	}
		delete currentPtr;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int List::removeFromPos()
{
	if ( isEmpty() )
	{
			cout<<"The list is empty \n";
			return -1;
	}
	int pos;
	int value =0;
	cout<<"Enter the postion of the node you want to remove\n";
	cin>>pos;
	Node* currentPtr = firstPtr;
	Node *tempPtr = firstPtr; 
	
	
	if ( pos < 0  )
	{
		cout<<"Invalid node position\n";
		return -1;
	}
	else
	
		
	{
		if ( pos ==0 )
			if (firstPtr == lastPtr)
				firstPtr = lastPtr =0;
			else
			{
				firstPtr = firstPtr->getNextPtr();
				
			}
		else
			
		{
			
			while ( currentPtr !=0   &&   value < pos)
			{
					value++;
					tempPtr = currentPtr;
					currentPtr = currentPtr->getNextPtr();
			}
			
			if ( currentPtr == 0 && value <= pos )
			{
				cout<<"Invalid node position\n";
				return -1;
			}
			tempPtr->setNextPtr(currentPtr->getNextPtr());
			if (currentPtr->getNextPtr() == 0 )
				lastPtr = tempPtr;


			
		}
		delete currentPtr;
	}
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////
int List::search()
{
	int value, pos = 0;
    bool flag = false;
	Node*currentPtr = firstPtr;
	Node*prevPtr;
    if (firstPtr == 0 )
    {
        cout<<"List is empty"<<endl;
        return -1;
    }
    cout<<"Enter the value to be searched: \n";
    cin>>value;
	
     while (currentPtr != 0 && value != currentPtr->getData())
	 {
		 prevPtr = currentPtr;
		 currentPtr = currentPtr->getNextPtr();
		 pos++;
	 }
	 if ( currentPtr == 0 && value != prevPtr->getData() )
		 return -1;
	 else
	 	 return pos;
}

void List::sort()
{
	Node* currentPtr = firstPtr;
	Node* tempPtr;
	int value;
	Node* ptr;
	if (firstPtr == 0)
		cout<<"The list is empty \n";
	else if ( firstPtr != lastPtr)
		
		while ( currentPtr->getNextPtr () != 0)
		{
			
			tempPtr = currentPtr->getNextPtr();
			
			while ( tempPtr !=0 )
			{
				
				if ( currentPtr->getData() > tempPtr->getData())
				{
					value = currentPtr->getData();
					currentPtr->setData (tempPtr->getData());
					tempPtr->setData(value);
				}
				tempPtr = tempPtr->getNextPtr();
			}
				
			currentPtr = currentPtr->getNextPtr();
			
				
		}


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::reverse()
{
	Node* currentPtr = firstPtr;
	Node* tempPtr;
	int value;
	Node* ptr;
	if (firstPtr != lastPtr )
	{
		lastPtr = firstPtr;
		tempPtr = currentPtr->getNextPtr();
		currentPtr->setNextPtr(0);
		ptr = currentPtr;
		currentPtr = tempPtr;
		
		while ( currentPtr != 0)
		{	
			tempPtr = currentPtr->getNextPtr();
			currentPtr->setNextPtr(ptr);
			ptr = currentPtr;
			currentPtr = tempPtr;
			
		}

		firstPtr = ptr;
	}
		
}
int List::update()
{
	if (isEmpty())
	{
		cout<<"The list is empty\n";
		return -1;
	}
	int value = -1;
	int pos, nodeValue;
	cout<<"Enter the node position that is to be updated \n";
	cin>>pos;
	cout<<"Enetr the new node value\n";
	cin>>nodeValue;
	Node *currentPtr = firstPtr;
	Node* tempPtr;
	if  ( pos < 0)
	{
		cout<<"Invalid node position"<<endl;
		return -1;
	}
	
	else
		while ( currentPtr !=0 && value < pos) 
		{
			value ++;
			tempPtr = currentPtr;
			currentPtr = currentPtr->getNextPtr();
		}
		if ( currentPtr == 0 && value < pos )
		{
			cout<<"Invalid node position\n";
			return -1;
		}
		else
			tempPtr->setData(nodeValue);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List:: display() const 
{
	Node * currentPtr = firstPtr;
		cout<< "Displaying list \n";
		while ( currentPtr != 0)
		{
		
			cout<<currentPtr->getData()<<"\t"; 
			currentPtr = currentPtr->getNextPtr();

		}
		cout<<"\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool List::isEmpty() const
{ if 
	(firstPtr == 0 )
		return true;
	else
		return false;

}
int List::size() const
{
	int len = 0;
	Node * currentPtr = firstPtr;
	while ( currentPtr != 0)
	{
		
		len++; 
		currentPtr = currentPtr->getNextPtr();

	}
	return len;
		
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Driver program to test above
void menuinstruction ()
{
	cout <<" ENTER 1 for INSERT at Front\n "<<endl;
	cout <<" ENTER 2 for INSERT at BACK\n "<<endl;
	cout <<" ENTER 3 for INSERT at POS\n "<<endl;
	cout <<" ENTER 4 for REMOVE from FRONT \n "<<endl;
	cout <<" ENTER 5 for REMOVE from BACK \n "<<endl;
	cout <<" ENTER 6 for REMOVE from POS \n "<<endl;
	cout <<" ENTER 7 for SEARCH a NODE \n"<<endl;
	cout <<" ENTER 8 for SORT \n"<<endl;
	cout <<" ENTER 9 for REVERSE \n"<<endl;
	cout <<" ENTER 10 for UPDATE \n"<<endl;
	cout <<" Enter 11 for SIZE\n"<<endl;
	cout <<" Enter 12 for DISPLAY\n"<<endl;
	cout <<" Enter 13 for Exit\n"<<endl;


};
int main()
{
	int choise;
	List mylist;
	do 
	{
		menuinstruction();
		cout << " ENTER the CHOICE\n";
		cin>>choise;
		switch ( choise )
		{
		case 1:
			mylist.insertAtFront();
			break;
		case 2:
			mylist.insertAtBack();
			break;
		case 3:
			mylist.insertAtPos();
			break;
		case 4:
			mylist.removeFromFront();
			break;
		case 5:
			mylist.removeFromBack();
			break;
		case 6:
			mylist.removeFromPos();
			break;
		case 7:
			cout<<"The position is "<<	mylist.search() << "\n";
			break;
		case 8: 
			mylist.sort();
			break;
		case 9:
			mylist.reverse();
			break;
		case 10:
			mylist.update();
			break;
		case 11:
			cout<<"The size is "<< mylist.size() <<"\n"; 
			break;
		case 12:
			mylist.display();
			break;
		}
	
	}
	while ( choise !=13);
	return 0;
}

