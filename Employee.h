//Employee.h
//All definitions are in "Employee.cpp"
#pragma once
#include <iostream>
using namespace std;
#include "String.h"
#include <iomanip>		//IO Manipulators

class Employee
{
private:
	String name_;			//surname and initials
	String position_;		//position held
	int year_;				//year of joining
public:
	//Default Constructor and destructor
	Employee();
	~Employee();

	//Constructor with name
	Employee (String name);

	//Constructor with the names and position
	Employee (String name, String position);

	//Constructor with the name, position and year of joining
	Employee (String name, String position, int year);

	//The copy constructor
	Employee(const Employee& employee);



	//Get the name of the object
	String getName();

	//Get the position of the object
	String getPosition();

	//Get the year of the object
	int getYear();



	//Set the name
	void setName(String name);

	//Set the position
	void setPosition(String position);

	//Set the year
	void setYear(int year);



	//Overload operator <<
	friend ostream& operator<< (ostream&, const Employee&);

	//Overload operator >>
	friend istream& operator>> (istream&, Employee&);

	//Overload operator =
			Employee operator= (const Employee& employee);

	//Overload operator ==
			bool	operator== (const Employee& employee);

	//Overload operator <
			bool	operator<  (const Employee& employee);

	//Overload operator >
			bool	operator>  (const Employee& employee);



	//Function searches an array object with the greatest name
	friend Employee findMaxEmployee(Employee* employee, const int nEmployees);

	//Sort the array in ascending names of objects
	friend void sortEmployees(Employee* employee, const int nEmployees);

	//Function searches for the maximum size of the position
	friend int findMaxPositionSize(Employee * employee, const int nEmployees);

	//Function searches for the maximum size of the name
	friend int findMaxNameSize(Employee * employee, const int nEmployees);

	//Function displays all the data from the array
	friend void showEmployees(Employee * employee, const int nEmployees);

	//Function converts the object to the standard form
	friend void standardizeEmployee(Employee& employee);
};

