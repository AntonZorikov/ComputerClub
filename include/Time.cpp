#include "../headers/Time.h"

bool Time::isValidTime(const string& time) {
    if (time.size() != 5) {
        return false;
    }

    if (time[2] != ':') {
        return false;
    }

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        return false;
    }

    return true;
}

Time Time::stringToTime(const string& time) {
    if (!isValidTime(time)) {
        throw invalid_argument("invalid time");
    }

    unsigned short hours = (time[0] - '0') * 10 + (time[1] - '0');
    unsigned short  minutes = (time[3] - '0') * 10 + (time[4] - '0');

    return Time(hours, minutes);
}

string Time::timeToString(const Time& time) {
    return (time.hour > 9 ? to_string(time.hour) : "0" + to_string(time.hour)) + ":" + (time.minute > 9 ? to_string(time.minute) : "0" + to_string(time.minute));
}

Time Time::add(const Time& other) const {
    unsigned short totalMinutes = minute + other.minute;
    unsigned short carry = totalMinutes / 60;
    unsigned short newMinute = totalMinutes % 60;
    unsigned short newHour = (hour + other.hour + carry) % 24;
    return Time(newHour, newMinute);
}

Time Time::subtract(const Time& other) const {
    int totalMinutes = (hour * 60 + minute) - (other.hour * 60 + other.minute);
    if (totalMinutes < 0) {
        totalMinutes += 24 * 60;
    }
    unsigned short newHour = totalMinutes / 60;
    unsigned short newMinute = totalMinutes % 60;
    return Time(newHour, newMinute);
}

bool Time::operator==(const Time& other) const {
    return hour == other.hour && minute == other.minute;
}

bool Time::operator<(const Time& other) const {
    if (hour < other.hour) {
        return true;
    }
    else if (minute < other.minute) {
        return true;
    }
    else {
        return false;
    }
}

bool Time::operator>(const Time& other) const {
    if (hour < other.hour) {
        return false;
    }
    else if (minute <= other.minute) {
        return false;
    }
    else {
        return true;
    }
}

Time::Time(unsigned short hour_, unsigned minute_) {
    this->hour = hour_;
    this->minute = minute_;
}

Time::Time() {

}