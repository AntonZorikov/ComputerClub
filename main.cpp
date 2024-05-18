#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <tuple>
#include <iostream>
#include <memory>

#include "Time.h"
#include "Event.h"
#include "Person.h"
#include "Club.h"

using namespace std;

int main()
{
    Club club("input.txt");
    club.fileName = "input.txt";
    club.run();
}
