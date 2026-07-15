#pragma once
#include <string>
using namespace std;

class HealthData
{
private:
	double weight;
	string exerciseType;
	double exerciseTime;
public:
	// Constructors
	HealthData();
	HealthData(double weight, string exerciseType, double exerciseTime);

	// Setter methods
	void setWeight(double weight);
	void setExerciseType(string exerciseType);
	void setExerciseTime(double exerciseTime);

	// Getter methods
	double getWeight();
	string getExerciseType();
	double getExerciseTime();

	// Print method
	void print();
};

