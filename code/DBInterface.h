#include <iostream>
#include "DBAbstraction.h"
#include <vector>

using namespace std;

class DBInterface : DBAbstraction {
public:
    DBInterface(string pathToFile);


    void EnterStudent(string fName, string lName);
    //void EnterSection(string description, int courseId);
    void EnterCourse(string courseName);
    void EnterAttendance(int sectionID, int studentID, string date, string attendanceStatus);


    void CreateCourseTable();
    void CreateStudentTable();
    //void CreateSectionTable();
    void CreateAttendanceTable();

private:
};