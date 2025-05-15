#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DBInterface.h"

using namespace std;

struct StudentAttendance
{
	vector <string> dates;
	vector <bool> present;
	vector <bool> tardy;
	vector <bool> excused;
};

struct Student
{
	string studentFirstName;
	string studentLastName;
	StudentAttendance attendanceRecord;
};

class Course
{
public:
	//default constructor
	Course(string name, const string& filePath, DBInterface& database)
	{
		courseName = name;
		database.EnterCourse(courseName);
		CreateCourse(filePath, database);
	}
	//course name (typed manually)
	void setCourseName(string name)
	{
		courseName = name;
	}
	string getCourseName()
	{
		return courseName;
	}
private:
	// \/\/\/--[everything else below will be gotten from a file/database]--\/\/\/
	//num of sections
	//num of students per section
	//name of every student in section
	void CreateCourse(const string& filePath, DBInterface& database)
	{
		ifstream fin;
		fin.open(filePath);
		string studentNames;

		//every student must be on a new line for this to work correctly
		while (getline(fin, studentNames))
		{
			stringstream ss(studentNames);
			Student student;
			ss >> student.studentFirstName >> student.studentLastName;
			students.push_back(student);
		}

		for(int i = 0; i < students.size(); i++) {
			database.EnterStudent(students[i].studentFirstName, students[i].studentLastName);
		}

		fin.close();
	}

	//Attendence function

	//Database info send function\s

	//Set up for mass student integration, course (one at a time) integration, and student's attendance (one at a time) integration

	// int getStudentID(string fName, string lName) {

	// }
	int getCourseID(string courseName);
	void SendAttendanceInfo(Student student, Course course);
	

	//Database info recieve function

	string courseName;
	vector <Student> students;
	vector <string> meetingDates;
};