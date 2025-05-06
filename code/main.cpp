#include <iostream>
#include "course.h"
using namespace std;

int main()
{
    //create course name and send file path for the sections that will be generated automatically
    const string filePath = "";
    string courseName;
    cout << "Please Enter Course Name: ";
    cin >> courseName;
    Course C1(courseName, filePath);

    cout << C1.getCourseName() << endl;

    cout<<"Agile Project"<<endl;
    return 0;
}
