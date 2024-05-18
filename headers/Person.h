#ifndef PERSON_H
#define PERSON_H

#include <memory>
#include "Time.h"

using namespace std;

class Person {
public:
    unsigned int table = 0;
    Time tableTime = Time();
    Time sitTime = Time();
    string name;

    bool operator<(const Person& other) const;

    Person();

    Person(string name_);

    Person(string name_, unsigned int table_, Time tableTime_);
};

struct PersonComparator {
    bool operator()(const shared_ptr<Person>& a, const shared_ptr<Person>& b) const;
};

#endif 
