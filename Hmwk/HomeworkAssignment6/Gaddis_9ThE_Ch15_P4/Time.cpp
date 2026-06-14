/*
Author: Philopatair Mallik
Date: 06/07/2026
purpose: Gaddis_9ThE_Ch15_P4 Time Class Implementation
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "Time.h"

// Default constructor initializes time to 00:00:00.
Time::Time(){
	hr = 0;
	min = 0;
	sec = 0;
}

// Overloaded constructor initializes time with provided values.
Time::Time(int hr, int min, int sec, char amPm){
	this->hr = hr;
	this->min = min;
	this->sec = sec;
	this->amPm = amPm;
}

int Time::getHr() const{
	return hr;
}

int Time::getMin() const{
	return min;
}

int Time::getSec() const{
	return sec;
}

char Time::getAmPm() const{
	return amPm;
}

void Time::dsplyStd() const{
    cout<< (hr < 10 ? "0" : "") << hr << ":"
        << (min < 10 ? "0" : "") << min << ":"
        << (sec < 10 ? "0" : "") << sec << " "
        << (amPm == 'A' ? "AM" : "PM") << endl;
}
