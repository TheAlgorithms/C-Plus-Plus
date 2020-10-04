#include<iostream>
#include<cstring>
struct Employee{
char name[50];
int id;
int dob;
float bsal;
};
int main(){
int n=0,p=0;
float hig=0.0;
std::cout<<"enter no. of employees\n";
std::cin>>n;
struct Employee emp[n];
std::cout<<"enter details of employees\n";
for(int i=0;i<n;i++){
std::cout<<"for employee no. "<<(i+1)<<"\n";
std::cout<<"enter name\n";
std::cin>>emp[i].name;
std::cout<<"enter ID\n";
std::cin>>emp[i].id;
std::cout<<"date of birth,in [ddmmyy] format\n";
std::cin>>emp[i].dob;
std::cout<<"enter salary\n";
std::cin>>emp[i].bsal;
}
for(int i=0;i<n;i++){
if(emp[0].bsal<emp[i].bsal){
hig=emp[i].bsal;
p=i;
}
}
std::cout<<"employee with the highest salary is "<<emp[p].name<<"\n";
std::cout<<"salary: Rs. "<<emp[p].bsal<<"\n";
std::cout<<"DOB= "<<emp[p].dob<<"\n";
return 0;
}
