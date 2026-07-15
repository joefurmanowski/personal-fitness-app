#include "HealthData.h"
#include <iostream>
#include <string>
using namespace std;

HealthData::HealthData()
{
	this->weight = 0;
	this->exerciseType = "";
	this->exerciseTime = 0;
}

HealthData::HealthData(double weight, string exerciseType, double exerciseTime)
{
	this->weight = weight;
	this->exerciseType = exerciseType;
	this->exerciseTime = exerciseTime;
}

void HealthData::setWeight(double weight)
{
	this->weight = weight;
}

void HealthData::setExerciseType(string exerciseType)
{
	this->exerciseType = exerciseType;
}

void HealthData::setExerciseTime(double exerciseTime)
{
	this->exerciseTime = exerciseTime;
}

double HealthData::getWeight()
{
	return this->weight;
}

string HealthData::getExerciseType()
{
	return this->exerciseType;
}

double HealthData::getExerciseTime()
{
	return this->exerciseTime;
}

void HealthData::print()
{
	cout << endl;
	cout << "Weight: " << weight << " kg" << endl;
	cout << "Exercise: " << exerciseType << " (" << exerciseTime << " minutes)" << endl;
}