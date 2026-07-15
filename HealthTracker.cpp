#include "HealthTracker.h"
#include "HealthData.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

HealthTracker::HealthTracker(string name, string gender, int age)
{
	this->name = name;
	this->gender = gender;
	this->age = age;
	this->counter = 0;
}

HealthTracker::~HealthTracker()
{
	this->history.clear();
}

int getLineCount(ifstream& temp)
{
	string line;

	// Ignore first line (file header)
	getline(temp, line);

	// Keep track of # of lines in file
	int lineCount = 0;

	// Keep reading until end of file
	while (!temp.eof())
	{
		getline(temp, line);

		// Make sure line actually contains an entry 
		if (line.length() > 0)
		{
			lineCount++;
		}
	}

	// Done using file
	temp.close();

	return lineCount;
}

string trimTrailingWhitespace(string& str)
{
	int startIndex = 0;
	int endIndex = 0;

	// Loop through string from front to back
	// Get index of first non-whitespace character
	for (int i = 0; i < str.length(); i++)
	{
		if (!isspace(str[i]))
		{
			startIndex = i;
			break;
		}
	}

	// Loop through string from back to front
	// Get index of first non-whitespace character
	for (int i = str.length() - 1; i > 0; i--)
	{
		if (!isspace(str[i]))
		{
			endIndex = i;
			break;
		}
	}

	// The trimmed string is created from start index of first non-whitespace char & end index of first non-whitespace character (inclusive)
	string trimmed = str.substr(startIndex, (endIndex - startIndex + 1));

	return trimmed;
}

void HealthTracker::input()
{
	double weight, exerciseTime;
	string exerciseType;

	HealthData data;

	cout << "You selected option 1." << endl << endl;

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

	// Push HealthData object to the end of the vector
	this->history.push_back(data);

	// Write data to <name>.txt
	ofstream output(this->name + ".txt", ios::app);
	output << left << setw(30) << data.getExerciseType() << right << fixed << setprecision(2) << setw(30) << data.getExerciseTime() << setw(30) << data.getWeight() << endl;
	output.close();

	cout << endl << "Weight and exercise information logged successfully!";

	this->counter++;
}

void HealthTracker::printHistory()
{
	cout << "You selected option 3." << endl;

	cout << endl << "Name: " << this->name << endl;
	cout << "Gender: " << this->gender << endl;
	cout << "Age: " << this->age << endl;

	string line;

	// Open temporary input stream to see how many lines are in the file
	ifstream temp;
	temp.open(this->name + ".txt");

	if (getLineCount(temp) == 0) // User has not input any fitness data yet
	{
		cout << endl << "There are no fitness data inputs to display yet." << endl;
	}
	else
	{
		// Read file with filename <name>.txt
		ifstream input;
		input.open(this->name + ".txt");

		// Ignore first line (file header)
		getline(input, line);

		vector<HealthData> entriesFromFile;

		// Now read each following line
		while (!input.eof())
		{
			getline(input, line);

			if (line.length() > 0)
			{
				// Keep track of start/end indices for exercise type, exercise time, and weight
				int exerciseTypeStart = 0;
				int exerciseTypeEnd = 0;
				int exerciseTimeStart = 0;
				int exerciseTimeEnd = 0;
				int weightStart = 0;
				int weightEnd = line.length();

				// Find end index of exercise type
				for (int i = 0; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						exerciseTypeEnd = i;
						break;
					}
				}

				// Find starting index of exercise time value
				for (int i = exerciseTypeEnd; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						exerciseTimeStart = i;
						break;
					}
				}

				// Find end index of exercise time value
				for (int i = exerciseTimeStart; i < line.length(); i++)
				{
					if (isspace(line[i]))
					{
						exerciseTimeEnd = i;
						break;
					}
				}

				// Find starting index of weight value
				for (int i = exerciseTimeEnd; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						weightStart = i;
						break;
					}
				}

				string exerciseType = line.substr(0, exerciseTypeEnd);
				exerciseType = trimTrailingWhitespace(exerciseType); // Trim any whitespace after the exercise type

				// Convert to double
				double weight = stod(line.substr(weightStart, line.length() - weightStart));
				double exerciseTime = stod(line.substr(exerciseTimeStart, exerciseTimeEnd - exerciseTimeStart));

				// Create HealthData object from the entry we just read from the file
				HealthData data(weight, exerciseType, exerciseTime);

				// Push the entry we just read to the end of the vector
				entriesFromFile.push_back(data);
			}
		}

		cout << endl << "History of inputs from most recent to oldest (displaying the last " << entriesFromFile.size() << " entries):" << endl << endl;

		// Table header
		cout << left << setw(25) << "Weight (kg)" << setw(25) << "Exercise Type" << setw(25) << "Exercise Time (minutes)" << endl;

		// Iterate the vector in reverse, displaying entries from newest to oldest
		for (int i = entriesFromFile.size() - 1; i >= 0; i--)
		{
			cout << left << setw(25) << fixed << setprecision(2) << entriesFromFile.at(i).getWeight() << setw(25) << entriesFromFile.at(i).getExerciseType() << setw(25) << entriesFromFile.at(i).getExerciseTime() << endl;
		}
	}
}

