#ifndef PERSON_PROFILE_H
#define PERSON_PROFILE_H
#include <iostream>

using namespace std;

class PersonProfile
{
private:
	int id;
	char name[40];
	double weight; // in kg
	double height; // in cm
	char password[20];

public:
	void addStudentInfo();
	const char* getName();
	const int getId();
	const char* getPassword();
	const double getBMI();
	const int getDietPlanLine();
	void setId(int newID);
	void setWeight(double newWeight);
	void setPassword(const string& newPassword);
	friend ostream& operator<<(ostream& cout, const PersonProfile& studentProfile);
};







#endif PERSON_PROFILE_H
