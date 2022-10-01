#include<iostream>
#include<cstring>
#include<unordered_map>
using namespace std;

class student
{
    public:
    string firstname;
    string lastname;
   string rollno;

student(string f,string l, string no)
{
    firstname = f;
    lastname = l;
    rollno = no;
}

bool operator == (const student &s) const{
    return rollno == s.rollno;
}
};

class HashFn
{
    public:
    size_t operator()(const student &s) 
    const{
        return s.firstname.length() + s.lastname.length();
    }
};

int main()
{    unordered_map<student,int,HashFn> student_map;
    student s1("Prateek","Narang","010");
    student s2("Rahul","Kumar","023");
    student s3("Prateek","Narang","030");
    student s4("Rahul","Kumar","120");

    student_map[s1] = 100;
    student_map[s2] = 120;
    student_map[s3] = 11;
    student_map[s4] = 45;

   cout<<student_map[s3]<<endl;

   for(auto s:student_map){
       cout<<s.first.firstname<<" "<<s.first.rollno<<" Marks "<<s.second<<endl;
   }

    return 0;
}