/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:ProductionWorker Class Implementation
*/

//User Libraries
#include "ProductionWorker.h"

ProductionWorker::ProductionWorker(string name, int num, int hDate, int shift, float payRate)
	: Employee(name, num, hDate)
{
	this->shift = shift;
	this->payRate = payRate;
}

int ProductionWorker::getShift() const
{
	return shift;
}

float ProductionWorker::getPayRate() const
{
	return payRate;
}

void ProductionWorker::setShift(int shift)
{
	this->shift = shift;
}

void ProductionWorker::setPayRate(float payRate)
{
	this->payRate = payRate;
}
