#include <iostream>
#include "course.h"
using namespace std;

int main()
{
    //create course name and send file path for the sections that will be generated automatically
    string input;
    cout << "Type \"1\" to select an existing course." << endl;
    cout << "Type \"2\" to create a new course." << endl;
    cin >> input;

    if(input == "1"){
        //select existing course by getting course data from database
        //select whether the user wants to sort or start attendence
    }
    else if(input == "2"){
        //create new course
        string courseName;
        string filePath;
        cout << "Enter name of course." << endl;
        cin >> courseName;
        cout << "Enter file path." << endl;
        cin >> filePath;
        //either create a Course or input into database
        Course c1(courseName, filePath);
        cout << c1.getCourseName();
        cout << " created." << endl;
    }
    else{

    }
    
    // const string filePath = "";
    // string courseName;
    // cout << "Please Enter Course Name: ";
    // cin >> courseName;
    // Course C1(courseName, filePath);

    // cout << C1.getCourseName() << endl;

    // cout<<"Agile Project"<<endl;
    return 0;
}
