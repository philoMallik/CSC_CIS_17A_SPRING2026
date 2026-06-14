/*
Author: Philopatair Mallik
Date: 06/07/2026
purpose: Gaddis_9ThE_Ch15_P4 MillTime Class Implementation
*/

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
#include "MillTime.h"

// Accept military time and initialize both military and standard fields.
MillTime::MillTime(int milHr, int milSec)
{
	setTime(milHr, milSec);
}

// Returns military time as HHMM.
int MillTime::getHr() const
{
	return milHr;
}

// Returns standard-format hour (1-12) stored by the base class.
int MillTime::getStandHr() const
{
	return hr;
}

void MillTime::setTime(int milHr, int milSec)
{
	// Validate military seconds.
	if (milSec < 0 || milSec > 59){
        string errorMsg = "ERROR: Invalid military seconds. \n";
		throw errorMsg;
	}

	// Validate HHMM range.
	if (milHr < 0 || milHr > 2359){
        string errorMsg = "ERROR: Invalid military time. \n";
		throw errorMsg;
	}

	int militaryHour = milHr / 100;
	int militaryMin = milHr % 100;

	this->milHr = milHr;
	this->milSec = milSec;

	// Convert to standard time (1-12 hour format).
	if (militaryHour == 0){
		amPm = 'A';
		hr = 12;
	}
	else if (militaryHour > 12){
		amPm = 'P';
		hr = militaryHour - 12;
	}
	else{
		if (militaryHour == 12) amPm = 'P';
		else amPm = 'A';

		hr = militaryHour;
	}

	min = militaryMin;
	sec = milSec;
}

void MillTime::dsplymil() const
{
    cout<< (milHr < 1000 ? "0" : "") << milHr << ":"
        << (milSec < 10 ? "0" : "") << milSec << endl;
}