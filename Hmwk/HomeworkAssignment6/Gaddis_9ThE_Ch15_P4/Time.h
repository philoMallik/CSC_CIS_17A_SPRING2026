/*
Author: Philopatair Mallik
Date: 06/07/2026
purpose: Gaddis_9ThE_Ch15_P4 Time Class Specification - copied from program 15.20 from the textbook
*/

#ifndef TIME_H
#define TIME_H

class Time
{
    protected:
        int hr;
        int min;
        int sec;
        char amPm; // 'A' for AM, 'P' for PM
    public:
        //Constructors
        Time();
        Time(int hr, int min, int sec, char amPm);

        //Accessors
        int getHr() const;
        int getMin() const;
        int getSec() const;
        char getAmPm() const;

        //display time in standard format (HH:MM:SS AM/PM)
        void dsplyStd() const;
};

#endif /* TIME_H */