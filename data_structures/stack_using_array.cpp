#include <iostream>
using namespace std;

class stack
{
    private:
        int top;
        int *arr;
        int n;

    public:
        stack(int x)
        {
            n=x;
            top=-1;
            arr=new int[n];
            for (int i=0;i<n;i++)
                arr[i]=0;
        }

        bool isempty()
        {
            if (top==-1)
                return true;
            else
                return false;
        }

        bool isfull()
        {
            if (top==(n-1))
                return true;
            else
                return false;
        }

        void push(int val)
        {
            if (isfull())
                cout<<"Stack Overflow"<<endl;
            else
            {
                top++;
                arr[top]=val;
                cout<<"Item pushed"<<endl;
            }
        }

        int pop()
        {
            if (isempty())
                cout<<"Stack underflow"<<endl;
            else
            {
                int t=arr[top];
                arr[top]=0;
                top--;
                return t;
            }
            return -1;
        }

        int count()
        {
            return (top+1);
        }

        int peek(int pos)
        {
            if (isempty())
                cout<<"Stack Underflow"<<endl;
            else if(pos>top)
                cout<<"Invalid position input"<<endl;
            else
                return arr[pos];
            return -1;
        }

        void change(int pos,int val)
        {
            if (pos>top)
                cout<<"Invalid position input"<<endl;
            else
            {
                arr[pos]=val;
                cout<<"Value changed at location "<<pos<<endl;
            }
        }

        void display()
        {
            if (isempty())
                cout<<"There are no elements in the stack"<<endl;
            else
            {
                cout<<"All the elements in the stack are as follows- "<<endl;
                for (int i=top;i>=0;i--)
                {
                    cout<<arr[i]<<endl;
                }
            }
        }
};

int main()
{
    cout<<"Please enter the size of the stack"<<endl;
    int n=0;
    cin>>n;
    stack s(n);
    int option=0,pos=0,val=0;
    do
    {
        cout<<endl;
        cout<<"Please choose from the following options-"<<endl;
        cout<<"1. To perform the push opeation"<<endl;
        cout<<"2. to perform the pop operation"<<endl;
        cout<<"3. To check if the stack is empty"<<endl;
        cout<<"4. To check if the stack is full"<<endl;
        cout<<"5. To peek a value at a specific position"<<endl;
        cout<<"6. To count the total number of elements in the stack"<<endl;
        cout<<"7. To change an element at a specific position"<<endl;
        cout<<"8. To display all the elements in the stack"<<endl;
        cout<<"9. To clear the screen"<<endl;
        cout<<"10. To exit"<<endl;
        cout<<endl;

        cin>>option;
        switch(option)
        {
            case (1):
            {
                cout<<"Please enter the element that is to be pushed"<<endl;
                cin>>val;
                s.push(val);
                break;
            }
            case (2):
            {
                int x=s.pop();
                if (x!=-1)
                    cout<<"The popped item is "<<x<<endl;
                break;
            }
            case (3):
            {
                if(s.isempty())
                    cout<<"The stack is empty"<<endl;
                else
                    cout<<"The stack is not empty"<<endl;
                break;
            }
            case (4):
            {
                if(s.isfull())
                    cout<<"The stack is full"<<endl;
                else
                    cout<<"The stack is not full"<<endl;
                break;
            }
            case (5):
            {
                cout<<"Enter the stack position to be peeked"<<endl;
                cin>>pos;
                if (s.peek(pos)!=-1)
                    cout<<"The element at position "<<pos<<" is "<<s.peek(pos)<<endl;
                break;
            }
            case (6):
            {
                cout<<"The total number of elements in the stack are- "<<s.count()<<endl;
                break;
            }
            case (7):
            {
                cout<<"Please enter the position of the item to be changed"<<endl;
                cin>>pos;
                cout<<"Please enter the new value"<<endl;
                cin>>val;
                s.change(pos,val);
                break;
            }
            case (8):
            {
                s.display();
                break;
            }
            case (9):
            {
                system("cls");
                break;
            }
            default:
            {
                if (option!=10)
                    cout<<"Please enter a valid option number"<<endl;
            }
        }
    }while (option!=10);
    cout<<"Program Terminated"<<endl;
    return 0;
}
