#include "../headers/club.h"

using namespace std;

void Club::run() {
    string line;
    ifstream in(fileName);
    if (in.is_open())
    {
        string str;
        getline(in, str);
        tableNum = std::atoi(str.c_str());
        if (tableNum <= 0) {
            cout << str;
            return;
        }

        getline(in, str);
        try {
            size_t pos = str.find(' ');
            if (pos == std::string::npos) {
                throw invalid_argument("invalid data");
            }
            openTime = Time::stringToTime(str.substr(0, pos));

            closeTime = Time::stringToTime(str.substr(pos + 1, str.size()));

        }
        catch (...) {
            cout << str;
            return;
        }

        getline(in, str);
        cost = std::atoi(str.c_str());
        if (cost <= 0) {
            cout << str;
            return;
        }

        while (std::getline(in, str)) {
            try {
                Event event = Event::stringToEvent(str, tableNum);
                events.push_back(event);
            }
            catch (...) {
                cout << str;
                return;
            }
        }
    }
    in.close();

    cout << Time::timeToString(openTime) << endl;

    for (Event& event_ : events) {
        cout << Event::eventToString(event_) << endl;
        if (event_.id == 1) {
            eventType1(event_);
        }
        if (event_.id == 2) {
            eventType2(event_);
        }
        if (event_.id == 3) {
            eventType3(event_);
        }
        if (event_.id == 4) {
            eventType4(event_);
        }
    }

    for (auto it = clients.begin(); it != clients.end(); ++it) {
        shared_ptr<Person> person_ = *it;
        eventType11(person_.get()->name, closeTime);
    }

    cout << Time::timeToString(closeTime) << endl;

    for (unsigned int i = 1; i <= tableNum; i++) {
        cout << i << " " << get<1>(tableInfo[i]) * cost << " " << Time::timeToString(get<0>(tableInfo[i])) << endl;
    }
}

void Club::eventType1(Event& event_) {
    set<Person>::iterator it;
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        shared_ptr<Person> personPtr = *it;
        Person& person = *personPtr;
        if (event_.name == person.name) {
            cout << Time::timeToString(event_.eventTime) << " 13 " << "YouShallNotPass" << endl;
            return;
        }
    }
    if (event_.eventTime < openTime || event_.eventTime > closeTime) {
        cout << Time::timeToString(event_.eventTime) << " 13 " << "NotOpenYet" << endl;
        return;
    }
    Person p(event_.name);
    clients.insert(make_shared<Person>(p));
}

void Club::eventType2(Event& event_) {
    Person* person = new Person();
    bool find = false;
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        shared_ptr<Person> personPtr = *it;
        Person& person_ = *personPtr;
        if (tables.find(event_.table) != tables.cend()) {
            cout << Time::timeToString(event_.eventTime) << " 13 " << "PlaceIsBusy" << endl;
            return;
        }
        if (event_.name == person_.name) {
            delete person;
            person = &person_;
            find = true;
        }
    }

    if (!find) {
        cout << Time::timeToString(event_.eventTime) << " 13 " << "ClientUnknown" << endl;
        delete person;
        return;
    }

    if (person->table > 0) {
        cout << person->table << endl;
        Time t = event_.eventTime.subtract(person->sitTime);
        get<0>(tableInfo[person->table]) = get<0>(tableInfo[person->table]).add(t);
        get<1>(tableInfo[person->table]) += t.hour + (t.minute > 0 ? 1 : 0);
    }

    tables.erase(person->table);
    person->table = event_.table;
    person->sitTime = event_.eventTime;
    tables.insert(event_.table);
}

void Club::eventType11(const string& name, const Time& time) {
    cout << Time::timeToString(time) << " 11 " << name << endl;

    auto iter = clients.begin();
    shared_ptr<Person> person = nullptr;
    for (iter = clients.begin(); iter != clients.end(); ++iter) {
        if (name == (*iter)->name) {
            person = *iter;
            break;
        }
    }

    Time t = time.subtract(person.get()->sitTime);
    auto& tupleElement1 = get<0>(tableInfo[person->table]);
    tupleElement1 = tupleElement1.add(t);

    auto& tupleElement2 = get<1>(tableInfo[person->table]);
    tupleElement2 += t.hour + (t.minute > 0 ? 1 : 0);
}

void Club::eventType3(Event& event_) {
    if (tables.size() < tableNum) {
        cout << Time::timeToString(event_.eventTime) << " 13 " << "ICanWaitNoLonger!" << endl;
    }
    else if (queue.size() > tableNum) {
        eventType11(event_.name, event_.eventTime);
    }
    else {
        set<Person>::iterator it;
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            shared_ptr<Person> personPtr = *it;
            Person& person_ = *personPtr;
            if (event_.name == person_.name) {
                queue.push_back(make_shared<Person>(person_));
            }
        }
    }
}

void Club::eventType12(const Time& time) {
    set<unsigned int>::iterator it;
    unsigned int last = 1;
    if (queue.size() == 0) {
        return;
    }

    if (tables.size() == 0) {
        queue.front()->table = tableNum;
        cout << Time::timeToString(time) << " 12 " << queue.front()->name << " " << tableNum << endl;
        queue.pop_front();
        return;
    }
    for (auto it = tables.begin(); it != tables.end(); ++it) {
        unsigned int num = *it;
        if (last - num > 1) {
            shared_ptr<Person> personPtr = queue.front();

            shared_ptr<Person> person_ = nullptr;
            for (auto iter = clients.begin(); iter != clients.end(); ++iter) {
                if (personPtr.get()->name == (*iter)->name) {
                    person_ = *iter;
                    break;
                }
            }

            cout << Time::timeToString(time) << " 12 " << person_.get()->name << " " << num - 1 << endl;

            tables.erase(person_.get()->table);
            person_.get()->table = num - 1;
            person_.get()->sitTime = time;
            tables.insert(num - 1);

            queue.pop_front();
            return;
        }
    }
}

void Club::eventType4(Event& event_) {
    auto iter = clients.begin();
    auto it = clients.begin();
    shared_ptr<Person> person = nullptr;
    for (iter = clients.begin(); iter != clients.end(); ++iter) {
        if (event_.name == (*iter)->name) {
            it = iter;
            person = *iter;
            break;
        }
    }

    if (it == clients.end()) {
        cout << Time::timeToString(event_.eventTime) << " 13 " << "ClientUnknown" << endl;
        return;
    }

    Time t = event_.eventTime.subtract(person.get()->sitTime);
    get<0>(tableInfo[person->table]) = get<0>(tableInfo[person->table]).add(t);
    get<1>(tableInfo[person->table]) += t.hour + (t.minute > 0 ? 1 : 0);

    tables.erase(person->table);
    clients.erase(it);
    eventType12(event_.eventTime);
}

Club::Club(string fileName_) {
    this->fileName = fileName_;
}