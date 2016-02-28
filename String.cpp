//String.cpp
#include "String.h"
const size_t MAX_SIZE = 1000000;

//Default Constructor
String::String()
{
	length_ = 0;
	string_ = 0;
}
String::~String()
{
	delete[] string_;
}



//Constructor with size of line
String::String(size_t n)
{
	if ((n < 0) || (n>MAX_SIZE)) throw SizeWrongException(n);

	length_ = n;
	Memory();
	string_[0] = '\0';
}



//Constructor with line
String::String(const char* string)
{
	length_ = 0;
	while (string[length_] != '\0') {			//length of the string
		length_++;
	}
	if (length_ > MAX_SIZE) throw SizeWrongException(length_);

	Memory();

	for (size_t i = 0; i <= length_; i++) {	//The transfer of the corresponding elements
		string_[i] = string[i];
	}
}



//The constructor with n times taken the symbol of symbol
String::String(size_t nSymbols, char symbol)
{
	if ((nSymbols < 0) || (nSymbols > MAX_SIZE)) throw SizeWrongException(nSymbols);
	length_ = nSymbols;

	Memory();

	for (size_t i = 0; i < length_; i++) {
		string_[i] = symbol;
	}
	string_[length_] = '\0';
}



//The copy constructor
String::String(const String& s)
{
	length_ = s.length_;
	Memory();
	for (size_t i = 0; i <= length_; i++) {
		string_[i] = s.string_[i];
	}
}



//Get the length of the line
size_t String::getLength()
{
	return length_;
}



//Overload operator <<
ostream& operator<<(ostream& os, const String& string) {
	if		(string.string_		==   0)  os << "The string is not defined!";
	else if (string.string_[0]	== '\0') os << "The string is empty!";
	else 								 os << string.string_;
	return os;
}



//Overload operator >>
istream& operator>>(istream& is, String& string) {
	char temp[MAX_SIZE + 1];					//temporary array

	cout << "Enter the string: ";
	is.getline(temp, MAX_SIZE + 1);				//get line
	if (!is)
		throw DataWrongException();

	while (temp[string.length_] != '\0') {
		string.length_++;
	}

	MemoryTo(string);

	for (size_t i = 0; i <= string.length_; i++) {	//transfer
		string.string_[i] = temp[i];
	}
	return is;
}



//Overload operator +
String String::operator+(const String& string) {
	if ((string_ == 0) && (string.string_ == 0))
		throw EmptyObjectsException();

	String temp;				//temporary string
	temp.length_ = length_ + string.length_;
	MemoryTo(temp);
	//Filling TEMP first term of the sum
	for (size_t i = 0; i < length_; i++) {
		temp.string_[i] = string_[i];
	}
	//Filling TEMP second term of the sum
	for (size_t i = length_; i <= temp.length_; i++) {
		temp.string_[i] = string.string_[string.length_ - temp.length_ + i];
	}

	return temp;
}



//Overload operator +=
String String::operator+=(const String& string) {
	*this = *this + string;		//It uses the overloaded operator +
	return *this;
}



//Overload operator =
String String::operator=(const String& string) {
	if (this == &string) 
		return *this;
	if (string.string_ == 0)
		throw EmptyObjectsException();

	delete[] string_;			//deallocation
	length_ = string.length_;
	Memory();
	for (size_t i = 0; i <= length_; i++) {
		string_[i] = string.string_[i];
	}

	return *this;
}



//Overload operator ==
bool String::operator==(const String& string) {
	if (length_ != string.length_)		//Length of the string must be the same
		return 0;

	for (size_t i = 0; i < length_; i++) {
		bool mismatchFound = (string_[i] != string.string_[i]);
		if (mismatchFound) 
			return 0;
	}

	return 1;
}



