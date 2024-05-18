#ifndef EVENT_H
#define EVENT_H

#include "time.h"

using namespace std;

class Event {
public:
    Time eventTime = Time();
    unsigned short id = 0;
    string name = "";
    unsigned int table = 0;

    static Event stringToEvent(const std::string& line, unsigned int tableNum);

    static string eventToString(const Event& event_);

    Event(Time time_, unsigned short id_, string name_);

    Event(Time time_, unsigned short id_, string name_, unsigned int table_);
};

#endif 
