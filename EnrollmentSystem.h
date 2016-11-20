#pragma once

#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

class University;
class College;
class Course;
class CourseUnit;
class CourseUnitClass;
class Student;
class Tutor;
class Date;

#include <vector>
#include <string>
using namespace std;


class EnrollmentSystem
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_CREDITS;
	string universityFile = "universities.txt",
		collegesFile = "colleges.txt",
		coursesFile = "courses.txt",
		courseUnitsFile = "courseunits.txt",
		courseUnitClassesFile = "courseunitclasses.txt",
		studentsFile = "students.txt",
		professorsFile = "tutors.txt";
	vector<University*> universitiesVector;

	//SORTING OPTIONS (POINTERS TO THE SORTING FUNCTIONS)
	bool(*universitySortOption)(University* l, University* r);
	bool(*collegeSortOption)(College* l, College* r);
	bool(*courseSortOption)(Course* l, Course* r);
	bool(*courseUnitSortOption)(CourseUnit* l, CourseUnit* r);
	bool(*courseUnitClassSortOption)(CourseUnitClass* l, CourseUnitClass* r);
	bool(*studentsSortOption)(Student* l, Student* r);
	bool(*professorsSortOption)(Tutor* l, Tutor* r);

		
public:
	//MEMBER FUNCTIONS
	EnrollmentSystem(unsigned int mc);
	~EnrollmentSystem() {}
	void addUniversity(University& u) { universitiesVector.push_back(&u); }
	void removeUniversity(University& u);

	//PRINT TO SCREEN
	void showUniversities();
	void showColleges();
	void showCourses();
	void showCourseUnits();
	void showCourseUnitClasses();	
	void showProfessors();
	void showStudents();


	template<class T>
	friend void saveToFiles(vector<T*> const &vector, string &fileName)
	{
		ofstream file;
		file.open(fileName);
		for (unsigned int i = 0; i < vector.size(); i++)
			(*vector[i]).operator<<(file);
		file.close();
	}

	//HANDLERS (COMMUNICATION WITH THE USER)
	/*!
	* Adds Students to Course
	*/
	friend bool addStudentHandler(EnrollmentSystem& s); 

	/*!
	*	Removes Students from Course
	*/
	friend bool removeStudentHandler(EnrollmentSystem& s); 

	/*!
	*	Shows Course Units available to Enroll and Adds a Student to them
	*/
	friend bool enrollmentHandler(EnrollmentSystem& s); 

	/*!
	*	
	*/
	friend bool studentFinishedCourseUnitHandler(EnrollmentSystem& s); //REMOVES THE STUDENT FROM THE COURSE UNIT IF THE GRADE IS HIGH ENOUGH
	//friend bool addUniversityHandler(EnrollmentSystem& s);
	friend bool removeUniversityHandler(EnrollmentSystem& s);
	//friend bool addCollegeHandler(EnrollmentSystem& s);
	//friend bool removeCollegeHandler(EnrollmentSystem& s);
	//friend bool addCourseHandler(EnrollmentSystem& s);
	//friend bool removeCourseHandler(EnrollmentSystem& s);

	//LOAD AND SAVE FROM FILES
	void loadHandler();
	void saveHandler();

	void loadStudents();
	void loadProfessors();
	void loadCourseUnitClasses();
	void loadUniversities();
	void loadColleges();
	void loadCourses();
	void loadCourseUnits();
	
	
	//SORT FUNCTIONS
	bool changeCourseUnitSortOption(unsigned int &option);
	bool changeCourseUnitClassSortOption(unsigned int &option);
	bool changeStudentsSortOption(unsigned int &option);
	bool changeProfessorsSortOption(unsigned int &option);

	//GETS
	/*!
	*		
	*/
	unsigned int getMaxCredits() const { return MAXIMUM_CREDITS; }
	vector<University*>& getUniversities() { return universitiesVector; }
	friend University& getUniversity(EnrollmentSystem &s);
	friend College& getCollege(EnrollmentSystem &s);
	friend Course& getCourse(EnrollmentSystem &s);
	friend CourseUnit& getCourseUnit(EnrollmentSystem &s);
	Student& getStudent(unsigned long long int &ID);
	Tutor& getProfessor(unsigned long long int &ID, Course& course);
	University& getUniversity(string &acronym);
	College& getCollege(string &acronym, University& university);
	Course& getCourse(string &acronym, College& college);
	CourseUnit& getCourseUnit(string &acronym, Course& course);
	CourseUnitClass& getCourseUnitClass(unsigned int &classNumber, CourseUnit& courseUnit);
	vector<College*> getAllColleges();
	vector<Course*> getAllCourses();
	vector<CourseUnit*> getAllCourseUnits();
	vector<CourseUnitClass*> getAllCourseUnitClasses();
	vector<Student*> getAllStudents();
	vector<Tutor*> getAllProfessors();

	
};

#endif