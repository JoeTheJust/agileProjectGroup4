#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Course
{
public:
	//default constructor
	Course(string name, const string& filePath)
	{
		courseName = name;
		CreateSections(filePath);
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
	void CreateSections(const string& filePath)
	{

	}
	string courseName;
	vector <Section> sections;
}

struct Section
{
	vector <Student> students;
	vector <string> meetingDates;
};

struct Student
{
	string studentName;
	StudentAttendance attendanceRecord;
};

struct StudentAttendance
{
	vector <string> dates;
	vector <bool> present;
	vector <bool> tardy;
	vector <bool> excused;
};