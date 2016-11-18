#pragma once
#ifndef COURSEUNITCLASS_H
#define COURSEUNITCLASS_H

#include <vector>
#include <string>
using namespace std;

class CourseUnit;
class Tutor;
class Student;


class CourseUnitClass 
{
private:
	//MEMBER VARIABLES
	const unsigned short int classNumber;
	vector<Student*> studentsInClass;
	CourseUnit* courseUnit;
	Tutor* professor;
	
	void assignTeacher();
public:
	//MEMBER FUNCTIONS
	CourseUnitClass(unsigned short int cn, CourseUnit* cu);
	CourseUnitClass(unsigned short int cn, CourseUnit* cu, Tutor* t);
	void addStudent(Student* s);
	bool removeStudent(Student* s);
	void setProfessor(Tutor* t);

	//COMPARES
	friend bool compareCourseUnitClassByNumber(CourseUnitClass* cuc1, CourseUnitClass* cuc2);
	friend bool compareCourseUnitClassByNumberStudents(CourseUnitClass* cuc1, CourseUnitClass* cuc2);

	//GETS
	unsigned short int getNumberOfStudents() const { return studentsInClass.size(); }
	unsigned short int getClassNumber() const { return classNumber; }
	vector<Student*>& getStudentsInClass() { return studentsInClass; }
	CourseUnit* getCourseUnit() {return courseUnit;}

	//OPERATORS
	friend ofstream& operator<<(ofstream& file, CourseUnitClass *cuc);

	//PRINT TO SCREEN
	void show() const;
};

#endif
