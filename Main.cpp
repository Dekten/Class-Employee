//Main.cpp
#include "String.h"
#include "Employee.h"
//isEmpty
//The form: last name, first name, patronymic
//Max size of the string: 1 000 000
//
int main() {
	try {
		setlocale(LC_ALL, "rus");

		Employee s0 ("      underwood      francis      uhh   ", "TeAcHeR",       1997);
		//Employee s0 ("    j j j j j j j j j j   ", "TeAcHeR",      1997);
		Employee s1 ("      underwood      claire       uhh   ", "copyrighter",   2005);
		Employee s2 ("      stamper        douglas      uhh   ", "manager",       1995);
		Employee s3 ("      danton         remy         uhh   ", "programmer",    2011);
		Employee s4 ("      walker         garrett      uhh   ", "politic",       2007);
		Employee s5 ("      underwood      den          uhh   ", "president"          );
		Employee s6 ("      tusk           raymond      uhh   ", "billionaire",   1974);
		Employee s7 ("      meechum        edward       uhh   ", "DRIVER",        2011);
		Employee s8 ("      durant         catherine    uhh   ", "senator",       2002);
		Employee s9 ("      feng           xander       uhh   ", "businessman",   2016);
		Employee s10("      hammerschmidt  tom          uhh   ", "    EDITor   ", 2000);
		Employee s11;
		Employee s12;
		s11 = s10;
		//cin >> s12;
		cout << s0 << endl;
		//s1.setYear(100);
		

		const int nEmployees = 13;
		Employee *employee = new Employee[nEmployees];
		employee[0]  = s0;
		employee[1]  = s1;
		employee[2]  = s2;
		employee[3]  = s3;
		employee[4]  = s4;
		employee[5]  = s5;
		employee[6]  = s6;
		employee[7]  = s7;
		employee[8]  = s8;
		employee[9]  = s9;
		employee[10] = s10;
		employee[11] = s11;
		employee[12] = s12;
		showEmployees(employee, nEmployees);
		//cout << employee[20] << endl;
		cout << findMaxEmployee(employee,nEmployees).getName() << endl;
		sortEmployees(employee, nEmployees);
		showEmployees(employee, nEmployees);
	
	}

	//Exception Handling
	catch (SizeWrongException s) {
		cerr << "The size of the string is incorrect! (" << s.getValue() << ")" << endl;
	}
	catch (bad_alloc &ba) {
		cout << ba.what() << endl;
	}
	catch (EmptyObjectsException) {
		cerr << "Working with a blank line is not allowed!" << endl;
	}
	catch (DataWrongException) {
		cerr << "Incorrectly chosen number!" << endl;
	}
}
