#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "head.hpp"
#include "restaurant.hpp"

class Command
{
public:
    Command(string districts_path, string restaurants_path, string discounts_path);
    void readDistricts(string districs_path);
    void readRestaurants(string restaurants_path, string discounts_path);
    void readDiscounts(Discount &first_dis, TotalDiscount &total_dis, vector<ItemSpecificDiscount> &food_dis, string discounts_path, string &restaurant_name);
    void setNewUser(pair<USERNAME, USER_DATA> &new_user);
    void setLogin(string username);
    void setLogout(string username);
    void setUserDistrict(string *districti_ptr, string username);
    void setReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                    string *&end_time_ptr,
                    string *&foods_ptr);
    bool is_logged_in()
    {
        for (auto user : users)
        {
            if (user.second.is_logged_in == true)
            {
                return true;
            }
        }
        return false;
    }
    int deleteReserve(vector<string> &command_words);
    bool checkRestaurantTimeConflic(Restaurant &restaurant, string *&start_time_ptr, string *&end_time_ptr, string *&table_id_ptr);
    bool checkUserTimeConflict(string *&start_time_ptr, string *&end_time_ptr);
    bool checkWorkingHoursRange(Restaurant &restaurant, string *&start_time_ptr, string *&end_time_ptr);
    bool checkFoodsTables(Restaurant &restaurant, string *&foods_ptr, string *&table_id_ptr);
    void handleReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr, string *&end_time_ptr, string *&foods_ptr);
    bool hasPermission(string username);
    virtual void checkCommand(vector<string> command_words) = 0;
    void setLastReserveExpense(string *&restaurant_name_ptr, pair<int, int> &expense);
    pair<int, int> printReserveMessage(string *&restaurant_name_ptr);
    int getReserveNum()
    {
        int num = 0;
        for (auto r : restaurants)
        {
            num += r.getReserves();
        }
        return num;
    };
    string getuserdis(string username) { return users[username].user_district; };
    void printing();
    void setBudget(int &amount);
    void getBudget()
    {
        for (auto user : users)
        {
            if (user.second.is_logged_in == true)
            {
                cout << user.second.user_balance << endl;
            }
        }
    }
    void decreaseBudget(int &expense)
    {
        for (auto &user : users)
        {
            if (user.second.is_logged_in == true)
            {
                user.second.user_balance -= expense;
            }
        }
    }

protected:
    USERS users;
    DISTRICTS districts;
    vector<Restaurant> restaurants;
};
#endif