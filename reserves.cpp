#include "reserves.hpp"
Reserve::Reserve(string owner_, vector<string> food_, pair<int, int> times_, int id_, int table_num_, int expense_, int pure_expense_)
{
    owner = owner_;
    food = food_;
    times = times_;
    table_num = table_num_;
    expense = expense_;
    id = id_;
    pure_expense = pure_expense_;
}
pair<int, int> Reserve::printReserveMessage(string &restaurant_name, int price, int &first_diss, int &food_diss, int &total_diss, int &final_diss)
{
    cout << "Reserve ID: " << id << endl;
    cout << "Table " << table_num << " for " << times.first << " to " << times.second << " in " << restaurant_name << endl;
    cout << "Original Price: " << price << endl;
    cout << "Order Amount Discount: " << total_diss << endl;
    cout << "Total Item Specific Discount: " << food_diss << endl;
    cout << "First Order Discount: " << first_diss << endl;
    cout << "Total Discount: " << final_diss << endl;
    cout << "Total Price: " << price - final_diss << endl;
    return {price - final_diss, price};
}
void Reserve::printUserReservesRI(string &restaurant_name, int &with_dis, int &without_dis)
{
    with_dis += expense;
    without_dis += pure_expense;
    cout << id << ": " << restaurant_name << ' ' << table_num << ' ' << times.first << '-' << times.second;
    cout << ' ';
    map<string, int> food_info;
    for (auto f : food)
    {
        food_info[f]++;
    }
    for (auto it = food_info.begin(); it != food_info.end(); it++)
    {
        cout << (*it).first << "(" << (*it).second << ")" << ' ';
    }

    cout << without_dis << ' ' << with_dis << endl;
}
