#include "restaurant.hpp"
#include "Utaste.hpp"
Restaurant::Restaurant(string name_, string district_, map<string, int> foods_, int opening_time_, int closing_time_, int table_no_)
{
    name = name_;
    district = district_;
    foods = foods_;
    opening_time = opening_time_;
    closing_time = closing_time_;
    table_no = table_no_;
}
bool Restaurant::checkConflict(string *&end_time_ptr, string *&start_time_ptr, string *&table_id_ptr)
{

    for (auto reserve : reserves)
    {
        if (reserve.getTableNum() == (*table_id_ptr).substr(1, (*table_id_ptr).size() - 2))
        {
            if (stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2)) <= reserve.getTimes().second && (stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2)) >= reserve.getTimes().first))
            {
                return true;
            }
            else if (stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2)) <= reserve.getTimes().second && (stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2)) >= reserve.getTimes().first))
            {
                return true;
            }
        }
    }
    return false;
}
bool Restaurant::checkUserConflict(string &owner, string *&start_time_ptr, string *&end_time_ptr)
{
    for (auto reserve : reserves)
    {
        if (reserve.getOwner() == owner)
        {
            if (stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2)) <= reserve.getTimes().second && (stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2)) >= reserve.getTimes().first))
            {
                return true;
            }
            else if (stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2)) <= reserve.getTimes().second && (stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2)) >= reserve.getTimes().first))
            {
                return true;
            }
        }
    }
    return false;
}
bool Restaurant::workingHoursRange(string *&start_time_ptr, string *&end_time_ptr)
{
    int start_time = stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2));
    int end_time = stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2));
    if ((end_time > closing_time) or (start_time < opening_time))
    {
        return true;
    }
    if ((stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2))) && (stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2)) == 1))
    {
        return true;
    }
    return false;
}
bool Restaurant::checkFoodsTables(string *&foods_ptr, string *&table_id_ptr)
{
    if (foods_ptr != nullptr)
    {
        string temp_word;
        stringstream s((*foods_ptr).substr(1, (*foods_ptr).size() - 2));
        while (getline(s, temp_word, ','))
        {
            auto it = find_if(foods.begin(), foods.end(),
                              [&temp_word](const pair<string, int> &item)
                              {
                                  return item.first == temp_word;
                              });

            if (it == foods.end())
            {
                return true;
            }
        }
    }
    return false;
}
void Restaurant::handleReserve(string &owner, string *&table_id_ptr, string *&start_time_ptr, string *&end_time_ptr, string *&foods_ptr)
{
    vector<string> temp_foods;
    if (foods_ptr != nullptr)
    {
        string temp_word;
        stringstream s((*foods_ptr).substr(1, (*foods_ptr).size() - 2));
        while (getline(s, temp_word, ','))
        {
            temp_foods.push_back(temp_word);
        }
    }
    int start_time = stoi((*start_time_ptr).substr(1, (*start_time_ptr).size() - 2));
    int end_time = stoi((*end_time_ptr).substr(1, (*end_time_ptr).size() - 2));
    Reserve temp_reserve(owner, temp_foods, {start_time, end_time}, reserves.size() + 1, stoi((*table_id_ptr).substr(1, (*table_id_ptr).size() - 2)));
    reserves.push_back(temp_reserve);
}
void Restaurant::printReserveMessage()
{
    int price = 0;
    vector<string> reserved_foods = reserves[reserves.size() - 1].getFoods();
    for (auto food : reserved_foods)
    {
        for (auto food2 : foods)
        {
            if (food == food2.first)
            {
                price += food2.second;
            }
        }
    }
    reserves.back().printReserveMessage(name, price);
}
void Restaurant::getUserReservesAll(string &owner, int &reserves_num, vector<pair<Reserve, string>> &all_user_reserves)
{
    for (auto reserve : reserves)
    {
        if (reserve.getOwner() == owner)
        {
            all_user_reserves.push_back({reserve, name});
            reserves_num++;
        }
    }
}
bool Restaurant::isFoodInMenu(string *&food_ptr)
{
    for (auto f : foods)
    {
        if (f.first == (*food_ptr).substr(1, (*food_ptr).size() - 2))
        {
            return true;
        }
    }
    return false;
}
void Restaurant::getUserReservesR(string &owner)
{
    vector<Reserve> temp_user_reserves;
    for (auto reserve : reserves)
    {
        if (reserve.getOwner() == owner)
        {
            temp_user_reserves.push_back(reserve);
        }
    }
    if (temp_user_reserves.size() == 0)
    {
        throw Exception(EMPTY);
    }
    else
    {
        sort(temp_user_reserves.begin(), temp_user_reserves.end(), [](Reserve &a, Reserve &b)
             { return a.getTimes().first < b.getTimes().first; });
        for (auto item : temp_user_reserves)
        {
            item.printUserReservesRI(name);
        }
    }
}
void Restaurant::getUserReservesRI(string &owner, string *&reserve_id_ptr)
{
    vector<Reserve> temp_user_reserves;
    for (auto reserve : reserves)
    {
        if (reserve.getID() == stoi((*reserve_id_ptr).substr(1, (*reserve_id_ptr).size() - 2)))
        {
            if (reserve.getOwner() == owner)
            {
                temp_user_reserves.push_back(reserve);
            }
            else
            {
                throw Exception(PERMISSION);
            }
        }
    }
    if (temp_user_reserves.size() == 0)
    {
        throw Exception(NOT_FOUND);
    }
    else
    {
        sort(temp_user_reserves.begin(), temp_user_reserves.end(), [](Reserve &a, Reserve &b)
             { return a.getTimes().first < b.getTimes().first; });
        for (auto item : temp_user_reserves)
        {
            item.printUserReservesRI(name);
        }
    }
}
void Restaurant::printAllFoods()
{
    vector<pair<string, int>> temp_foods;
    for (auto item : foods)
    {
        temp_foods.push_back(item);
    }
    sort(temp_foods.begin(), temp_foods.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.first < b.first;
         });
    for (auto it = temp_foods.begin(); it != temp_foods.end(); ++it)
    {
        cout << it->first << "(" << it->second << ")";
        if (next(it) != temp_foods.end())
        {
            cout << ", ";
        }
        else
        {
            cout << endl;
        }
    }
}
void Restaurant::printAllTables()
{
    for (int i = 1; i <= table_no; i++)
    {
        cout << i << ":";
        vector<pair<int, int>> temp_times;
        for (auto it = reserves.begin(); it != reserves.end(); it++)
        {
            if (stoi(it->getTableNum()) == i)
            {
                temp_times.push_back(it->getTimes());
            }
        }
        sort(temp_times.begin(), temp_times.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.first < b.first; });
        for (auto it = temp_times.begin(); it != temp_times.end(); it++)
        {
            cout << " (" << (*it).first << "-" << (*it).second << ")";
            if (next(it) != temp_times.end())
            {
                cout << ",";
            }
        }
        cout << endl;
    }
}
void Restaurant::getRestaurantDetail()
{
    cout << "Name: " << name << endl;
    cout << "District: " << district << endl;
    cout << "Time: " << opening_time << "-" << closing_time << endl;
    cout << "Menu: ";
    printAllFoods();
    printAllTables();
}
void Restaurant::deleteReserve(string &owner, string *&reserve_id_ptr)
{
    int reserve_id = stoi((*reserve_id_ptr).substr(1, (*reserve_id_ptr).size() - 2));
    vector<Reserve> temp_reserves = reserves;
    for (auto it = temp_reserves.begin(); it != temp_reserves.end(); ++it)
    {
        if (it->getID() == reserve_id)
        {
            if (it->getOwner() == owner)
            {
                temp_reserves.erase(it);
                reserves = temp_reserves;
                return;
            }
            else
            {
                throw Exception(PERMISSION);
            }
        }
    }
    throw Exception(NOT_FOUND);
}