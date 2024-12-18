#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP
#include "head.hpp"

class Restaurant
{
public:
    Restaurant(string name, string district, map<string, int> foods, int opening_time, int closing_time, int table_no);


    string name;
    string district;
    int opening_time;
    int closing_time;
    int table_no;
    map<string, int> foods;
};
#endif