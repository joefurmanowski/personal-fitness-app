// PersonalFitnessApp.cpp : Personal fitness application that keeps track of a user's health and activity based on user input.

#include <iostream>
#include <iomanip>
#include <string>
#include "HealthTracker.h"
using namespace std;

void getUserInfo(string& name, string& gender, int& age, int& maxInputs)
{
	// Get user's name
	cout << "What is your name?: ";
	getline(cin, name);

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

	cout << "How many days to keep history of?: ";
	cin >> maxInputs;

	// If user does not provide an integer value
	// or if they provide an inappropriate integer value,
	// keep asking user for a valid integer value until it is provided
	while (cin.fail() || maxInputs <= 0)
	{
		if (cin.fail())
		{
			cin.clear(); // Only clear error state if user provides non-integer input
			cin.ignore(10000, '\n');
		}
		cout << "The value you provided is not valid!" << endl;
		cout << "How many days to keep history of?: ";
		cin >> maxInputs;
	}

	cin.ignore(10000, '\n');
}

int main()
{
	string name, gender, exerciseType;
	int age, maxInputs;

	getUserInfo(name, gender, age, maxInputs);

	HealthTracker tracker(name, gender, age, maxInputs);

	tracker.menu();

	return 0;
}