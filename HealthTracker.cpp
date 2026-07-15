#include "HealthTracker.h"
#include "HealthData.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

HealthTracker::HealthTracker(string name, string gender, int age, int size)
{
	this->name = name;
	this->gender = gender;
	this->age = age;
	this->size = size;
	this->history = new HealthData[size];
}

HealthTracker::~HealthTracker()
{
	delete[] history;
	history = NULL;
}

void shiftArrayLeft(HealthData myArray[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		myArray[i] = myArray[i + 1];
	}
}

void HealthTracker::input()
{
	double weight, exerciseTime;
	string exerciseType;

	HealthData data;

	cout << "You selected option 1." << endl << endl;

	// If user has logged 'size' inputs,
	// the elements of the history arrays are shifted to the left,
	// freeing up a space at the last index where we will insert the user's next (most recent) inputs.
	if (this->counter == this->size)
	{
		shiftArrayLeft(this->history, this->counter);
		this->counter = this->size - 1; // The last index of the history array is (size - 1)
		// 'size' elements in each array means indices range from 0 to (size - 1)
	}

	// Get user's weight
	cout << "What is your weight (in kg)?: ";
	cin >> weight;
	data.setWeight(weight);

	// If user does not provide an integer value,
	// keep asking user for a valid integer value until it is provided
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "The weight you provided is not valid!" << endl;
		cout << "What is your weight (in kg)?: ";
		cin >> weight;
		data.setWeight(weight);
	}

	cin.ignore(10000, '\n');

	// Get user's exercise type
	cout << "What was the type of exercise?: ";
	getline(cin, exerciseType);
	data.setExerciseType(exerciseType);

	// Get user's exercise time
	cout << "How long did you exercise for (in minutes)?: ";
	cin >> exerciseTime;
	data.setExerciseTime(exerciseTime);

	// If user does not provide an integer value,
	// keep asking user for a valid integer value until it is provided
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "The exercise time you provided is not valid!" << endl;
		cout << "How long did you exercise for (in minutes)?: ";
		cin >> exerciseTime;
		data.setExerciseTime(exerciseTime);
	}

	cin.ignore(10000, '\n');
	
	// Store health data (HealthData object) in the history array 
	this->history[counter] = data;

	cout << endl << "Weight and exercise information logged successfully!";

	this->counter++;
}

void HealthTracker::printHistory()
{
	cout << "You selected option 3." << endl;

	cout << endl << "Name: " << this->name << endl;
	cout << "Gender: " << this->gender << endl;
	cout << "Age: " << this->age << endl;

	if (this->counter == 0) // User has not input any fitness data yet
	{
		cout << endl << "There are no fitness data inputs to display yet." << endl;
	}
	else
	{
		cout << endl << "History of inputs from most recent to oldest (displaying up to last " << this->size << " entries):" << endl;

		// Iterate the array in reverse which displays entries from newest to oldest newest
		for (int i = this->counter - 1; i >= 0; i--)
		{
			this->history[i].print();
		}
	}
}

void HealthTracker::printRecent()
{
	cout << "You selected option 2." << endl;

	if (this->counter == 0) // User has not input any fitness data yet
	{
		cout << endl << "No fitness data to print." << endl;
	}
	else
	{
		cout << endl;
		cout << this->name << " (" << this->gender << ", " << this->age << ")" << endl;
		this->history[counter - 1].print();
	}
}

void HealthTracker::menu()
{
	int option;
	while (true)
	{
		cout << endl << "--------------------------------------";
		cout << endl << "<< Personal Fitness App Menu >>" << endl;
		cout << "Please select from one of the following options:" << endl;
		cout << setw(5) << "- " << "Option 1: Input today's weight and exercise information;" << endl;
		cout << setw(5) << "- " << "Option 2: Display your latest health and activity information;" << endl;
		cout << setw(5) << "- " << "Option 3: Display your health and activity input history;" << endl;
		cout << setw(5) << "- " << "Option 4: Exit the program." << endl;
		cout << "--------------------------------------" << endl;

		// Get user's option choice
		cout << endl << "Please select an option (1-4): ";
		cin >> option;

		// If user provides a non-integer value
		// or an option that is not present in the menu,
		// keep asking user for a valid value until it is provided
		while (option != 1 && option != 2 && option != 3 && option != 4)
		{
			if (cin.fail())
			{
				cin.clear(); // Only clear error state if user provides non-integer input
				cin.ignore(10000, '\n');
			}
			cout << "The option you selected is invalid. Please try again." << endl;
			cout << "Please select an option (1-4): ";
			cin >> option;
		}

		cin.ignore(10000, '\n');

		switch (option)
		{
		case 1:
			input();
			break;
		case 2:
			printRecent();
			break;
		case 3:
			printHistory();
			break;
		case 4:
			cout << "You selected option 4. Goodbye!" << endl;
			return;
		}
	}
}