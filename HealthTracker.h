#pragma once
#include <string>
#include "HealthData.h"
using namespace std;

class HealthTracker
{
private:
	string name;
	string gender;
	int age;
	int size;
	HealthData* history;
	int counter;
public:
	// Constructor
	HealthTracker(string name, string gender, int age, int size);

	// Destructor
	~HealthTracker();

	// Public methods
	void input();
	void printHistory();
	void printRecent();
	void menu();
};

