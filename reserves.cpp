#include "reserves.hpp"
Reserve::Reserve(string owner_, vector<string> food_, pair<int, int> times_, int id_, int table_num_)
{
    owner = owner_;
    food = food_;
    times = times_;
    table_num = table_num_;
    id = id_;
}
void Reserve::printReserveMessage(string &restaurant_name, int price)
{
    cout << "Reserve ID: " << id << endl;
    cout << "Table " << table_num << " for " << times.first << " to " << times.second << " in " << restaurant_name << endl;
    cout << "Price: " << price << endl;
}
void Reserve::printUserReservesRI(string &restaurant_name)
{
    cout << id << ": " << restaurant_name << ' ' << table_num << ' ' << times.first << '-' << times.second;
    if (food.size() == 0)
    {
        cout << endl;
    }
    else
    {
        cout << ' ';
        map<string, int> food_info;
        for (auto f : food)
        {
            food_info[f]++;
        }
        for (auto it = food_info.begin(); it != food_info.end(); it++)
        {
            cout << (*it).first << "(" << (*it).second << ")";
            if (next(it) != food_info.end())
            {
                cout << ' ';
            }
            else
            {
                cout << endl;
            }
        }
    }
}
