#include "DBInterface.h"
#include <vector>
#include <array>
#include <string>

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

void DBInterface::EnterCourse(string courseName) {
    string sql = "INSERT INTO Courses (courseName) VALUES (?);";

    sqlite3_stmt* myStatement;

    int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if(status == SQLITE_OK) {
        sqlite3_bind_text(myStatement, 1, courseName.c_str(), -1, SQLITE_STATIC);

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
    string sql = "CREATE TABLE IF NOT EXISTS Courses ( id INTEGER PRIMARY KEY NOT NULL, courseName TEXT);";

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


vector<array<string,3>> DBInterface ::getdateattendenceAlph(string date, string course){
 const char* sql = "SELECT s.firstName, s.lastName, a.status "
      "FROM Attendance a "
      " JOIN Students s ON s.id = a.studentID "
      " JOIN Courses  c ON c.id = a.courseID "
      "WHERE c.courseName = ? AND a.date = ? "
      "ORDER BY s.lastName, s.firstName;";
    sqlite3_stmt* stmt = nullptr;
    vector<array<string,3>> out;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
           while (sqlite3_step(stmt) == SQLITE_ROW) {
        array<string,3> row;
        row[0] = (char*)sqlite3_column_text(stmt, 0);
        row[1] = (char*)sqlite3_column_text(stmt, 1);
        row[2] = (char*)sqlite3_column_text(stmt, 2);
        out.push_back(row);
      }
        }
    } else {
        cout << "SQL prepare error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

vector<array<string,3>> DBInterface ::getdateattendenceAbsent(string date, string course){
    const char* sql = "SELECT s.firstName, s.lastName, a.status "
      "FROM Attendance a "
      " JOIN Students s ON s.id = a.studentID "
      " JOIN Courses  c ON c.id = a.courseID "
      "WHERE c.courseName = ? AND a.date = ? "
      "ORDER BY ("
        "SELECT COUNT(*) FROM Attendance x "
        " WHERE x.courseID=a.courseID "
        "   AND x.studentID=a.studentID "
        "   AND x.status IN('AbsentExcused','AbsentUnexcused')"
      ") DESC, s.lastName, s.firstName;";
    sqlite3_stmt* stmt = nullptr;
    vector<array<string,3>> out;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
           while (sqlite3_step(stmt) == SQLITE_ROW) {
        array<string,3> row;
        row[0] = (char*)sqlite3_column_text(stmt, 0);
        row[1] = (char*)sqlite3_column_text(stmt, 1);
        row[2] = (char*)sqlite3_column_text(stmt, 2);
        out.push_back(row);
      }
        }
    } else {
        cout << "SQL prepare error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}
vector<array<string,2>> DBInterface::CommonAbsentscourse(string course){
    const char* sql = "SELECT s.firstName||' '||s.lastName AS fullName, COUNT(*) AS absCount "
      "FROM Attendance a "
      " JOIN Students s ON s.id = a.studentID "
      " JOIN Courses  c ON c.id = a.courseID "
      "WHERE c.courseName = ? "
      "  AND a.status IN('AbsentExcused','AbsentUnexcused') "
      "GROUP BY a.studentID "
      "ORDER BY absCount DESC;";
    sqlite3_stmt* stmt = nullptr;
    vector<array<string,2>> out;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
           while (sqlite3_step(stmt) == SQLITE_ROW) {
        array<string,2> row;
        row[0] = (char*)sqlite3_column_text(stmt, 0);
        row[1] = (char*)sqlite3_column_text(stmt, 1);
        //add row
        out.push_back(row);
      }
        }
    } else {
        cout << "SQL prepare error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}