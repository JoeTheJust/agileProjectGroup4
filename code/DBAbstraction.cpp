#include "DBAbstraction.h"
#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <array>
#include <string>

using namespace std;

DBAbstraction::DBAbstraction(string pathToFile) {
    int status = sqlite3_open(pathToFile.c_str(), &db);

    if(status != SQLITE_OK) {
        cout << "Error in opening the database" << endl;

        db = NULL;
    }

}

//---

DBAbstraction::~DBAbstraction() {
    if(db != NULL) {
        sqlite3_close(db);


        db = NULL;
    }
}

//---

bool DBAbstraction::exectueQueryNoResultsBack(sqlite3_stmt* myStatement) {

    bool retVal = false;

    int status = sqlite3_step(myStatement);

    if(status == SQLITE_DONE) {
        retVal = true;
    }

    sqlite3_finalize(myStatement);


    return retVal;
}

//---

bool DBAbstraction::exectueQueryNoResultsBack(string sql) {
    
    bool retVal = false;

    sqlite3_stmt* myStatement;

    int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if(status == SQLITE_OK) {
        retVal = exectueQueryNoResultsBack(myStatement);
    }

    return retVal;
}


//---

bool DBAbstraction::prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement) {

    bool retVal = false;

    int status = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    if(status == SQLITE_OK) {
        retVal = true;
    }

    return retVal;
}

vector<array<string,3>> DBAbstraction::getdateattendenceAlph(string date, string course){
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
vector<array<string,3>> DBAbstraction::getdateattendenceFreqAbsent(string date, string course){
    const char* sql = "SELECT s.firstName, s.lastName, a.status "
      "FROM Attendance a "
      " JOIN Students s ON s.id = a.studentID "
      " JOIN Courses  c ON c.id = a.courseID "
      "WHERE c.courseName = ? AND a.date = ? "
      "  AND a.status IN('AbsentExcused','AbsentUnexcused') "
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
vector<array<string,3>> DBAbstraction::getdateattendenceAbsent(string date, string course){
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
vector<array<string,2>> DBAbstraction::CommonAbsentscourse(string course){
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
        out.push_back(row);
      }
        }
    } else {
        cout << "SQL prepare error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}


