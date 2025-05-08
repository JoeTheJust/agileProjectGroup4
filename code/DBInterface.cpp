#include "DBInterface.h"

DBInterface::DBInterface(string pathToFile) : DBAbstraction(pathToFile) {

    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, NULL);
}

void DBInterface::EnterStudent(string fName, string lName) {

    string sql = "INSERT INTO Students (firstName, lastName) VALUES (?, ?);";

    sqlite3_stmt* myStatement;

    int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if(status == SQLITE_OK) {

        sqlite3_bind_text(myStatement, 1, fName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, lName.c_str(), -1, SQLITE_STATIC);

        if(!exectueQueryNoResultsBack(myStatement)) {
            cout << "Error inserting into Students Table" << endl;
        }

    }
}

// void DBInterface::EnterSection(string description, int courseId) {
//     string sql = "INSERT INTO Sections (description, courseId) VALUES (?, ?);";

//     sqlite3_stmt* myStatement;

//     int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

//     if(status == SQLITE_OK) {

//         sqlite3_bind_text(myStatement, 1, description.c_str(), -1, SQLITE_STATIC);
//         sqlite3_bind_int(myStatement, 2, courseId);

//         if(!exectueQueryNoResultsBack(myStatement)) {
//             cout << "Error inserting into Section Table" << endl;
//         }
//     }
// }

void DBInterface::EnterCourse(string courseName, string description) {
    string sql = "INSERT INTO Courses (courseName, description) VALUES (?, ?);";

    sqlite3_stmt* myStatement;

    int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if(status == SQLITE_OK) {
        sqlite3_bind_text(myStatement, 1, courseName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, description.c_str(), -1, SQLITE_STATIC);

        if(!exectueQueryNoResultsBack(myStatement)) {
            cout << "Error inserting into Course Table" << endl;
        }
    }
}

void DBInterface::EnterAttendance(int courseId, int studentId, string date, string attendanceStatus) {
    string sql = "INSERT INTO Attendance (courseId, studentId, date, status) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* myStatement;

    int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if(status == SQLITE_OK) {
        sqlite3_bind_int(myStatement, 1, courseId);
        sqlite3_bind_int(myStatement, 2, studentId);
        sqlite3_bind_text(myStatement, 3, date.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 4, attendanceStatus.c_str(), -1, SQLITE_STATIC);

        if(!exectueQueryNoResultsBack(myStatement)) {
            cout << "Error inserting into Attendance Join Table" << endl;
        }
    }
}

void DBInterface::CreateCourseTable() {
    string sql = "CREATE TABLE IF NOT EXISTS Courses ( id INTEGER PRIMARY KEY NOT NULL, courseName TEXT, description TEXT);";

    if(!exectueQueryNoResultsBack(sql)) {
        cout << "Error in creating Course Table" << endl;
    }
    
}

void DBInterface::CreateStudentTable() {
    string sql = "CREATE TABLE IF NOT EXISTS Students ( id INTEGER PRIMARY KEY NOT NULL, firstName TEXT, lastName TEXT);";

    if(!exectueQueryNoResultsBack(sql)) {
        cout << "Error in creating Student Table" << endl;
    }
}

// void DBInterface::CreateSectionTable() {
//     string sql = "CREATE TABLE IF NOT EXISTS Sections ( id INTEGER PRIMARY KEY NOT NULL, description TEXT, courseID INTEGER, FOREIGN KEY (courseID) REFERENCES Courses(id));";

//     if(!exectueQueryNoResultsBack(sql)) {
//         cout << "Error in creating Section Table" << endl;
//     }
// }

void DBInterface::CreateAttendanceTable() {
    string sql = "CREATE TABLE IF NOT EXISTS Attendance ( courseID INTEGER NOT NULL, studentID INTEGER NOT NULL, date TEXT, status TEXT, PRIMARY KEY(courseId, studentId), FOREIGN KEY (courseId) REFERENCES Courses(id), FOREIGN KEY (studentID) REFERENCES Students(id));";

    if(!exectueQueryNoResultsBack(sql)) {
        cout << "Error in creating Attedance Join Table" << endl;
    }
}