//Overload operator <
bool String::operator<(const String& string) {
	if ((string_ == 0) || (string.string_ == 0))
		throw EmptyObjectsException();

	//We are looking for the nearest a mismatch
	size_t i = 0;
	while ((string_[i] == string.string_[i]) && (string_[i] != '\0') && (string.string_[i] != '\0')) 
		i++;

	bool NullOnLeft	 = (	   string_[i] == '\0');
	bool NullOnRight = (string.string_[i] == '\0');

	bool leftLowerRight = (string_[i] < string.string_[i]);
	bool leftOverRight	= (string_[i] > string.string_[i]);

	//Delete the condition of equality of rows
	if (NullOnLeft && NullOnRight)
	 	 return 0;

	//Test conditions
	else if (leftLowerRight && !NullOnLeft && !NullOnRight || NullOnLeft) 
		 return 1;

	else if ( leftOverRight && !NullOnLeft && !NullOnRight || NullOnRight)
		 return 0;

	else return 0;
}



//Overload operator >
bool String::operator>(const String& string) {
	if ((string_ == 0) || (string.string_ == 0))
		throw EmptyObjectsException();

	//We are looking for the nearest a mismatch
	size_t i = 0;
	while ((string_[i] == string.string_[i]) && (string_[i] != '\0') && (string.string_[i] != '\0'))
		i++;
	
	bool NullOnLeft  = (	   string_[i] == '\0');
	bool NullOnRight = (string.string_[i] == '\0');

	bool leftLowerRight = (string_[i] < string.string_[i]);
	bool leftOverRight  = (string_[i] > string.string_[i]);

	//Delete the condition of equality of rows
	if (NullOnLeft && NullOnRight)
		 return 0;

	//Test conditions
	else if (leftLowerRight && !NullOnLeft && !NullOnRight || NullOnLeft) 
		 return 0;
	
	else if (leftOverRight && !NullOnLeft && !NullOnRight || NullOnRight) 
		 return 1;
	
	else return 0;
	
}



//Function reported, if the string is empty
bool String::isEmpty() {
	return (string_[0] == '\0') ? 1 : 0;
}



//Function allocates memory for a base object
void String::Memory() {
	string_ = new char[length_ + 1];
}



//Function allocates memory for the selected object
void MemoryTo(String& temp) {
	temp.string_ = new char[temp.length_ + 1];
}



//Function inserts a row ADD in the ORIGINAL row on the n-th symbol
//Ex: insertString(oooo, i, 3) -> ooioo
void insertString(String &original, const String &add, size_t n) {
	if ((original.string_ == 0) || (add.string_ == 0))
		throw EmptyObjectsException();
	if ((n > original.length_ + 1) || (n < 0))
		throw DataWrongException();

	//it contains a piece of ORIGINAL before the ADD
	String temp;
	temp.length_ = (n - 1);
	MemoryTo(temp);
	for (size_t i = 0; i < (n - 1); i++) {
		temp.string_[i] = original.string_[i];
	}
	temp.string_[temp.length_] = '\0';

	//it contains a piece of ORIGINAL after the ADD
	String temp2;
	temp2.length_ = original.length_ - n + 1;
	MemoryTo(temp2);
	for (size_t i = 0; i <= temp2.length_; i++) {
		temp2.string_[i] = original.string_[n + i - 1];
	}

	//association
	temp += add;
	temp += temp2;
	original = temp;
}



//Function cuts out a piece of string from n to k
void cutString(String &string, size_t n, size_t k) {
	if (string.string_ == 0)
		throw EmptyObjectsException();
	if ((n > k) || (n<1) || (k > string.length_))
		throw DataWrongException();

	String temp;
	temp.length_ = string.length_ - (k - n + 1);	//the final line

	MemoryTo(temp);
	
	//Filling temporary array elements from 1 to n-1
	for (size_t i = 0; i < (n - 1); i++) {
		temp.string_[i] = string.string_[i];
	}
	
	//Filling temporary array elements from k + 1 to the end of line
	for (size_t i = (n - 1); i <= temp.length_; i++) {
		temp.string_[i] = string.string_[k - n + i + 1];
	}
	
	string = temp;
}



