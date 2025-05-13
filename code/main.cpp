#include <iostream>
#include <ctime>
#include "course.h"
using namespace std;

int main()
{
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    int month = 1 + newtime.tm_mon;
    int day = newtime.tm_mday;
    int year = newtime.tm_year;
    cout << year << endl;
   
    cout << "Current date: " << year << "-" << month << "-" << day << endl;

    //create course name and send file path for the sections that will be generated automatically
    string input;
    while(true){
        cout << "Type \"1\" to select an existing course." << endl;
        cout << "Type \"2\" to create a new course." << endl;
        cout << "Type \"Q\" to quit." << endl;
        cin >> input;

        if(input == "1"){
            bool loop = true;
            while (loop){
                //select existing course by getting course data from database
                string inputCourseName;
                cout << "Type name of course you want to open." << endl;
                cin >> inputCourseName;
                bool isCourseName = false; 
                /* for(int i = 0; i < courseList.size; ++i){
                    if(courseList.at(i)->getCourseName == inputCourseName){
                        isCourseName = true;
                    }
                }*/

                if(isCourseName){
                    //select whether the user wants to sort or start attendence
                    string input1;
                    cout << "Type \"1\" to start attendance." << endl;
                    cout << "Type \"2\" to sort students." << endl;
                    cin >> input1;
                    if (input1 == "2"){
                        //sort stuff
                    }

                    //start attendance

                    loop = false;
                } else{
                    cout << "Please enter a valid course name" << endl;
                }
            
            }
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
            cout << endl;
        }
        else if(input == "Q"){
            return 0;
        }else{
            cout << endl;
            cout << "Please input a valid value."<< endl;
        }

        
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
