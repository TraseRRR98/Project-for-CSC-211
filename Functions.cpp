#include "Functions.h"
#include "PersonProfile.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include <conio.h>

using namespace std;

void showMainMenu() // Original Main menu
{
	char choice;
	int number;
	set<char> validInputs = { '1','2','3','$' };

	do {
		system("CLS"); // clear the screen
		cout << "\n\n\t==========MAIN MENU============";
		cout << "\n\n\tAre you:";
		cout << "\n\n\t1. New Student";
		cout << "\n\n\t2. Existing Student";
		cout << "\n\n\t3. Exit";

		choice = getValidatedCharInput("\n\n\tEnter your choice (1 - 3): ", "Wrong Input. Your choice has to be 1 - 3: ", validInputs);

		system("CLS");
		switch (choice)
		{
		case '1':
			addStudent();
			break;
		case '2':
			number = getValidatedIntInput("\n\n\tEnter your Student ID: ", "\n\tPlease enter a valid ID number(has to be positive integer number): ");
			returningStudent(number);
			break;
		case '3':
			cout << "\n\n\tThank you for using this program!\n\n";
			exit(0);
		case '$':
		{
			if (isAdminPassword())
			{
				adminMenu();
			}
			break;
		}
		}
	} while (choice != '3');

}

bool idExists(int id, const string& fileName)
{
	PersonProfile idToCheck;
	ifstream inFile(fileName, ios::binary);
	if (!inFile)
	{
		cout << "\nFile could not be opened! \nPress Enter key to return to the main menu.";
		cin.get();
		return false;
	}
	while(inFile.read(reinterpret_cast<char*>(&idToCheck), sizeof(PersonProfile)))
	{
		if (idToCheck.getId() == id)
		{
			inFile.close();
			return true; // ID already exists
		}
	}
	inFile.close();
	return false; // ID does not exist
}

// Function called under option '1' in Main Menu
void addStudent()
{
	PersonProfile* student = new PersonProfile; // Dynamically creating student objects
	int studentId = getValidatedIntInput("\nEnter your Student ID: ", "Please enter a valid ID number(has to be positive integer number): ");
	while(idExists(studentId, "studentArchive.dat"))
	{
		cout << "\nID already exists. \n\tPlease enter a different ID: ";
		studentId = getValidatedIntInput("\nEnter your Student ID: ", "Please enter a valid ID number(has to be positive integer number): ");
	}
	student->setId(studentId);
	student->addStudentInfo();
	ofstream outFile;
	outFile.open("studentArchive.dat", ios::binary | ios::app);
	if (!outFile)
	{
		cout << "Failed to open file for writing. \n";
		delete student;
		return;
	}
	outFile.write(reinterpret_cast<char*> (student), sizeof(PersonProfile));
	outFile.close();
	cout << "\n\nNew student added. \nPress Enter key continue and view your workout and diet plan. ";
	cin.ignore();
	cin.get();

	int determinedLine = student->getDietPlanLine();// Creating variable to pass the calculated line to newStudentMenu
	studentMenu(determinedLine); // passing line to the menu
	delete student;
}

//This function called after option '2' in Main Menu
void returningStudent(const int idToCheck)// This function check student Id for existence 
{
	PersonProfile* checkedStudent = new PersonProfile;
	string storedPassword, passwordToCheck;
	double currentWeight;

	if (!idExists(idToCheck, "studentArchive.dat"))
	{	
		cout << "\n\tStudent with ID " << idToCheck << " does not exist. \n\n\t\tPress Enter key to return to the main menu.";
		cin.get();
		return;
	}

	ifstream inFile;
	inFile.open("studentArchive.dat", ios::binary);
	if (!inFile)
	{
		cout << "\nFile could not be opened! \nPress Enter key to return to the main menu.";
		cin.ignore();
		cin.get();
		delete checkedStudent;
		return;
	}

	while (inFile.read(reinterpret_cast<char*> (checkedStudent), sizeof(PersonProfile)))
	{
		if (checkedStudent->getId() == idToCheck)
		{
			cout << "\nStudent found. \n\tPlease Enter password: ";
			passwordToCheck = hiddenPassword();
			storedPassword = checkedStudent->getPassword();

			system("CLS");
			if (passwordToCheck == storedPassword)
			{
				cout << "\nAccess allowed. \n\tHello " << checkedStudent->getName();
				currentWeight = getValidatedIntInput("\n\t\tPlease, Enter your current weight (in kg): ", "Please enter a valid number(has to be positive integer number): ");

				checkedStudent->setWeight(currentWeight);
				cout << "\nYour Weight Updated. \n\tPress Enter key to continue";
				cin.get();

				int determinedLine = checkedStudent->getDietPlanLine();// Creating variable to pass the calculated line to newStudentMenu
				studentMenu(determinedLine); // passing line to the menu
			}
			else
			{
				cout << "Access denied. Password Incorrect";
			}
		}
	}

	cout << "\n\tPress Enter to return to the main menu.";
	
	inFile.close();
	cin.get();
	delete checkedStudent;
}

