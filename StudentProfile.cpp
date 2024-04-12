#include "PersonProfile.h"
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void PersonProfile::addStudentInfo()
{
	cout << "\n\nPlease Enter your student ID: ";
	while (!(cin >> id))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid ID number(has to be integer number): ";
	}

	cout << "\nPlease, Enter your name: ";
	cin.ignore();
	cin.getline(name, 40);

	cout << "\nPlease, Enter your weight (in kg): ";
	while (!(cin >> weight))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid weight(has to be integer number): ";
	}

	cout << "\nPlease, Enter your height (in cm): ";
	while(!(cin >> height))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid height(has to be integer number): ";
	}

	cout << "\nPlease, Create your password: ";
	cin >> password;
}

const char* PersonProfile::getName()
{
	return name;
}

int PersonProfile::getId()
{
	return id;
}

const char* PersonProfile::getPassword()
{
	return password;
}

double PersonProfile::getBMI()
{
	return weight / (pow(height / 100, 2));
}

// Function to determine which line to read from file
int PersonProfile::getDietPlanLine()
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
	else // line 3 have plan to loose weight
	{
		return 3;
	}
}

void PersonProfile::setWeight(double new_weight)
{
	weight = new_weight;
}
