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
Temp Reserve::printReserveMessage(string &restaurant_name, int price, int &first_diss, int &food_diss, int &total_diss, int &final_diss)
{
    std::string result = "";
    result += "Reserve ID: " + std::to_string(id) + "\n";
    result += "Table " + std::to_string(table_num) + " for " + std::to_string(times.first) + " to " + std::to_string(times.second) + " in " + restaurant_name + "\n";
    result += "Original Price: " + std::to_string(price) + "\n";
    result += "Order Amount Discount: " + std::to_string(total_diss) + "\n";
    result += "Total ItemSpecific Discount: " + std::to_string(food_diss) + "\n";
    result += "First Order Discount: " + std::to_string(first_diss) + "\n";
    result += "Total Discount: " + std::to_string(final_diss) + "\n";
    result += "Total Price: ";
    if (price - final_diss >= 0)
    {
        result += std::to_string(price - final_diss) + "\n";
    }
    else
    {
        result += "0\n";
    }
    return {{price - final_diss, price}, result};
}
void Reserve::printUserReservesRI(string &restaurant_name, int &with_dis, int &without_dis, string &test)
{
    with_dis += expense;
    without_dis += pure_expense;
    test += id + ": " + restaurant_name + ' ' + std::to_string(table_num) + ' ' +
            std::to_string(times.first) + '-' + std::to_string(times.second) + ' ';
    map<string, int> food_info;
    for (auto f : food)
    {
        food_info[f]++;
    }
    for (auto it = food_info.begin(); it != food_info.end(); it++)
    {
        test += it->first + "(" + std::to_string(it->second) + ") ";
    }

    test += std::to_string(without_dis) + ' ' + std::to_string(with_dis) + '\n';
}
