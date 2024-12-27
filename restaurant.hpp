#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP
#include "head.hpp"
#include "reserves.hpp"
class Restaurant
{
public:
    Restaurant(string name, string district, map<string, int> foods_, int opening_time, int closing_time, int table_no);
    bool checkConflict(string *&end_time_ptr, string *&start_time_ptr, string *&table_id_ptr);
    bool checkUserConflict(string &owner, string *&start_time_ptr, string *&end_time_ptr);
    bool workingHoursRange(string *&start_time_ptr, string *&end_time_ptr);
    bool checkFoodsTables(string *&foods_ptr, string *&table_id_ptr);
    void handleReserve(string &owner, string *&table_id_ptr, string *&start_time_ptr, string *&end_time_ptr, string *&foods_ptr);
    void printReserveMessage();
    void printAllFoods();
    void printAllTables();
    void showRestaurant(bool food_flag, int &restaurant_num);
    void deleteReserve(string &owner, string *&reserve_id_ptr);
    bool isFoodInMenu(string *&food_ptr);
    int getReserves() { return reserves.size(); };
    void getUserReservesAll(string &owner, int &reserves_num, vector<pair<Reserve, string>> &all_user_reserves);
    void getUserReservesR(string &owner);
    void getUserReservesRI(string &owner, string *&reserve_id_ptr);
    string getDistrict() { return district; };
    void getRestaurantDetail();
    int getTableNo() { return table_no; };
    string getName() { return name; };

protected:
    string name;
    string district;
    int opening_time;
    int closing_time;
    int table_no;
    map<string, int> foods;
    vector<Reserve> reserves;
};
#endif