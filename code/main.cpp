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

    string filePath = "C:/Users/joedi/Agile_mini_project.db";
    DBInterface db(filePath);
   
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
                    cout << "Type \"3\" to edit a students' attendance" << endl;
                    cout << "Type \"4\" to get summaries" << endl;
                    cin >> input1;

                    //get summaries
                    if(input1 == "4"){
                        //what summaries would the user want
                        string input4;
                        cout << "Type \"1\" to generate day summary." << endl;
                        cout << "Type \"2\" to generate student summary." << endl;
                        cout << "Type \"3\" to generate course summary." << endl;
                        cin >> input4;
                        cout << endl;

                        if(input4 == "1"){

                            //generate day summary for selected course

                        }else if(input4 == "2"){

                            string studentName;
                            cout << "Please enter student name" << endl;
                            cin >> studentName;
                            cout << endl;

                            bool isStudentName = false;
                            //loop through course to see if the student name that was inputed
                            // if student found, isStudentName = true;

                            if(isStudentName){
                                //call generate student summary
                            }else{
                                cout << "Invalid Student Name!" << endl;
                                cout << endl;
                            }

                        }else if(input4 == "3"){

                            //generate course summary for selected course

                        }else{
                            cout << "Invalid input!" << endl;
                            cout << endl;
                        }

                        
                    }

                    //edit a students' attendance 
                    if(input1 == "3"){
                        
                        string studentName;
                        cout << "Type the name of the student you would like to edit the attendance of." << endl;
                        cin >> studentName;
                        cout << endl;

                        bool isStudentName = false;
                        // find if inputed student name is valid

                        if(isStudentName){

                            string attendanceInput;
                            cout << "What would you like to change about " << studentName << "'s attendance?" << endl;
                            cout << "Guide: Type \"P\" for present, type \"A\" for absent, type \"T\" for tardy,"  << 
                            " type \"E\" for excused, type \"U\" for unexcused."<< endl;
                            cin >> attendanceInput;

                            if(attendanceInput == "P"){
                                //set present
                            }else if(attendanceInput == "A"){
                                //set absent
                            }else if (attendanceInput == "T"){
                                //set tardy
                            }else if (attendanceInput == "E"){
                                //set excused
                            }else if (attendanceInput == "U"){
                                //set unexcused
                            } else {
                                cout << "Invalid input!" << endl;
                                cout << endl;
                            }


                        } else {

                            cout << "Invalid student name!" << endl;
                            cout << endl;
                        }

                    }
                    
                    //sort students
                    if (input1 == "2"){
                        //sort stuff

                        cout << "Type \"1\" to start attendance." << endl;
                        cout << "Type \"2\" to return to start." << endl;
                        cin >> input1;
                    }

                    //start attendance
                    if (input1 == "1"){
                        cout << "Guide: Type \"P\" for present, type \"A\" for absent, type \"T\" for tardy, type \"E\" for excused." << endl;
                        string attendanceInput;
                        bool attendanceLoop;

                        /*  possible attendance implementation below  */
                        ////c1 will be the selected course
                        // for(int i = 0; i < c1.students.size(); ++i){
                        //     attendanceLoop = true;
                        //     while (attendanceLoop){
                        //         cout << c1.students.at(i).studentFirstName << " " << c1.students.at(i).studentLastName << "     ";
                        //         cin >> attendanceInput;
                        //         if (attendanceInput == "P"){
                        //             //input student attendance present
                        //             attendanceLoop = false;
                        //         }else if(attendanceInput == "A"){
                        //             //input student attendance absent
                        //             attendanceLoop = false;
                        //         }else if(attendanceInput == "T"){
                        //             //input student attendance tardy
                        //             attendanceLoop = false;
                        //         }else if(attendanceInput == "E"){
                        //              //input student attendance excused
                        //              attendanceLoop = false;
                        //         }else{
                        //             cout << "Please enter a valid value" << endl;
                        //         }
                        //         cout << endl;
                        //     }

                        // }

                    }
                    loop = false;
                }
                else{
                    cout << "Please enter a valid course name" << endl;
                    loop = true;
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
            Course c1(courseName, filePath, db);

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
}
