#pragma once
#include <string>
#include "HealthData.h"
#include <vector>
using namespace std;

class HealthTracker
{
private:
	string name;
	string gender;
	int age;
	vector<HealthData> history;
	int counter;
public:
	// Constructor
	HealthTracker(string name, string gender, int age);

	// Destructor
	~HealthTracker();

	// Public methods
	void input();
	void printHistory();
	void printRecent();
	void printSummaryReport();
	void menu();
};

