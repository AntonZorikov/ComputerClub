#ifndef CLUB_H
#define CLUB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <unordered_map>
#include "time.h"
#include "event.h"
#include "person.h"

class Club {
public:
    std::string fileName;
    int tableNum = 0, cost = 0;
    Time openTime, closeTime;
    std::vector<Event> events;
    std::set<std::shared_ptr<Person>, PersonComparator> clients;
    std::set<unsigned int> tables;
    std::list<std::shared_ptr<Person>> queue;
    std::unordered_map<unsigned int, std::tuple<Time, unsigned int>> tableInfo;

    void run();
    void eventType1(Event& event_);
    void eventType2(Event& event_);
    void eventType11(const std::string& name, const Time& time);
    void eventType3(Event& event_);
    void eventType12(const Time& time);
    void eventType4(Event& event_);

    Club(std::string fileName_);
};

#endif 
