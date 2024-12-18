#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "head.hpp"
#include "restaurant.hpp"

class Command
{
public:
    Command(string districts_path, string restaurants_path);
    void readDistricts(string districs_path);
    void readRestaurants(string restaurants_path);
    void printing();

protected:
    USERS users;
    DISTRICTS districts;
    vector<Restaurant> restaurants;
};
#endif