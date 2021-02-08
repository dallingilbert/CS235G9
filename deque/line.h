#pragma once
/***********************************************************************
 * Header:
 *    Student
 * Summary:
 *    This class contains the student input.
 * Authors:
 *    John McCleve 
 *    Dallin Gilbert
 ************************************************************************/
#ifndef LINE_h
#define LINE_h

#include <string>      // for STRING
#include <cassert>
#include "student.h"   // for STUDENT
#include "deque.h"     // for DEQUE
using namespace std;

using namespace custom;

class Line
{
private:
	deque <Student> line;
public:
	Student serveNext() throw (std::string)
	{
		if (line.empty())
			throw std::string("empty line");
		Student next = line.front();
		line.pop_front();
		return next;
	}
	void addStud(const Student& student) { line.push_back(student); }
	void addEmer(const Student& student) { line.push_front(student); }
	bool empty() const { return line.empty(); }
};
#endif