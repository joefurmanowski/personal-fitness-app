// Joseph Furmanowski
// Project2.cpp : Personal fitness application that keeps track of a user's health and activity.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "HealthTracker.h"
using namespace std;

bool fileExists(const string& name)
{
	ifstream file;
	file.open(name + ".txt");

	if (file.fail()) // File does not exist
	{
		// Create file with filename <name>.txt
		ofstream output(name + ".txt", ios::out);

		// Insert file header
		output << left << setw(30) << "Exercise Type" << setw(30) << right << "Exercise Time" << setw(30) << "Weight" << endl;

		output.close();
		return false;
	}
	else // File exists
	{
		return true;
	}
}

void getUserInfo(string& name, string& gender, int& age)
{
	// Get user's name
	cout << "What is your name?: ";
	getline(cin, name);

	// Check if file with filename <name>.txt already exists
	if (fileExists(name))
	{
		cout << "Welcome back, " << name << "!" << endl;
	}

	// Get user's gender
	cout << "What is your gender?: ";
	getline(cin, gender);

	// Get user's age
	cout << "What is your age?: ";
	cin >> age;

	// If user does not provide an integer value,
	// keep asking user for a valid integer value until it is provided
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "The age you provided is not valid!" << endl;
		cout << "What is your age?: ";
		cin >> age;
	}

	cin.ignore(10000, '\n');
}

int main()
{
	string name, gender, exerciseType;
	int age;

	getUserInfo(name, gender, age);

	HealthTracker tracker(name, gender, age);

	tracker.menu();

	return 0;
}