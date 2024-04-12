#include "PersonProfile.h"
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void PersonProfile::addStudentInfo()
{
	cout << "\nPlease, Enter your name: ";
	cin.getline(name, 40);

	weight = getValidatedIntInput("\nPlease, Enter your weight (in kg): ", "Please enter a valid number(has to be positive integer number): ");

	height = getValidatedIntInput("\nPlease, Enter your height (in cm): ", "Please enter a valid number(has to be positive integer number): ");

	cout << "\nPlease, Create your password: ";
	cin >> password;
}

const char* PersonProfile::getName()
{
	return name;
}

const int PersonProfile::getId()
{
	return id;
}

const char* PersonProfile::getPassword()
{
	return password;
}

const double PersonProfile::getBMI()
{
	return weight / (pow(height / 100, 2));
}

// Function to determine which line to read from file
const int PersonProfile::getDietPlanLine()
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

void PersonProfile::setId(int newID)
{
	id = newID;
}







