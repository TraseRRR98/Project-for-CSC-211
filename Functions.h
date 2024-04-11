#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>

using namespace std;

void showMainMenu();
void studentMenu(const int determinedLine);
//void returnedStudentMenu();
void addStudent();
void returningStudent(int idToCheck);
void displayFileContent(const string& fileName, int lineNum);
void displayAllStudents();


#endif FUNCTIONS_H
