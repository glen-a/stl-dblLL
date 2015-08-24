/*
glen Wiltshire

Student class definition



*/

#ifndef _STUDENT_H_
#define _STUDENT_H_

class Student{
	friend std::ostream& operator<<(std::ostream& out , const Student &e){
		out << e.getNumber() << ", " << e.getName() << ", " << e.getEmail();
		return out;
	}
	friend std::istream& operator>>(std::istream&,  Student &);
private:
	int StudentNumber;
	std::string StudentName;
	std::string email;

public:
	Student(){;}
	void something();
	void setNumber(int i){StudentNumber = i;}
	void setName(std::string n){StudentName=n;}
	void setEmail(std::string e){email=e;}
	std::string getEmail()const{return email;}
	std::string getName()const{return StudentName;}
	int getNumber()const{return StudentNumber;}
	bool operator<(const Student &);
};


#endif