#include "Utaste.hpp"

UTaste::UTaste(string restaurants_path, string districts_path, string discounts_path)
    : putter(restaurants_path, districts_path, discounts_path, *this),
      poster(restaurants_path, districts_path, discounts_path, *this),
      deleter(restaurants_path, districts_path, discounts_path, *this),
      getter(restaurants_path, districts_path, discounts_path, *this) {}
void UTaste::checkCommand(const vector<string> &command_words, string &test)
{
    if (command_words[0] == "GET")
    {
        getter.checkCommand(command_words, test);
    }
    else if (command_words[0] == "PUT")
    {
        putter.checkCommand(command_words, test);
    }
    else if (command_words[0] == "POST")
    {
        poster.checkCommand(command_words, test);
    }
    else if (command_words[0] == "DELETE")
    {
        deleter.checkCommand(command_words, test);
    }
    else
    {
        throw Exception(BAD_REQ);
    }
}
void UTaste::deleteReserve(vector<string> &command_words)
{
    int expense = putter.deleteReserve(command_words);
    poster.deleteReserve(command_words);
    deleter.deleteReserve(command_words);
    getter.deleteReserve(command_words);
    expense = (6 * expense) / 10;
    putter.setBudget(expense);
    getter.setBudget(expense);
    poster.setBudget(expense);
    deleter.setBudget(expense);
    throw Exception(OK);
}
void UTaste::delLastReserve(string &name)
{
    putter.delLastReserve(name);
    poster.delLastReserve(name);
    deleter.delLastReserve(name);
    getter.delLastReserve(name);
}
void UTaste::setNewUser(pair<USERNAME, USER_DATA> &new_user)
{
    putter.setNewUser(new_user);
    poster.setNewUser(new_user);
    deleter.setNewUser(new_user);
    getter.setNewUser(new_user);
}
void UTaste::setLogin(string username)
{
    putter.setLogin(username);
    poster.setLogin(username);
    deleter.setLogin(username);
    getter.setLogin(username);
}
void UTaste::setLogout(string username)
{
    putter.setLogout(username);
    poster.setLogout(username);
    deleter.setLogout(username);
    getter.setLogout(username);
}
void UTaste::setUserDistrict(string *districti_ptr, string username)
{
    putter.setUserDistrict(districti_ptr, username);
    poster.setUserDistrict(districti_ptr, username);
    deleter.setUserDistrict(districti_ptr, username);
    getter.setUserDistrict(districti_ptr, username);
    throw Exception(OK);
}
void UTaste::setReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                        string *&end_time_ptr,
                        string *&foods_ptr, string &test)
{
    putter.setReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    putter.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    getter.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    deleter.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    poster.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    Temp temp;
    temp = putter.printReserveMessage(restaurant_name_ptr);
    putter.setLastReserveExpense(restaurant_name_ptr, temp.expenses);
    getter.setLastReserveExpense(restaurant_name_ptr, temp.expenses);
    deleter.setLastReserveExpense(restaurant_name_ptr, temp.expenses);
    poster.setLastReserveExpense(restaurant_name_ptr, temp.expenses);
    putter.decreaseBudget(temp.expenses.first);
    getter.decreaseBudget(temp.expenses.first);
    poster.decreaseBudget(temp.expenses.first);
    deleter.decreaseBudget(temp.expenses.first);
    test = temp.msg;
}
void UTaste::increaseBudget(int &amount)
{
    putter.setBudget(amount);
    getter.setBudget(amount);
    poster.setBudget(amount);
    deleter.setBudget(amount);
    throw Exception(OK);
}
void UTaste::printing()
{
}
