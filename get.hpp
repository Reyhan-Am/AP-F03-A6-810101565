#ifndef GET_HPP
#define GET_HPP

#include "command.hpp"
#include "head.hpp"
#include <string>
class UTaste;

class Getter : public Command
{
public:
    Getter(string districts_path, string restaurants_path, string discounts_path, UTaste &utaste_ref);
    void getDistrict(vector<string> &command_words);
    void showBudget();
    void getDistricts(vector<string> &command_words);
    void getRestaurantDetail(vector<string> &command_words);
    void getRestaurants(vector<string> &command_words);
    void bfsOnDistricts(queue<string> &q, vector<string> &visited, string *&food_ptr, int &restaurant_num);
    void showRestaurants(string &district, string *&food_ptr, int &restaurant_num);
    void getUserReserves(vector<string> &command_words, string &test);
    void getUserReservesAll(string &owner, string &test);
    void getUserReservesR(string *&restaurant_name_ptr, string &owner, string &test);
    void getUserReservesRI(string *&restaurant_name_ptr, string *&reserve_id_ptr, string &owner, string &test);
    virtual void checkCommand(vector<string> command_words, string &test);

private:
    UTaste *utaste;
};

#endif
