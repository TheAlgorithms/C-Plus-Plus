#include<iostream>
using namespace std;
struct node
{
    node *next;
    int event,start,end;
};
node *getnode()
{
    node *p=new node;											//d1
    p->next=NULL;											//d2
    return p;												//d3
}
node *head=NULL;											//d4
void find_loc(node **locp,node **loc,int end_time)
{
    node *save=head;											//d5
    node *ptr=head->next;										//d6
    while(ptr!=NULL && ptr->end<end_time)								//d7*n
    {
        save=ptr;											//d8*n
        ptr=ptr->next;											//d9*n
    }
    *loc=ptr;												//d10
    *locp=save;												//d11
}
void insert(int event_no,int start_time,int end_time)
{
    node *p=getnode();											//d12
	p->event=event_no;										//d13
	p->start=start_time;										//d14
    p->end=end_time;											//d15
    if(head==NULL || head->end>end_time)								//d16
    {
        p->next=head;											//d17
        head=p;												//d18
        
    }
    else
    {
        node *loc=NULL;											//d19
        node *locp=NULL;										//d20
        find_loc(&locp,&loc,end_time);									//d21
        locp->next=p;											//d22
        p->next=loc;											//d23
    }   
}
void display()
{
	node *ptr=head;											//d24
	while(ptr != NULL)										//d25*n
	{
		cout << ptr->event <<"\t"<<ptr->start<<"\t"<<ptr->end<<endl;				//d26*n
		ptr = ptr->next;									//d27*n
	}
}
int no_of_events()
{
	node *ptr=head;											//d28
	int count=0;											//d29
	while(ptr != NULL)										//d30*n
	{
		count++;										//d31*n
		ptr=ptr->next;										//d32*n
	}
	return count;											//d33
}	
void ActivitySelector()
{
	node *save=head;										//d34
	node *ptr=head->next;										//d35
	int count=no_of_events();
	//cout<<"count "<< count;
	cout<<"Order of events possible is"<< save->event<<" ";						//d36
	for( int i=1; i<count; i++)									//d37*n
	{
			if((ptr)->start >= save->end)							//d38*n
			{
				cout<<"->"<<ptr->event<<" ";						//d39*n
				save=ptr;								//d40*n
			}
			ptr=ptr->next;									//d41*n
	}
}
int main()
{
	char enter='y';											//c1
	int i=1;											//c2
	cout<<"Do you want to enter a event[y/n]?";							//c3
	cin >> enter;											//c4
	while(enter == 'y')										//c5*n
	{
		cout << "Enter the starting time and ending time of event"<<endl;			//c6*n
		int start_time,end_time;								//c7*n
		cin >> start_time>>end_time;		
		if(start_time >24 || end_time >24 || end_time < start_time)				//c8*n/2
			cout<<"Time cannot be greater than 24 and start time cannot be more than the end time";													//c9*n/2
		else											//c10*n/2
		{
			insert(i,start_time,end_time);							//c11*n/2
			i++;										//c12*n/2	
		}
		cout << "Do you want to insert more events? [y/n]";					//c13*n
		cin >> enter;										//c14*n
	}
	cout<<" List of events is"<<endl;								//c15
	display();											//c16
	ActivitySelector();										//c17
	return 0;
}
		
		
