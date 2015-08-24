/*
glen Wiltshire
gaw844
4067393

Student class member functions

For some reason using the given testing commands (such as ./task1 < input1.txt or cat input1.txt | ./task1) makes the 
student output go all weird (or atleast it does on my end). Manualy entering the data (or even copy paste from the 
input file) works fine though.
It seems to be working on banshee
*/

#include "OrderedList.h"
#include "Student.h"

std::istream& operator>>(std::istream& in, Student &e) {
	std::string temp;
	int tempi=0;
	std::cout << "Input Number: ";
	in >> tempi;
	e.setNumber(tempi);
	std::cout << "Input Name: "; 
	in.ignore();
	std::getline (in,temp);
	e.setName(temp);
	std::cout << "Input Email: ";
	in >> temp;
	e.setEmail(temp);
	return in;
}


bool Student::operator<(const Student &right){
	if(email<right.email) //both are strings
		return true;
	return false;


}

