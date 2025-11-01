#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Course
{
string name;
string grade;
double credit;
double gradePoint;
double creditPoint;
};

double convertGradeToPoint(string grade)
{
if (grade == "A+" || grade == "a+") return 10.0;
if (grade == "A"  || grade == "a")  return 9.5;
if (grade == "B"  || grade == "b")  return 8.0;
if (grade == "C"  || grade == "c")  return 6.0;
if (grade == "D"  || grade == "d")  return 4.0;
if (grade == "E"  || grade == "e")  return 2.0;
if (grade == "F"  || grade == "f")  return 0.0;
return -1.0;
}

int main() {
int semesters;
cout << "Enter number of Semester";
cin >> semesters;
cin.ignore();

double overallCredits = 0, overallPoints = 0;
for(int k=1;k <= semesters; k++)
{
int courses;
cout << "Enter the number of courses" << endl;
cin >> courses;
cin.ignore();

vector<Course> subjects(courses);
double semesterCredits = 0, semesterPoints = 0;

for(int i=0 ; i < subjects.size() ; i++)
{
cout << "enter name of course " << i+1 << endl;
getline(cin,subjects[i].name);

cout << "enter grade of the course " << i+1 << endl;
cin >> subjects[i].grade;

cout << "enter credits of the course " << i+1 << endl;
cin >> subjects[i].credit;
cin.ignore();

subjects[i].gradePoint = convertGradeToPoint(subjects[i].grade);
if(subjects[i].gradePoint == -1)
{
cout << "Invalid grade" << endl;
return 1;
}
subjects[i].creditPoint = subjects[i].credit * subjects[i].gradePoint;
semesterCredits += subjects[i].credit;
semesterPoints += subjects[i].creditPoint;
}
double semesterCgpa = semesterPoints/semesterCredits;
overallCredits += semesterCredits;
overallPoints += semesterPoints;
 
cout << "Course-wise details for Semester " << k << endl;
cout << left << setw(20) << "Course" 
<< setw(8) << "Grade" 
<< setw(8) << "Credit" 
<< setw(12) << "Grade Point" 
<< setw(18) << "Credit x Grade Point" << endl;
for(const auto &c : subjects)
{
cout << left << setw(20) << c.name
<< setw(8) << c.grade
<< setw(8) << c.credit
<< setw(12) << c.gradePoint
<< setw(18) << c.creditPoint << endl;
}
cout << fixed << setprecision(2);
cout << "Semester Cgpa is " << semesterCgpa << endl;
}    
double finalCgpa = overallPoints / overallCredits;
cout << "FINAL CGPA IS......" << endl;
cout << fixed << setprecision(2);
cout << "Total Credits: " << overallCredits << endl;
cout << "Total Grade Points: " << overallPoints << endl;
cout << "final CGPA: " << finalCgpa << endl;
cout << "Approx Percentage: " << finalCgpa * 9.5 << "%" << endl;
return 0;
}