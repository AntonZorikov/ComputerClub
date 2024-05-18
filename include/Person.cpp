#include "../headers/Person.h"

using namespace std;

bool Person::operator<(const Person& other) const {
        return name < other.name;
}

Person::Person() {

};

Person::Person(string name_) {
    this->name = name_;
}

Person::
Person(string name_, unsigned int table_, Time tableTime_) {
    this->name = name_;
    this->table = table_;
    this->tableTime = tableTime_;
}


bool PersonComparator::operator()(const shared_ptr<Person>& a, const shared_ptr<Person>& b) const {
    return a->name < b->name;
}
