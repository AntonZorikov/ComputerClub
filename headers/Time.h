#ifndef TIME_H
#define TIME_H

#include <string>
#include <stdexcept>

using namespace std;

class Time {
public:
    unsigned short hour = 0;
    unsigned short minute = 0;

    static bool isValidTime(const string& time);

    static Time stringToTime(const string& time);

    static string timeToString(const Time& time);

    Time add(const Time& other) const;

    Time subtract(const Time& other) const;

    bool operator==(const Time& other) const;

    bool operator<(const Time& other) const;

    bool operator>(const Time& other) const;

    Time(unsigned short hour_, unsigned minute_);

    Time();
};

#endif 