void HealthTracker::printRecent()
{
	cout << "You selected option 2." << endl;

	string line;

	// Open temporary input stream to see how many lines are in the file
	ifstream temp;
	temp.open(this->name + ".txt");

	string exerciseType;
	double weight = 0;
	double exerciseTime = 0;

	if (getLineCount(temp) == 0)
	{
		cout << endl << "No fitness data to display." << endl;
	}
	else
	{
		// Read file with filename <name>.txt
		ifstream input;
		input.open(this->name + ".txt");

		// Ignore first line (file header)
		getline(input, line);

		// Now read each following line
		while (!input.eof())
		{
			getline(input, line);

			if (line.length() > 0)
			{
				// Keep track of start/end indices for exercise type, exercise time, and weight
				int exerciseTypeStart = 0;
				int exerciseTypeEnd = 0;
				int exerciseTimeStart = 0;
				int exerciseTimeEnd = 0;
				int weightStart = 0;
				int weightEnd = line.length();

				// Find end index of exercise type
				for (int i = 0; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						exerciseTypeEnd = i;
						break;
					}
				}

				// Find starting index of exercise time value
				for (int i = exerciseTypeEnd; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						exerciseTimeStart = i;
						break;
					}
				}

				// Find end index of exercise time value
				for (int i = exerciseTimeStart; i < line.length(); i++)
				{
					if (isspace(line[i]))
					{
						exerciseTimeEnd = i;
						break;
					}
				}

				// Find starting index of weight value
				for (int i = exerciseTimeEnd; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						weightStart = i;
						break;
					}
				}

				exerciseType = line.substr(0, exerciseTypeEnd);
				exerciseType = trimTrailingWhitespace(exerciseType);

				// Convert to double
				weight = stod(line.substr(weightStart, line.length() - weightStart));
				exerciseTime = stod(line.substr(exerciseTimeStart, exerciseTimeEnd - exerciseTimeStart));
			}
		}

		cout << endl;
		cout << this->name << " (" << this->gender << ", " << this->age << ")" << endl;
		cout << "Weight: " << weight << " kg" << endl;
		cout << "Exercise: " << exerciseType << " (" << exerciseTime << " minutes)" << endl;
	}

}

void HealthTracker::printSummaryReport()
{
	cout << "You selected option 4." << endl;

	string line;

	// Open temporary input stream to see how many lines are in the file
	ifstream temp;
	temp.open(this->name + ".txt");

	// First make sure the user has data we can summarize
	if (getLineCount(temp) == 0)
	{
		cout << endl << "No fitness data to summarize." << endl;
	}
	else
	{
		// Flag to use to check if min/max values have been set
		bool minMaxValuesSet = false;

		// Initialize min/max values to 0, but these will be re-assigned values when the first entry is read
		double minWeight = 0;
		double maxWeight = 0;
		double minExerciseTime = 0;
		double maxExerciseTime = 0;

		// Read file with filename <name>.txt
		ifstream input;
		input.open(name + ".txt");

		// Ignore first line (file header)
		getline(input, line);

		// Now read each following line
		while (!input.eof())
		{
			getline(input, line);

			if (line.length() > 0)
			{
				// Keep track of start/end indices for exercise time and weight
				int exerciseTimeStart = 0;
				int exerciseTimeEnd = 0;
				int weightStart = 0;
				int weightEnd = line.length();

				// Find starting index of exercise time value
				for (int i = 0; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						exerciseTimeStart = i;
						break;
					}
				}

				// Find end index of exercise time value
				for (int i = exerciseTimeStart; i < line.length(); i++)
				{
					if (isspace(line[i]))
					{
						exerciseTimeEnd = i;
						break;
					}
				}

				// Find starting index of weight value
				for (int i = exerciseTimeEnd; i < line.length(); i++)
				{
					if (isdigit(line[i]))
					{
						weightStart = i;
						break;
					}
				}

				// Convert to double
				double weight = stod(line.substr(weightStart, weightEnd - weightStart));
				double exerciseTime = stod(line.substr(exerciseTimeStart, exerciseTimeEnd - exerciseTimeStart));

				if (!minMaxValuesSet)
				{
					// Assume that the first weight is the min and max value
					// Assume that the first exercise time is the min and max value
					// We can then compare the rest of the entries with these initial values
					minWeight = weight;
					maxWeight = weight;
					minExerciseTime = exerciseTime;
					maxExerciseTime = exerciseTime;

					// Set flag to true
					minMaxValuesSet = true;
				}
				else {
					// Check if current weight is a min/max value
					if (weight < minWeight)
					{
						minWeight = weight;
					}
					else if (weight > maxWeight)
					{
						maxWeight = weight;
					}

					// Check if current exercise time is a min/max value
					if (exerciseTime < minExerciseTime)
					{
						minExerciseTime = exerciseTime;
					}
					else if (exerciseTime > maxExerciseTime)
					{
						maxExerciseTime = exerciseTime;
					}
				}
			}
		}

		// Display summary report
		cout << endl;
		cout << "Your fitness summary report is below!" << endl << endl;
		cout << left << setw(25) << " " << setw(20) << "Min" << setw(20) << "Max" << endl;
		cout << setw(25) << "Weight (kg)" << setw(20) << fixed << setprecision(2) << minWeight << setw(20) << maxWeight << endl;
		cout << setw(25) << "Exercise Time (minutes)" << setw(20) << minExerciseTime << setw(20) << maxExerciseTime << endl;

		input.close();
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
		cout << setw(5) << "- " << "Option 4: Display a summary report;" << endl;
		cout << setw(5) << "- " << "Option 5: Exit the program." << endl;
		cout << "--------------------------------------" << endl;

		// Get user's option choice
		cout << endl << "Please select an option (1-5): ";
		cin >> option;

		// If user provides a non-integer value
		// or an option that is not present in the menu,
		// keep asking user for a valid value until it is provided
		while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5)
		{
			if (cin.fail())
			{
				cin.clear(); // Only clear error state if user provides non-integer input
				cin.ignore(10000, '\n');
			}
			cout << "The option you selected is invalid. Please try again." << endl;
			cout << "Please select an option (1-5): ";
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
			printSummaryReport();
			break;
		case 5:
			cout << "You selected option 5. Goodbye!" << endl;
			return;
		}
	}
}