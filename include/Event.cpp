#include "../headers/event.h"

using namespace std;

Event Event::stringToEvent(const std::string& line, unsigned int tableNum) {
    size_t pos1 = line.find(' ');
    if (pos1 == std::string::npos) {
        throw invalid_argument("invalid data");
    }
    Time time = Time::stringToTime(line.substr(0, pos1));

    size_t pos2 = line.find(' ', pos1 + 1);
    if (pos2 == std::string::npos) {
        throw invalid_argument("invalid data");
    }

    int id = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
    if (id < 1 || id > 4) {
        throw invalid_argument("invalid id");
    }

    if (id == 2) {
        size_t pos3 = line.find(' ', pos2 + 1);

        if (pos3 == std::string::npos) {
            throw invalid_argument("invalid data");
        }

        string clientName = line.substr(pos2 + 1, pos3 - pos2 - 1);

        int table = 0;

        table = std::stoi(line.substr(pos3 + 1));
        if (table < 1 || table > tableNum) {
            throw invalid_argument("invalid data");
        }
        return Event(time, id, clientName, table);
    }

    string clientName = line.substr(pos2 + 1, line.size());

    return Event(time, id, clientName);
}

string Event::Event::eventToString(const Event& event_) {
    return Time::timeToString(event_.eventTime) + " " + to_string(event_.id) + " " + event_.name + (event_.table > 0 ? " " + to_string(event_.table) : "");
}

Event::Event(Time time_, unsigned short id_, string name_) {
    this->eventTime = time_;
    this->id = id_;
    this->name = name_;
}

Event::Event(Time time_, unsigned short id_, string name_, unsigned int table_) {
    this->eventTime = time_;
    this->id = id_;
    this->name = name_;
    this->table = table_;
}

