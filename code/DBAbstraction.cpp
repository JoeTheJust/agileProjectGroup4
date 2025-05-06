#include "DBAbstraction.h"
#include <iostream>
#include "sqlite3.h"

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