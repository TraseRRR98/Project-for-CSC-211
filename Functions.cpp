#include "Functions.h"
#include "PersonProfile.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void showMainMenu() // Original Main menu
{
	char choice;
	int number;

	do {
		system("CLS"); // clear the screen
		cout << "\n\n\t==========MAIN MENU============";
		cout << "\n\n\tAre you:";
		cout << "\n\n\t1. New Student";
		cout << "\n\n\t2. Existing Student";
		cout << "\n\n\t3. Exit";
		//cout << "\n\n\t4. Display all students";
		cout << "\n\n\tEnter your Choice (1 - 3): ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (choice != '1' && choice != '2' && choice != '3')
		{
			cout << "Wrong Input. Your choice has to be 1 - 3: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		system("CLS");
		switch (choice)
		{
		case '1':
			addStudent();
			break;
		case '2':
			cout << "Please enter your Student ID:";
			while(!(cin >> number))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please enter a valid ID number(has to be integer number): ";
			}
			returningStudent(number);
			break;
		case '3':
			cout << "\n\n\tThank you for using this program!\n\n";
			exit(0);
		case '$':
			displayAllStudents();
			break;
		}
	} while (choice != '3');

}

//This menu called after creating new Student or after returning student enter his information
void studentMenu(const int determinedLine)
{
	char choice;
	do
	{
		system("CLS");  // clear the screen
		cout << "\n\t============STUDENT MENU========";
		cout << "\n\n\t1. View workout plan";
		cout << "\n\n\t2. View diet plan";
		cout << "\n\n\t3. Return to main menu.";

		cout << "\n\n\tEnter your Choice(1 - 3): ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (choice != '1' && choice != '2' && choice != '3')
		{
			cout << "Wrong Input. Your choice has to be 1 - 3: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		switch (choice)
		{
		case '1':
			displayFileContent("workoutPlan.txt", determinedLine);
			break;
		case '2':
		{
			displayFileContent("dietPlan.txt", determinedLine);
			break;
		}
		case '3':
			showMainMenu();
			break;
		default:
			cout << "Invalid choice. Please enter 1, 2, or 3\n";
			break;
		}
	} while (choice != '3');
}

// Function called under option '1' in Main Menu
void addStudent() 
{
	PersonProfile student;
	student.addStudentInfo();
	ofstream outFile;
	outFile.open("studentArchive.dat", ios::binary | ios::app);
	outFile.write(reinterpret_cast<char*> (&student), sizeof(PersonProfile));
	outFile.close();
	cout << "\n\nNew student added. \nPress Enter key continue and view your workout and diet plan. ";
	cin.ignore();
	cin.get();

	int determinedLine = student.getDietPlanLine();// Creating variable to pass the calculated line to newStudentMenu
	studentMenu(determinedLine); // passing line to the menu
}

//This function called after option '2' in Main Menu
void returningStudent(int idToCheck)// This function check student Id for existence 
{
	ifstream inFile;
	PersonProfile checkedStudent; // Function will check if inputted password and actual password are the same
	string storedPassword;
	string passwordToCheck;
	double currentWeight;

	inFile.open("studentArchive.dat", ios::binary);
	
	if (!inFile)
	{
		cout << "\nFile could not be opened! \nPress Enter key to return to the main menu.";
		cin.ignore();
		cin.get();
		return;
	}

	bool flag = false;
	while (inFile.read(reinterpret_cast<char*> (&checkedStudent), sizeof(PersonProfile)))
	{
		if (checkedStudent.getId() == idToCheck)
		{
			cout << "Student found. Please Enter password:";
			cin >> passwordToCheck;
			storedPassword = checkedStudent.getPassword();

			system("CLS"); // clear the screen
			if (passwordToCheck == storedPassword) 
			{
				cout << "\nAccess allowed. \n\tHello "<< checkedStudent.getName()<< "\n\t\tEnter your current weight : ";
				while (!(cin >> currentWeight))
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter valid number(has to be integer value): ";
				}
				checkedStudent.setWeight(currentWeight);
				cout << "\nYour Weight Updated. \n\tPress Enter key to continue";
				cin.ignore();
				cin.get();
				
				int determinedLine = checkedStudent.getDietPlanLine();// Creating variable to pass the calculated line to newStudentMenu
				studentMenu(determinedLine);
			}
			else
			{
				cout << "Access denied. Password Incorrect";
			}
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "\nStudent does not exist!";
	}
	cout << "\n\tPress Enter to return to the main menu.";

	inFile.close();
	cin.ignore();
	cin.get();
}

void displayFileContent(const string& fileName, int lineNum) // reads and displays the content of the given file
{
	string line;
	ifstream inFile(fileName);
	int currentLine = 1; // set current line to 1 in order to search

	if (!inFile)
	{
		cout << "\nFile could not be opened! \nPress Enter key to return to the main menu.";
		cin.ignore();
		cin.get();
		return;
	}
	while (getline(inFile, line))
	{
		if (currentLine == lineNum)
		{
			cout << line << endl;
			break; // Exit the loop after finding and displaying the line
		}
		currentLine++;
	}
	cout << "\nPress Enter key to return to the previous menu.";

	inFile.close();
	cin.ignore();
	cin.get();
}

void displayAllStudents() //Function to display all students in the file in sorted order by name
{
	vector<PersonProfile> students;
	PersonProfile student;

	//Load students data from file
	ifstream inFile("studentArchive.dat", ios::binary);
	if (!inFile)
	{
		cout << "\nFile could not be opened! \nPress Enter key to return to the main menu.";
		cin.ignore();
		cin.get();
		return;
	}
	while (inFile.read(reinterpret_cast<char*>(&student), sizeof(PersonProfile)))
	{
		students.push_back(student);
	}
	inFile.close();

	//Sort data
	for (int i = 0; i < students.size(); i++)
	{
		for (int j = i + 1; j < students.size(); j++)
		{
			if (strcmp(students[i].getName(), students[j].getName()) > 0) // Compare names
			{
				PersonProfile temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}

	//Display sorted students
	for (auto& s : students)
	{
		cout << s; // Using overloaded operator to display student info
	}
	cout << "\nPress Enter key to return to the previous menu.";
	cin.ignore();
	cin.get();
}

ostream& operator<<(ostream& cout, const PersonProfile& studentProfile) // Overloaded operator to display student info
{
	cout << "ID: " << studentProfile.id << " - Name: " << studentProfile.name << endl;
	return cout;
}
