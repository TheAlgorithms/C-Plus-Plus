#include <iostream>
#include <string>

using namespace std;
/*
Write a C++ program that will ask the user to input his/her names as a single entity,
the number of registered courses in a semester, course code,
course unit and grade of each course and then compute
the following parameters: UA (Unit Attempted), UP (Unit Passed), WS (Weighted Score)
as the product of UA and Grade Point, where grade point is as indicated below,
and GPA (Grade Point Average) as the quotient of WS and UA.
The results should be displayed as depicted in Fig. Q1.
Note that xx refers to actual values computed with the program.
[Grade Point: A – 5 point, B – 4 points, C – 3 points, D – 2 points, E – 1 point and E – 0 point]
*/

struct Course
{
	char course_code[50];
	int course_unit;
	char course_grad;
};
struct Student
{
	char name[50];
	int number_of_registered_courses;
	Course student_course;
	float units_attempted;
	float units_passed;
	float weighted_score;
	float CGPA;
};
int main()
{
	Student student1;
	cout << "Enter Student's name: " << endl;
	cin.getline(student1.name, 50);
	cout << "Enter number of registered courses: " << endl;
	cin >> student1.number_of_registered_courses;
	cin.ignore();


	int i = 0;
	student1.weighted_score = 0;
	student1.units_attempted = 0;
	student1.units_passed = 0;
	while(i<student1.number_of_registered_courses)
	{
		cout << "Enter the course code: " << endl;
		cin.getline(student1.student_course.course_code, 50);
		cout << "Enter the course unit for " << student1.student_course.course_code <<endl;
		cin >> student1.student_course.course_unit;
		cout << "Enter the grade for this course: " << endl;
		cin >> student1.student_course.course_grad;
		cin.ignore();

		if(student1.student_course.course_grad == 'A' || student1.student_course.course_grad == 'a')
		{
			student1.units_attempted +=(1*student1.student_course.course_unit);
			student1.units_passed += (1*student1.student_course.course_unit);
			student1.weighted_score += (5*student1.student_course.course_unit);
		}
		else if(student1.student_course.course_grad == 'B' || student1.student_course.course_grad == 'b')
		{
			student1.units_attempted +=(1*student1.student_course.course_unit);
			student1.units_passed +=(1*student1.student_course.course_unit);
			student1.weighted_score += (4*student1.student_course.course_unit);
		}
		else if(student1.student_course.course_grad == 'C' || student1.student_course.course_grad == 'c')
		{
			student1.units_attempted +=(1*student1.student_course.course_unit);
			student1.units_passed +=(1*student1.student_course.course_unit);
			student1.weighted_score += (3*student1.student_course.course_unit);
		}
		else if(student1.student_course.course_grad == 'D'|| student1.student_course.course_grad == 'd')
		{
			student1.units_attempted +=(1*student1.student_course.course_unit);
			student1.units_passed +=(1*student1.student_course.course_unit);
			student1.weighted_score += (2*student1.student_course.course_unit);
		}
		else if(student1.student_course.course_grad == 'E'|| student1.student_course.course_grad == 'e')
		{
			student1.units_attempted +=(1*student1.student_course.course_unit);
			student1.units_passed +=(1*student1.student_course.course_unit);
			student1.weighted_score += (1*student1.student_course.course_unit);
		}
		else if(student1.student_course.course_grad == 'F' || student1.student_course.course_grad == 'f')
		{
			student1.units_attempted +=(1*student1.student_course.course_unit);
		}


		i++;
	}
	student1.CGPA = student1.weighted_score/student1.units_attempted;

	cout << endl;
	cout << student1.name << endl;
	cout << "Units Attempted: " << student1.units_attempted << endl;
	cout << "Units Passed: " << student1.units_passed << endl;
	cout << "Weighted Score: " << student1.weighted_score <<endl;
	cout << "CGPA: " << student1.CGPA << endl;

	cout << endl;

	system("Pause");
}
