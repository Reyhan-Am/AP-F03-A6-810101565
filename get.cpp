#include "get.hpp"
#include "Utaste.hpp"
Getter::Getter(string districts_path, string restaurants_path, string discounts_path, UTaste &utaste_ref) : Command(districts_path, restaurants_path, discounts_path, utaste_ref), utaste(&utaste_ref) {}
void Getter::checkCommand(vector<string> command_words, string &test)
{
    if (this->hasPermission("") == false)
    {
        throw Exception(PERMISSION);
    }
    if (command_words[1] == GET_DISTRICTS)
    {

        for (auto x : command_words)
        {
            if (x == "district")
            {
                this->getDistrict(command_words);
                return;
            }
        }
        this->getDistricts(command_words);
    }
    else if (command_words[1] == GET_RESTAURANT)
    {
        this->getRestaurantDetail(command_words);
    }
    else if (command_words[1] == GET_RESTAURANTS)
    {
        this->getRestaurants(command_words);
    }
    else if (command_words[1] == RESERVES)
    {
        this->getUserReserves(command_words, test);
    }
    else if (command_words[1] == SHOW_BUDGET)
    {
        this->showBudget();
    }
    else
    {
        throw Exception(NOT_FOUND);
    }
}
bool is_bad_get_district_request(vector<string> &command_words, string *&district_ptr)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if ((*it == "district") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            district_ptr = &*(it + 1);
        }
    }
    if ((district_ptr == nullptr) or (*district_ptr == ""
                                                       ""))
    {
        return true;
    }
    return false;
}
bool is_bad_get_restaurant_request(vector<string> &command_words, string *&restaurant_name_ptr)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if ((*it == "restaurant_name") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            restaurant_name_ptr = &*(it + 1);
        }
    }
    if ((restaurant_name_ptr == nullptr) or (*restaurant_name_ptr == ""
                                                                     ""))
    {
        return true;
    }
    return false;
}
bool is_bad_get_user_reserves_request(vector<string> &command_words, string *&restaurant_name_ptr, string *&reserve_id_ptr)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if ((*it == "restaurant_name") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            restaurant_name_ptr = &*(it + 1);
        }
        if ((*it == "reserve_id") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            reserve_id_ptr = &*(it + 1);
        }
    }
    if (((restaurant_name_ptr == nullptr) or (*restaurant_name_ptr == ""
                                                                      "")) &&
        (reserve_id_ptr != nullptr))
    {
        return true;
    }
    return false;
}
bool is_bad_get_restaurants_request(vector<string> &command_words, string *&food_ptr)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if ((*it == "food_name"))
        {
            if ((it + 1 == command_words.end()) or (isStartWithComma(*(it + 1)) == false))
            {
                return true;
            }
            else
            {
                food_ptr = &*(it + 1);
                if ((*food_ptr == ""
                                  ""))
                {
                    throw Exception(BAD_REQ);
                }
            }
        }
    }
    return false;
}
bool isInQueue(queue<string> q, const string &target)
{
    while (!q.empty())
    {
        if (q.front() == target)
        {
            return true;
        }
        q.pop();
    }
    return false;
}
void Getter::getRestaurants(vector<string> &command_words)
{
    string *food_ptr = nullptr;
    string user_district = "";
    if (is_bad_get_restaurants_request(command_words, food_ptr) == true)
    {
        throw Exception(BAD_REQ);
    }
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            if (user.second.user_district == "")
            {
                throw Exception(NOT_FOUND);
            }
            else
            {
                user_district = user.second.user_district;
                break;
            }
        }
    }
    queue<string> q;
    vector<string> visited;
    int restaurant_num = 0;
    q.push(user_district);
    while (!q.empty())
    {
        this->bfsOnDistricts(q, visited, food_ptr, restaurant_num);
    }
    if (restaurant_num == 0)
    {
        throw Exception(EMPTY);
    }
}
void Getter::bfsOnDistricts(queue<string> &q, vector<string> &visited, string *&food_ptr, int &restaurant_num)
{
    this->showRestaurants(q.front(), food_ptr, restaurant_num);
    visited.push_back(q.front());
    vector<string> neighbors;
    for (auto district : districts)
    {
        if (district.first == q.front())
        {
            neighbors = district.second;
        }
    }
    for (auto neighbor : neighbors)
    {
        if ((find(visited.begin(), visited.end(), neighbor) == visited.end()) && (isInQueue(q, neighbor) == false))
        {
            q.push(neighbor);
        }
    }
    q.pop();
}
void Getter::showRestaurants(string &district, string *&food_ptr, int &restaurant_num)
{
    vector<string> temp_restaurants;
    for (auto restaurant : restaurants)
    {
        if (restaurant.getDistrict() == district)
        {
            if (food_ptr == nullptr)
            {
                temp_restaurants.push_back(restaurant.getName());
                restaurant_num++;
            }
            else
            {
                if (restaurant.isFoodInMenu(food_ptr) == true)
                {
                    temp_restaurants.push_back(restaurant.getName());
                    restaurant_num++;
                }
            }
        }
    }
    if (temp_restaurants.size() != 0)
    {
        sort(temp_restaurants.begin(), temp_restaurants.end(), [](string &a, string &b)
             { return a < b; });
        for (auto it = temp_restaurants.begin(); it != temp_restaurants.end(); it++)
        {
            cout << *it << " (" << district << ")" << endl;
        }
    }
}
void Getter::getUserReserves(vector<string> &command_words, string &test)
{
    string *restaurant_name_ptr = nullptr;
    string *reserve_id_ptr = nullptr;
    if (is_bad_get_user_reserves_request(command_words, restaurant_name_ptr, reserve_id_ptr) == true)
    {
        throw Exception(BAD_REQ);
    }
    string owner = "";
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            owner = user.first;
        }
    }
    if (restaurant_name_ptr == nullptr)
    {
        this->getUserReservesAll(owner, test);
    }
    else if ((restaurant_name_ptr != nullptr) && (reserve_id_ptr == nullptr))
    {
        this->getUserReservesR(restaurant_name_ptr, owner, test);
    }
    else if ((restaurant_name_ptr != nullptr) && (reserve_id_ptr != nullptr))
    {
        this->getUserReservesRI(restaurant_name_ptr, reserve_id_ptr, owner, test);
    }
}
void Getter::getUserReservesR(string *&restaurant_name_ptr, string &owner, string &test)
{
    for (auto &restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            restaurant.getUserReservesR(owner, test);
            return;
        }
    }
    throw Exception(NOT_FOUND);
}
void Getter::getUserReservesRI(string *&restaurant_name_ptr, string *&reserve_id_ptr, string &owner, string &test)
{
    for (auto &restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            restaurant.getUserReservesRI(owner, reserve_id_ptr, test);
            return;
        }
    }
    throw Exception(NOT_FOUND);
}
void Getter::getUserReservesAll(string &owner, string &test)
{
    int reserves_nums = 0;
    vector<pair<Reserve, string>> all_user_reserves;
    for (auto &restaurant : restaurants)
    {
        restaurant.getUserReservesAll(owner, reserves_nums, all_user_reserves);
    }
    if (reserves_nums == 0)
    {
        throw Exception(EMPTY);
    }
    else
    {
        sort(all_user_reserves.begin(), all_user_reserves.end(), [](pair<Reserve, string> &a, pair<Reserve, string> &b)
             { return a.first.getTimes().first < b.first.getTimes().first; });
        for (auto item : all_user_reserves)
        {
            int without_dis = 0;
            int with_dis = 0;
            item.first.printUserReservesRI(item.second, with_dis, without_dis, test);
        }
    }
}
void Getter::getRestaurantDetail(vector<string> &command_words)
{
    string *restaurant_name_ptr = nullptr;
    if (is_bad_get_restaurant_request(command_words, restaurant_name_ptr) == true)
    {
        throw Exception(BAD_REQ);
    }
    for (auto restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            restaurant.getRestaurantDetail();
            return;
        }
    }
    throw Exception(NOT_FOUND);
}
void Getter::getDistrict(vector<string> &command_words)
{
    string *district_ptr = nullptr;
    if (is_bad_get_district_request(command_words, district_ptr) == true)
    {
        throw Exception(BAD_REQ);
    }
    for (auto district : districts)
    {
        if (district.first == (*district_ptr).substr(1, (*district_ptr).size() - 2))
        {
            cout << district.first << ": ";
            for (auto it = district.second.begin(); it != district.second.end(); it++)
            {
                cout << *it;
                if (it == district.second.end() - 1)
                {
                    cout << endl;
                }
                else
                {
                    cout << ", ";
                }
            }
            return;
        }
    }
    throw Exception(NOT_FOUND);
}
void Getter::getDistricts(vector<string> &command_words)
{
    if (command_words[2] != "?")
    {
        throw Exception(BAD_REQ);
    }
    if (districts.size() == 0)
    {
        throw Exception(EMPTY);
    }
    sort(districts.begin(), districts.end(), [](const auto &a, const auto &b)
         { return a.first < b.first; });
    for (auto district : districts)
    {
        cout << district.first << ": ";
        for (auto it = district.second.begin(); it != district.second.end(); it++)
        {
            cout << *it;
            if (it == district.second.end() - 1)
            {
                cout << endl;
            }
            else
            {
                cout << ", ";
            }
        }
    }
}
void Getter::showBudget()
{
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            cout << user.second.user_balance << endl;
        }
    }
}