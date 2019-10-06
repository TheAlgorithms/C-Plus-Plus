#include <iostream.h>
#include <stdlib.h>
//Program to add 2 polynomials represented as SLL
typedef struct abb
{
    int coeff,expn;
    struct abb *link;
}term;

term *poly1,*poly2,*poly3; //header pointer to 3 different polynomials

term *get_node()
{
    return((term *)malloc(sizeof(term)));
} //end of fuction get_node

//Insert in order such that the SLL is in descending order of EXPN
term *insert_inorder(term *p1,int coeff, int expn)
{
    term *temp, *pred,*succ;
    temp = get_node();//Allocate memory for new term
    temp->coeff = coeff;
    temp->expn = expn;
    temp->link = NULL;
    //Scenario #1 EMPTY LIST
    if (p1 == NULL)
    {
        p1 = temp;
    }
    else //Scenario #2
    { //Insert at front of SLL
        if (expn > p1->expn)
        {
            temp->link =p1;
            p1 = temp;
        }
        else //Scenarion #3 & #4
        {
            pred = p1; succ=p1;
            while((succ != NULL) && (succ->expn > expn))
            {
                pred = succ;
                succ = succ->link;
            }//end of while loop
            pred->link = temp;
            temp->link = succ;
        } //end of Scenario #3 & #4
    } //end of Scenario #2
return p1;
} //end of function Insert_in descending order

term *create_poly(term *p1)
{
    int coeff, expn;
    term *temp;
    int choice=1;
    while (choice)
    {
        cout<<"Input the Coeffecient and Exponeniation\n";
        cin>>coeff>>expn;
        p1 = insert_inorder(p1, coeff,expn);
        cout<<"Input 1 to continue 0 to Exit";
        cin>>choice;
    }//end of while loop
    return p1;
}//end of function CreatePOLY

void display(term *p)
{
    if (p == NULL)
    cout<<"Empty LIST\n";
    else
    {
        cout<<"THE POLYNOMIAL is \n";
        while (p!=NULL)
        {
            cout<<"   "<<p->coeff<<" X ^"<<p->expn<< " +";
            p=p->link;
        }//end of while loop
    }//end of else
}//end of function display

term *poly_add(term *p1,term *p2)
{
    while((p1 != NULL) && (p2 != NULL))
    {
        if (p1->expn == p2->expn)
        {
            poly3=insert_inorder(poly3,p1->coeff+p2->coeff,p1->expn);
            p1 = p1->link;
            p2 = p2->link;
        }
        else
        {
            if(p1->expn > p2->expn)
             {
                poly3 = insert_inorder(poly3,p1->coeff,p1->expn);
                p1 = p1->link;
             }
             else
             {
                 poly3 = insert_inorder(poly3,p2->coeff,p2->expn);
                 p2 = p2->link;
             }
    }//end of else
  }//end of while
  if (p1== NULL)
  {
      while (p2!=NULL)
      {
          poly3 = insert_inorder(poly3,p2->coeff,p2->expn);
          p2 = p2 ->link;
      }
  }
  else
  {
      while (p1!=NULL)
      {
          poly3 = insert_inorder(poly3,p1->coeff,p1->expn);
          p1 = p1->link;
      }//end of while
  }//end of else
  return poly3;
}//end of function POLY_ADD

int main()
{
    cout<<"Polynomial Addition\n";
    cout<<"Creating 1st POLYNOMIAL\n";
    poly1=create_poly(poly1);
    cout<<"\nCreating 2nd POLYNOMIAL\n";
    poly2 = create_poly(poly2);
    cout<<"PRINTING 1st POLYNOMIAL\n";
    display(poly1);
    cout<<"\n PRINTING 2nd POLYNOMIAL\n";
    display(poly2);
    poly3=poly_add(poly1,poly2);
    cout<<"\n The resulatant POLYNOMIAL \n";
    display(poly3);
    return 0;
}