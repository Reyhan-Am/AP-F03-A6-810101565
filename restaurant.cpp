#include "restaurant.hpp"
Restaurant::Restaurant(string name_, string district_, map<string, int> foods_, int opening_time_, int closing_time_, int table_no_)
{
    name = name_;
    district = district_;
    foods = foods_;
    opening_time = opening_time_;
    closing_time = closing_time_;
    table_no = table_no_;
}