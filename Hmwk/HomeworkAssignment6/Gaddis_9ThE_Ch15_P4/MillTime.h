/*
Author: Philopatair Mallik
Date: 06/07/2026
purpose: Gaddis_9ThE_Ch15_P4 MillTime Class Specification
*/

#ifndef MILLTIME_H
#define MILLTIME_H

#include "Time.h"

class MillTime : public Time
{
    private:
        int milHr;  // for digit military hour (0000-2359)
        int milSec; // Military second (0-59)
    public:
        //Constructors
        MillTime(int milHr, int milSec);    //Accept time in military format and convert to standard time

        //Accessors
        int getHr() const;          //Returns the hour in military format
        int getStandHr() const;     //Returns the hour in standard format

        //Mutators
        void setTime(int milHr, int milSec);    //Accept time in military format and convert to standard time

        //display time in standard format (HH:MM:SS AM/PM)
        void dsplymil() const;
};

#endif /* MILLTIME_H */