string hiddenPassword() // Function to hide password while entering
{
	string password;
	char ch;
	while ((ch = _getch()) != '\r') // Read chars until Enter is pressed
	{
		if (ch == '\b') // Check for backspace
		{
			if (!password.empty())
			{
				cout << "\b \b"; // Erase the last asterisk from console
				password.pop_back(); // Remove the last char from password string
			}
		}
		else
		{
			password += ch; // Add the char to password string
			cout << '*'; // Print asterisk to console
		}
	}
	cout << endl;
	return password;
}

//This menu called after creating new Student or after returning student enter his information
void studentMenu(const int determinedLine)
{
	char choice;
	set<char> validInputs = { '1','2','3'};
	do
	{
		system("CLS"); 
		cout << "\n\t============STUDENT MENU========";
		cout << "\n\n\t1. View workout plan";
		cout << "\n\n\t2. View diet plan";
		cout << "\n\n\t3. Return to main menu.";

		choice = getValidatedCharInput("\n\n\tEnter your choice (1 - 3): ", "Wrong Input. Your choice has to be 1 - 3: ", validInputs);

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

void displayFileContent(const string& fileName, int lineNum) // reads and displays the content of the given file
{
	string line;
	ifstream inFile(fileName);
	int currentLine = 1; // set current line to 1 in order to search
	system("CLS");
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
		cout << "\nFile could not be opened! \n\tPress Enter key to return to the main menu.";
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
	cin.get();
}

ostream& operator<<(ostream& cout, const PersonProfile& studentProfile) // Overloaded operator to display student info
{
	cout << "| ID: "<< left << setw(10) << studentProfile.id << " | Name: " <<  studentProfile.name << endl;
	return cout;
}

char getValidatedCharInput(const string& prompt, const string& error, const set<char>& validInputs)
{
	char input;
	cout << prompt;
	while (true)
	{
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (validInputs.find(input) != validInputs.end())
		{
			return input;
		}
		cout << error;
	}
}

int getValidatedIntInput(const string& prompt, const string& error)
{
	int input;
	cout << prompt;
	while (!(cin >> input) || input < 1)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << error;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return input;
}

bool isAdminPassword()
{
	const string adminPassword = "BMCCadmin";
	string passwordToCheck;
	cout << "Please Enter predetermined admin password: ";
	passwordToCheck = hiddenPassword();;
	if (passwordToCheck == adminPassword)
	{
		return true;
	}
	else
	{
		cout << "\n\nAccess Denied. Password is incorrect. \n\tPress Enter key to return to Main Menu";
		cin.ignore();
		cin.get();
		return false;
	}
}

string toLower(const string& str) //change string and make everything lower case
{
	string lowerCaseStr;
	for (char c : str) {
		lowerCaseStr += tolower(c);
	}
	return lowerCaseStr; 
}

void adminMenu()
{
	char choice;
	int numberSearch;
	string nameSearch;
	set<char> validInputs = { '1','2','3','4','5','6','7'};

	do {
		system("CLS");
		cout << "\n\n\t==========ADMIN MENU============";
		cout << "\n\n\t1. Display student using ID";
		cout << "\n\n\t2. Display student using name";
		cout << "\n\n\t3. Delete student";
		cout << "\n\n\t4. Change student's information";
		cout << "\n\n\t5. Display ALL students";
		cout << "\n\n\t6. Return to the Main Menu";
		cout << "\n\n\t7. Exit";


		choice = getValidatedCharInput("\n\n\tEnter your choice (1 - 7): ", "Wrong Input. Your choice has to be 1 - 6: ", validInputs);

		system("CLS");
		switch (choice)
		{
		case '1':
		{
			numberSearch = getValidatedIntInput("Enter the Student ID:", "Please enter a valid ID number(has to be positive integer number): ");
			displayStudent(numberSearch);
			break;
		}
		case '2':
			cout << "Enter the Student's name: ";
			cin >> nameSearch;
			displayStudent(toLower(nameSearch));
			break;
		case '3':
			numberSearch = getValidatedIntInput("Enter the Student ID:", "Please enter a valid ID number(has to be positive integer number): ");
			deleteStudent(numberSearch);
			break;
		case '4':
			numberSearch = getValidatedIntInput("Enter the Student ID:", "Please enter a valid ID number(has to be positive integer number): ");
			changeStudentInfo(numberSearch);
			break;
		case '5':
			displayAllStudents();
			break;
		case '6':
			showMainMenu();
			break;
		case '7':
			cout << "\n\n\tThank you for using this program!\n\n";
			exit(0);
		}
	} while (choice != '7');
}

void displayStudent(const int idToCheck)
{
	PersonProfile studentToShow;
	ifstream inFile;
	inFile.open("studentArchive.dat", ios::binary);
	if (!inFile)
	{
		cout << "\nFile could not be opened! \n\tPress Enter key to return to the main menu.";
		cin.ignore();
		cin.get();
		return;
	}

	bool flag = false;
	while (inFile.read(reinterpret_cast<char*>(&studentToShow), sizeof(PersonProfile)))
	{
		if (studentToShow.getId() == idToCheck)
		{
			cout << studentToShow;
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "\n\nStudent does not exist!";
	}
	cout << "\nPress Enter key to return to the menu.";
	inFile.close();
	cin.get();
}

void displayStudent(const string nameToCheck)
{
	PersonProfile studentToShow;
	ifstream inFile;
	inFile.open("studentArchive.dat", ios::binary);
	if (!inFile)
	{
		cout << "\nFile could not be opened! \n\tPress Enter key to return to the main menu.";
		cin.ignore();
		cin.get();
		return;
	}

	bool flag = false;
	while (inFile.read(reinterpret_cast<char*>(&studentToShow), sizeof(PersonProfile)))
	{
		if (toLower(studentToShow.getName()) == toLower(nameToCheck))
		{
			cout << studentToShow;
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "\n\nStudent does not exist!";
	}
	cout << "\nPress Enter key to return to the menu.";
	inFile.close();
	cin.ignore();
	cin.get();
}

void deleteStudent(int idToDelete)
{
	PersonProfile studentToDelete;
	ifstream inFile;
	inFile.open("studentArchive.dat", ios::binary); 
	if (!inFile)
	{
		cout << "\nFile could not be opened! \n\tEnter key to return to the main menu.";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("temp.dat", ios::binary);
	while (inFile.read(reinterpret_cast<char*>(&studentToDelete), sizeof(PersonProfile)))
	{
		if(studentToDelete.getId() != idToDelete)
		{
			outFile.write(reinterpret_cast<char*>(&studentToDelete), sizeof(PersonProfile));
		}
	}
	outFile.close();
	inFile.close();
	remove("studentArchive.dat");
	rename("temp.dat", "studentArchive.dat");
	cout << "\nStudent deleted. \n\tPress Enter key to return to the menu.";
	cin.get();
}

void changeStudentInfo(int idToChange)
{
	PersonProfile studentToChange;
	bool studentFound = false;
	fstream file;
	file.open("studentArchive.dat", ios::binary|ios::in|ios::out);
	if (!file)
	{
		cout << "\nFile could not be opened! \n\tPress Enter key to return to the main menu.";
		cin.get();
		return;
	}
	while (!file.eof() && studentFound == false)
	{
		file.read(reinterpret_cast<char*>(&studentToChange), sizeof(PersonProfile));
		if (studentToChange.getId() == idToChange)
		{
			studentFound = true;
			cout << "Student found.\n" << studentToChange << "Please Enter new information: ";
			studentToChange.addStudentInfo();
			file.seekp((-1)*sizeof(PersonProfile), ios::cur);
			file.write(reinterpret_cast<char*>(&studentToChange), sizeof(PersonProfile));
			cout << "\nStudent information updated. \n\tPress Enter key to return to the menu.";
		}
	}
	file.close();
	if(studentFound == false)
	{
		cout << "\nStudent does not exist! \n\tPress Enter key to return to the menu";
	}
	cin.get();
}
