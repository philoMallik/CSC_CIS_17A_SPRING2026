#ifndef DATE_H
#define DATE_H

class Date
{  
    private:
        int month;
        int day;
        int year;
    public:
        Date(int m, int d, int y);
        void printNum() const;
        void printWrtn_DMY() const;
        void printWrtn_MDY() const;
};

#endif // DATE_H