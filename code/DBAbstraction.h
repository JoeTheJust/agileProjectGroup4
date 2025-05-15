#pragma once
#include <string>
#include "sqlite3.h"
#include "vector"
using namespace std;

class DBAbstraction {
public:
    //Constructor and Destructor for this class
    DBAbstraction(string pathToFile);
    ~DBAbstraction();
    // will return first name, last name, and status 
    vector<array<string,3>> getdateattendenceAlph(string date, string course);
    vector<array<string,3>> getdateattendenceFreqAbsent(string date, string course);
    vector<array<string,3>> getdateattendenceAbsent(string date, string course);
    vector<array<string,2>> CommonAbsentscourse(string course);
protected:
    //Pointer to the database
    sqlite3* db;

    //Helper methods for creating tables/data with queries 
    bool exectueQueryNoResultsBack(sqlite3_stmt* myStatement);
    bool exectueQueryNoResultsBack(string sql);
    bool prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement);
};