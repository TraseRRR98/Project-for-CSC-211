#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <set>

using namespace std;

void showMainMenu();
bool idExists(int id, const string& fileName);
void studentMenu(const int determinedLine);
void addStudent();
void returningStudent(const int idToCheck);
string hiddenPassword();
void displayFileContent(const string& fileName, int lineNum);
void displayAllStudents();
char getValidatedCharInput(const string& prompt, const string& error, const set<char>& validInputs);
int getValidatedIntInput(const string& prompt, const string& error);
bool isAdminPassword();
string toLower(const string& str);
void adminMenu();
void displayStudent(const int idToCheck);
void displayStudent(const string nameToCheck);
void deleteStudent(int idToDelete);
void changeStudentInfo(int idToChange);


#endif FUNCTIONS_H
