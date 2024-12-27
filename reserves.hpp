#ifndef RESERVES_HPP
#define RESERVES_HPP

#include "head.hpp"

class Reserve
{
public:
    Reserve(string owner_, vector<string> food_, pair<int, int> times_, int id_, int table_num_);
    pair<int, int> getTimes() { return times; };
    string getOwner() { return owner; };
    string getTableNum() { return to_string(table_num); };
    vector<string> getFoods() { return food; };
    void printReserveMessage(string &restaurant_name, int price);
    void printUserReservesRI(string &restaurant_name);
    int getID() { return id; };

private:
    string owner;
    vector<string> food;
    pair<int, int> times;
    int id;
    int table_num;
};

#endif