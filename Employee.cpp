#include "Employee.h"


//Default Constructor and destructor
Employee::Employee()
{
	name_		=	"";
	position_	=	"";
	year_		=	-1;
}
Employee::~Employee() {}



//Constructor with name 
Employee::Employee(String name)
{
	name_		=	name;
	position_	=	"";
	year_		=	-1;
	standardizeEmployee(*this);
}



//Constructor with the names and position 
Employee::Employee(String name, String position)
{
	name_		=	name;
	position_	=	position;
	year_		=	-1;
	standardizeEmployee(*this);
}



//Constructor with the name, position and year of joining
Employee::Employee(String name, String position, int year)
{
	name_		=	name;
	position_	=	position;
	year_		=	year;
	standardizeEmployee(*this);
}



//The copy constructor 
Employee::Employee(const Employee& employee)
{
	name_		=	employee.name_;
	position_	=	employee.position_;
	year_		=	employee.year_;
}



//Get the name of the object
String Employee::getName()
{
	return name_;
}

//Get the position of the object
String Employee::getPosition()
{
	return position_;
}

//Get the year of the object
int Employee::getYear()
{
	return year_;
}



//Set the name
void Employee::setName(String name)
{
	name_		=	name;
	standardizeName(name_);
}

//Set the position
void Employee::setPosition(String position)
{
	position_	=	position;
	standardizePosition(position_);
}

//Set the year
void Employee::setYear(int year)
{
	year_		=	year;
}



//Overload operator <<
ostream& operator<<(ostream& os, const Employee& employee) {
	String position = employee.position_;
	String name		= employee.name_;

	bool emptyPosition	= position.isEmpty();
	bool emptyName		= position.isEmpty();
	bool wrongYear		= employee.year_ < 0;

	//pattern:
	//POSITION NAME went to work in XXXX year.
	if (emptyPosition && emptyName && wrongYear) {
		os << "No information about employee!";
	}
	else {
		if		(emptyPosition)	os << "(no position) ";
		else					os << employee.position_	<< " ";

		if		(emptyName)		os << "(no name) "; 
		else					os << employee.name_		<< " went to work in ";

		if		(wrongYear)		os << "(no year)";
		else					os << employee.year_		<< " year.";
	}
	return os;
}



//Overload operator >>
istream& operator>>(istream& is, Employee& employee) {
	cout << " Enter the name: ";
	is >> employee.name_;

	cout << " Enter the position: ";
	is >> employee.position_;

	cout << " Enter the year: ";
	is >> employee.year_;

	if (!is)
		throw DataWrongException();

	standardizeEmployee(employee);

	return is;
}



//Overload operator =
Employee Employee::operator=(const Employee& employee) {
	if (this == &employee) 
		return *this;
	else {
		name_		= employee.name_;
		position_	= employee.position_;
		year_		= employee.year_;

		return *this;
	}
}



//Overload operator ==
bool Employee::operator==(const Employee& employee) {
	bool sameName		= (name_	 == employee.name_	  );
	bool samePosition	= (position_ == employee.position_);
	bool sameYear		= (year_	 == employee.year_	  );

	return (sameName && samePosition && sameYear) ? 1 : 0;
}



//Overload operator <
bool Employee::operator<(const Employee& employee) {
	return (name_ < employee.name_) ? 1 : 0;
}



//Overload operator >
bool Employee::operator>(const Employee& employee) {
	return (name_ > employee.name_) ? 1 : 0;
}



//Function searches an array object with the greatest name
Employee findMaxEmployee(Employee* employee, const int nEmployees) {
	Employee maxEmployee = employee[0];

	for (int iEmployee = 0; iEmployee < nEmployees; iEmployee++) {
		if (employee[iEmployee] > maxEmployee) {
			maxEmployee = employee[iEmployee];
		}
	}

	return maxEmployee;
}



//Sort the array in ascending names of objects
void sortEmployees(Employee* employee, const int nEmployees) {
	Employee key;			//temporary object

	for (int iEmployee = 1; iEmployee < nEmployees; iEmployee++) {
		static int j = 0;
		key = employee[iEmployee];
		j = iEmployee - 1;
		while (j >= 0 && employee[j].getName() > key.getName()) {
			employee[j + 1] = employee[j];
			j--;
		}
		employee[j + 1] = key;
	}
}



//Function searches for the maximum size of the position
int findMaxPositionSize(Employee * employee, const int nEmployees) {
	size_t maxPositionSize = 0;

	for (int iEmployee = 0; iEmployee < nEmployees; iEmployee++) {
		size_t currentPositionSize = employee[iEmployee].position_.getLength();

		if (currentPositionSize > maxPositionSize)
				maxPositionSize = currentPositionSize;
	}
	return maxPositionSize;
}



//Function searches for the maximum size of the name
int findMaxNameSize(Employee * employee, const int nEmployees) {
	size_t maxNameSize = 0;

	for (int iEmployee = 0; iEmployee < nEmployees; iEmployee++) {
		size_t currentNameSize = employee[iEmployee].name_.getLength();

		if (currentNameSize > maxNameSize) {
				maxNameSize = currentNameSize;
		}
	}
	return maxNameSize;
}



//Function displays all the data from the array
void showEmployees(Employee * employee, const int nEmployees)
{
	size_t maxNameSize		= findMaxNameSize	 (employee, nEmployees) + 5;
	size_t maxPositionSize  = findMaxPositionSize(employee, nEmployees) + 5;

	//table base
	cout << endl << "EMPLOYEES NOW: " << nEmployees << endl;
	cout << "ID# "
		<< setw(maxNameSize) << left << "EMPLOYEE_NAME"	
		<< setw(maxPositionSize) << "POSITION"
		<< setw(5) << "YEAR"
		<< endl;

	//datas
	for (int iEmployee = 0; iEmployee < nEmployees; iEmployee++) {
		String name		= employee[iEmployee].name_;
		String position = employee[iEmployee].position_;
		size_t year		= employee[iEmployee].year_;

		bool less = false;			//report, if some string is empty
		bool incorrectName = name.isEmpty();
		bool incorrectPosition = position.isEmpty();
		bool incorrectYear = year < 0;

		//ID#
			 cout << setw(3)				<< right << iEmployee << " ";

		//EMPLOYEE_NAME
		if (incorrectName) {
			 cout << setw(maxNameSize)		<< left << "-";
			 less = true;
		}
		else cout << setw(maxNameSize)		<< left << employee[iEmployee].name_;

		//POSITION
		if (incorrectPosition) {
			 cout << setw(maxPositionSize)  << left << "-";
			 less = true;
		}
		else cout << setw(maxPositionSize)  << left << employee[iEmployee].position_;

		//YEAR
		if (incorrectYear) {
			 cout << setw(5)				<< left << "-";
			 less = true;
		}
		else cout << setw(5)				<< left << employee[iEmployee].year_;

		//if lessed 
		if (less == true) {
			 cout << setw(8)				<< right << "LESS" << endl;
		}
		else cout							<< endl;
	}
}



//Function converts the object to the standard form
void standardizeEmployee(Employee& employee) {
	standardizeName(employee.name_);

	standardizePosition(employee.position_);
}



