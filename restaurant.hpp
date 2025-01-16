#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP
#include "head.hpp"
#include "reserves.hpp"
#include "discount.hpp"
#include "item_specific_discount.hpp"
#include "total_discount.hpp"
class UTaste;
class Restaurant
{
public:
    Restaurant(string name, string district, map<string, int> foods_, int opening_time, int closing_time, int table_no, Discount &first_discount_,
               TotalDiscount &total_discount_,
               vector<ItemSpecificDiscount> &food_discounts_, UTaste &utaste_ref);
    bool checkConflict(string *&end_time_ptr, string *&start_time_ptr, string *&table_id_ptr);
    bool checkUserConflict(string &owner, string *&start_time_ptr, string *&end_time_ptr);
    bool workingHoursRange(string *&start_time_ptr, string *&end_time_ptr);
    bool checkFoodsTables(string *&foods_ptr, string *&table_id_ptr);
    bool hasMoney(int &original_price, int &final_diss, int &user_balance);
    int calc_first_dis(int temp_price);
    void calc_first_dis2(string &name, int &cnt);
    int calc_food_dis(vector<string> &reserved_foods);
    int calc_total_dis(int temp_price);
    void handleReserve(string &owner, string *&table_id_ptr, string *&start_time_ptr, string *&end_time_ptr, string *&foods_ptr);
    Temp printReserveMessage(int &user_balance);
    void printAllFoods();
    void printAllTables();
    void showRestaurant(bool food_flag, int &restaurant_num);
    int deleteReserve(string &owner, string *&reserve_id_ptr);
    bool isFoodInMenu(string *&food_ptr);
    int getReserves() { return reserves.size(); };
    void setLastReserveExpense(pair<int, int> &expense);
    void getUserReservesAll(string &owner, int &reserves_num, vector<pair<Reserve, string>> &all_user_reserves);
    void getUserReservesR(string &owner, string &test);
    void getUserReservesRI(string &owner, string *&reserve_id_ptr, string &test);
    string getDistrict() { return district; };
    void getRestaurantDetail();
    int getTableNo() { return table_no; };
    void delLastReserve() { reserves.pop_back(); }
    string getName() { return name; };
    void printing();

protected:
    string name;
    string district;
    int opening_time;
    int closing_time;
    int table_no;
    Discount first_discount;
    TotalDiscount total_discount;
    vector<ItemSpecificDiscount> food_discounts;
    map<string, int> foods;
    vector<Reserve> reserves;
    UTaste *utaste;
};
#endif
