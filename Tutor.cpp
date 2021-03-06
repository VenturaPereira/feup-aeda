#include "Tutor.h"
#include "CourseUnitClass.h"
#include "Course.h"
#include "College.h"
#include "CourseUnit.h"
#include "University.h"
#include <fstream>
#include "Student.h"
#include "Utilities.h"

Tutor::Tutor(string n, Date dob, Course& c, vector<CourseUnit*>& att)
	: CollegeUser(n, dob, c), course(&c),
	ableToTeach(att)
{
	assignID();
	assignEmail();
	c.addProfessor(*this);
}

Tutor::Tutor(string n, Date dob, Date dor, Course& c, unsigned long long int &ID, vector<CourseUnit*> &ct, vector<CourseUnit*> &att)
	: CollegeUser(n, dob, c), course(&c),
	ableToTeach(att), currentlyTeaching(ct)
{
	setID(ID);
	assignEmail();
	c.addProfessor(*this);
	dateOfRegistration = dor;
}

void Tutor::tutorStudent(Student& s)
{
	students.push_back(&s);
}

bool Tutor::teachClass(CourseUnitClass& c)
{
	if (find(ableToTeach.begin(), ableToTeach.end(), &(c.getCourseUnit())) == ableToTeach.end()) //NOT ABLE TO TEACH
		return false;
		
	if (find(currentlyTeaching.begin(), currentlyTeaching.end(), &(c.getCourseUnit())) == currentlyTeaching.end()) //NOT TEACHING
	{
		c.getCourseUnit().addProfessor(*this);
		currentlyTeaching.push_back(&(c.getCourseUnit()));
	}
		
	return true;
}

void Tutor::assignEmail()
{
	string inicials;
	for (int i = 0; i < name.size(); i++)
	{
		if(iswalpha(name[i]))
			if (iswupper(name[i]))
				inicials += name[i];
	}
	if (inicials.size() == 0)
		email = name;
	else email = inicials;
	email += '@'
		+ course->getCollege().getAcronym()
		+ '.'
		+ course->getCollege().getUniversity().getAcronym()
		+ '.'
		+ course->getCollege().getUniversity().getCountryAcronym();
}

void Tutor::assignID()
{
	ID = course->getCollege().getUniversity().getLastProfessorID() + 1;
	course->getCollege().getUniversity().incrementLastProfessorID();
}

bool compareProfessorByName(Tutor* p1, Tutor* p2) 
{
	return p1->name < p2->name;
}

bool compareProfessorByID(Tutor* p1, Tutor* p2)
{
	return p1->ID < p2->ID;
}

bool compareProfessorByBirth(Tutor* p1, Tutor* p2)
{
	return p1->dateOfBirth < p2->dateOfBirth;
}

bool compareProfessorByRegistration(Tutor* p1, Tutor* p2)
{
	return p1->dateOfRegistration < p2->dateOfRegistration;
}

ofstream& Tutor::operator<<(ofstream& file)
{
	file << this->getCourse().getCollege().getUniversity().getAcronym()
		<< ';'
		<< this->getCourse().getCollege().getAcronym()
		<< ';'
		<< this->getCourse().getAcronym()
		<< ';'
		<< this->name
		<< ';'
		<< this->getDateOfBirth().getDateString()
		<< ';'
		<< this->getDateOfRegistration().getDateString()
		<< ';'
		<< this->ID
		<< ';'
		<< '{';

	for (unsigned int i = 0; i < this->ableToTeach.size(); i++) {
		file << this->ableToTeach[i]->getAcronym();
		if (i != this->ableToTeach.size() - 1)
			file << ',';
	}

	file << '}'
		<< ';'
		<< '{';

	for (unsigned int i = 0; i < this->currentlyTeaching.size(); i++) {
		file << this->currentlyTeaching[i]->getAcronym();
		if (i != this->currentlyTeaching.size() - 1)
			file << ',';
	}

	file << '}'
		 << endl;

	return file;
}

void Tutor::show() const {
	cout
		<< left
		<< setw(CONSOLE_WIDTH * 0.5)
		<< name
		<< ID
		<< '\t'
		<< setw(CONSOLE_WIDTH * 0.2)
		<< course->getAcronym()
		<< setw(CONSOLE_WIDTH * 0.2)
		<< course->getCollege().getAcronym()
		<< right
		<< endl
		<< '\t'
		<< dateOfBirth.getDateString()
		<< '\t'
		<< dateOfRegistration.getDateString()
		<< endl;
}