#include "StudentProfile.h"
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void StudentProfile::addStudentInfo()
{
	cout << "\n\nPlease Enter your student ID: ";
	cin >> id;
	cout << "\nPlease, Enter your name: ";
	cin.ignore();
	cin.getline(name, 40);
	cout << "\nPlease, Enter your weight (in kg): ";
	cin >> weight;
	cout << "\nPlease, Enter your height (in cm): ";
	cin >> height;
	cout << "\nPlease, Create your password: ";
	cin >> password;
}

const char* StudentProfile::getName()
{
	return name;
}

int StudentProfile::getId()
{
	return id;
}

const char* StudentProfile::getPassword()
{
	return password;
}

double StudentProfile::getBMI()
{
	return weight / (pow(height / 100, 2));
}

// Function to determine which line to read from file
int StudentProfile::getDietPlanLine()
{
	double bmi = getBMI();
	if (bmi < 18.5) // line 1 have plan to gain weight
	{
		return 1;
	}
	else if (bmi >= 18.5 && bmi < 24.9)// line 2 have plan to maintain weight
	{
		return 2;
	}
	else // line 2 have plan to loose weight
	{
		return 3;
	}
}

void StudentProfile::setWeight(double new_weight)
{
	weight = new_weight;
}





