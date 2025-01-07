#ifndef RESERVES_HPP
#define RESERVES_HPP

#include "head.hpp"

class Reserve
{
public:
    Reserve(string owner_, vector<string> food_, pair<int, int> times_, int id_, int table_num_, int expense_ = 0, int pure_expense_ = 0);
    pair<int, int> getTimes() { return times; };
    string getOwner() { return owner; };
    int getExpense() { return expense; }
    string getTableNum() { return to_string(table_num); };
    vector<string> getFoods() { return food; };
    void setExpense(int new_expense) { expense = new_expense; }
    void setExpenses(pair<int, int> new_expenses)
    {
        expense = new_expenses.first;
        pure_expense = new_expenses.second;
    }
    pair<int, int> printReserveMessage(string &restaurant_name, int price, int &first_diss, int &food_diss, int &total_diss, int &final_diss);
    void printUserReservesRI(string &restaurant_name, int &with_dis, int &without_dis);
    int getID() { return id; };

private:
    string owner;
    vector<string> food;
    pair<int, int> times;
    int id;
    int expense;
    int pure_expense;
    int table_num;
};

#endif