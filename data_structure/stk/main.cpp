/*
 * This program reads a data file consisting of students' GPAs
 * followed by their names. The program then prints the highest
 * GPA and the names of the students with the highest GPA.
 * It uses stack to store the names of the students
 * Run:
 *     make all
 *     ./main student.txt
 ************************************************************
 * */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <assert.h>

#include "stack.h"
#include "stack.cpp"

using namespace std;

int main(int argc, char * argv[]) {
    double GPA;
    double highestGPA;
    string name;

    assert(argc == 2);
    ifstream infile;
    stack<string> stk;

    infile.open(argv[1]);
    cout << fixed << showpoint;
    cout << setprecision(2);
    infile >> GPA >> name;
    highestGPA = GPA;

    while (infile) {
        if (GPA > highestGPA) {
            stk.clear();
            stk.push(name);
            highestGPA = GPA;
        } else if (GPA == highestGPA) {
            stk.push(name);
        }
        infile >> GPA >> name;
    }
    cout << "Highest GPA: " << highestGPA <<endl;
    cout << "Students the highest GPA are: " << endl;
    while (!stk.isEmptyStack()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    cout << endl;
    return 0;
}