//Function looks for a string WHAT in string WHERE, and outputs the symbol number
void findString(const String &where, const String &what) {
	if ((where.string_ == 0) || (what.string_ == 0))
		throw EmptyObjectsException();
	if (what.length_ > where.length_)
		throw DataWrongException();
	
	size_t k = 0;
	size_t j = 0;
	for (size_t i = 0; i < where.length_; i++) {
		//k -  the symbol number of WHAT 
		//j -  the symbol number of WHERE 
		j = i;
		//We are looking for the nearest a mismatch, if a match is found
		while ((what.string_[k] == where.string_[j]) && (what.string_[k] != '\0')) {
			k++;
			j++;
		}
		bool endOfWhat = (what.string_[k] == '\0');
		if  (endOfWhat) {
			cout << "The string enters another on " << (j - k + 1) << " symbol." << endl;
			return;
		}
	}
	cout << "String is not included in the other!";
}



//Function changes lowercase characters to uppercase after the gap
void toUppercaseFirsts(String& string) {

	//First symbol
	if (string.string_[0] >= 'a' && string.string_[0] <= 'z') 
		string.string_[0] += 'A' - 'a';
	
	//The following characters after gaps
	for (int i = 0; string.string_[i] != '\0'; i++) 
		if ((string.string_[i] >= 'a' && string.string_[i] <= 'z') && (string.string_[i - 1] == ' ')) 
			string.string_[i] += 'A' - 'a';
}



//Function changes all capital letters to lowercase
void toLowercaseAll(String& string) {

	for (size_t i = 0; i < string.length_; i++) 
		if (string.string_[i] >= 'A' && string.string_[i] <= 'Z') 
			string.string_[i] -= 'A' - 'a';
		
}



//Function converts the object`s name to the standard form
void standardizeName(String& string) {

	int nGaps = 0;		//count the gaps

	//Removing spaces before the name
	while (string.string_[nGaps + 1] == ' ') 
		nGaps++;
	if (nGaps != 0) 
		cutString(string, 1, nGaps + 1);
	
	//Removing spaces after the name
	nGaps = string.length_;
	while (string.string_[nGaps - 1] == ' ') 
		nGaps--;
	if (nGaps != string.length_)
		cutString(string, nGaps + 1, string.length_);

	//Removing extra spaces in the name
	for (int i = 1, nGaps = 0; string.string_[i - 1] != '\0'; ) {

		//while the gap before i and the gap on i 
		while ((string.string_[i - 1] == ' ') && (string.string_[i] == ' ')) {
			nGaps++;
			i++;
		}
		if (nGaps != 0) {
			cutString(string, i - nGaps + 1, i);
			i -= nGaps;
			nGaps = 0;
		}
		i++;
	}

	//It cuts a piece of surname and patronymic
	//k is the gap position
	//i is the now position
	for (size_t i = 1, k = 0; i <= (string.length_ + 1); i++) {

		bool gapNow		  = (string.string_[i - 1] == ' ');
		bool endNow		  = (string.string_[i - 1] == '\0');
		bool singleLetter = (i - k == 2);
		bool wasGap		  = (k != 0);

		if		((gapNow || endNow) && !wasGap)					k = i;
		else if ((gapNow || endNow) && wasGap && singleLetter)  k = i;
		else if ((gapNow || endNow) && wasGap && !singleLetter) {
			cutString(string, k + 2, i - 1);
			insertString(string, ".", k + 2);
			i = k;
			k = 0;
		}
	}

	//Changes lowercase characters to uppercase 
	toUppercaseFirsts(string);
}



//Function converts the object`s position to the standard form
void standardizePosition(String& string) {

	//Removing spaces before the position
	int nGaps = 0;
	while (string.string_[nGaps + 1] == ' ') 
		nGaps++;
	if (nGaps != 0) 
		cutString(string, 1, nGaps + 1);
	
	//Removing spaces after the position
	nGaps = string.length_;
	while (string.string_[nGaps - 1] == ' ') 
		nGaps--;
	if (nGaps != string.length_) 
		cutString(string, nGaps + 1, string.length_);
	
	//Changes all uppercase characters to lowercase
	toLowercaseAll(string);
}




