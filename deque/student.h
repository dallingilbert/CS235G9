#pragma once
/***********************************************************************
 * Header:
 *    Student class
 * Summary:
 *    This class contains the student input.
 * Authors:
 *    John McCleve 
 *    Dallin Gilbert
 ************************************************************************/
#ifndef Student_h
#define Student_h

#include <string>      // for STRING
#include <cassert>
using namespace std;

class Student
{
private:
	// private member variables
	string name;
	string Class;
	int time;
	bool emer;

public:
	// default constructor
	Student() : time(0) { };

	// getters 
	string getName() const { return name; }
	string getClass() const { return Class; }
	int getTime() const { return time; }
	bool getEmer() const { return emer; }

	// setters 
	void setName(string name) { this->name = name; }
	void setClass(string Class) { this->Class = Class; }
	void setTime(int time) { this->time = time; }
	void setEmer(bool emer) { this->emer = emer; }
};
#endif