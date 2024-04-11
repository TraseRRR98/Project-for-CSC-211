#ifndef STUDENTPROFILE_H
#define STUDENTPROFILE_H

class StudentProfile
{
private:
	int id;
	char name[40];
	double weight; // in kg
	double height; // in cm
	//double age; 
	//char sex; // 'M' for Male, 'F' for Female
	char password[20];
public:
	void addStudentInfo();
	const char* getName();
	int getId();
	const char* getPassword();
	double getBMI();
	int getDietPlanLine();
	void setWeight(double new_weight);
	

};







#endif STUDENT_PROFILE_H
