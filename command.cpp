#include "command.hpp"
#include "Utaste.hpp"
Command::Command(string restaurants_path, string districts_path, string discounts_path, UTaste& utaste_ref)
{
    readDistricts(districts_path);
    readRestaurants(restaurants_path, discounts_path, utaste_ref);
}
void Command::readDistricts(string districs_path)
{
    fstream csv_file;
    csv_file.open(districs_path);
    string line, word;
    vector<string> temp_line, temp_neighbors;
    int first_line_flag = 1;
    while (getline(csv_file, line))
    {
        stringstream line_stream(line);
        if (first_line_flag)
        {
            first_line_flag = 0;
            continue;
        }
        else
        {
            while (getline(line_stream, word, ','))
            {
                temp_line.push_back(word);
            }
            stringstream neighbors_stream(temp_line[1]);
            while (getline(neighbors_stream, word, ';'))
            {
                temp_neighbors.push_back(word);
            }
            districts.push_back({temp_line[0], temp_neighbors});
            temp_neighbors.clear();
            temp_line.clear();
        }
    }
}
void Command::readRestaurants(string restaurants_path, string discounts_path, UTaste& utaste_ref)
{
    fstream csv_file;
    csv_file.open(restaurants_path);
    string line, word;
    vector<string> temp_line, temp_food;
    map<string, int> temp_foods;
    int first_line_flag = 1;
    while (getline(csv_file, line))
    {
        stringstream line_stream(line);
        if (first_line_flag)
        {
            first_line_flag = 0;
            continue;
        }
        else
        {
            while (getline(line_stream, word, ','))
            {
                temp_line.push_back(word);
            }
            stringstream foods_stream(temp_line[2]);
            while (getline(foods_stream, word, ';'))
            {
                stringstream food_stream(word);
                while (getline(food_stream, word, ':'))
                {
                    temp_food.push_back(word);
                }
                temp_foods[temp_food[0]] = stoi(temp_food[1]);
                temp_food.clear();
            }
            Discount first_dis;
            TotalDiscount total_dis;
            vector<ItemSpecificDiscount> food_dis;
            readDiscounts(first_dis, total_dis, food_dis, discounts_path, temp_line[0]);
            Restaurant temp_restaurant(temp_line[0], temp_line[1], temp_foods, stoi(temp_line[3]), stoi(temp_line[4]), stoi(temp_line[5]), first_dis, total_dis, food_dis, utaste_ref);
            restaurants.push_back(temp_restaurant);
            temp_foods.clear();
            temp_line.clear();
        }
    }
}
void Command::readDiscounts(Discount &first_dis, TotalDiscount &total_dis, vector<ItemSpecificDiscount> &food_dis, string discounts_path, string &name)
{
    fstream csv_file;
    csv_file.open(discounts_path);
    string line, word;
    vector<string> temp_line, temp_dis;
    int first_line_flag = 1;
    while (getline(csv_file, line))
    {
        stringstream line_stream(line);
        if (first_line_flag)
        {
            first_line_flag = 0;
            continue;
        }
        else
        {
            while (getline(line_stream, word, ','))
            {
                temp_line.push_back(word);
            }
            if (temp_line[0] == name)
            {
                stringstream s1(temp_line[1]);
                while (getline(s1, word, ';'))
                {
                    temp_dis.push_back(word);
                }
                if (temp_dis[0] != "none")
                {
                    total_dis.update_values(temp_dis[0], stoi(temp_dis[1]), stoi(temp_dis[2]));
                }
                temp_dis.clear();
                stringstream s2(temp_line[2]);
                while (getline(s2, word, ';'))
                {
                    temp_dis.push_back(word);
                }
                if (temp_dis[0] != "none")
                {
                    first_dis.update_values(temp_dis[0], stoi(temp_dis[1]));
                }
                temp_dis.clear();
                stringstream s3(temp_line[3]);
                while (getline(s3, word, '|'))
                {
                    stringstream s4(word);
                    while (getline(s4, word, ';'))
                    {
                        temp_dis.push_back(word);
                    }
                    if (temp_dis[0] != "none")
                    {
                        stringstream s5(temp_dis[1]);
                        temp_dis.erase(temp_dis.begin() + 1, temp_dis.end());
                        while (getline(s5, word, ':'))
                        {
                            temp_dis.push_back(word);
                        }
                        food_dis.push_back(ItemSpecificDiscount(temp_dis[0], stoi(temp_dis[2]), temp_dis[1]));
                    }
                    temp_dis.clear();
                }
                temp_line.clear();
            }
            else
            {
                temp_line.clear();
            }
        }
    }
}
void Command::setNewUser(pair<USERNAME, USER_DATA> &new_user)
{
    users[new_user.first] = {false, new_user.second.password, new_user.second.user_district, 10000000};
}
void Command::setLogin(string username)
{
    users[username].is_logged_in = true;
}
void Command::setLogout(string username)
{
    users[username].is_logged_in = false;
}
void Command::setUserDistrict(string *districti_ptr, string username)
{
    for (auto &user : users)
    {
        if (user.second.is_logged_in == true)
        {
            user.second.user_district = (*districti_ptr).substr(1, (*districti_ptr).size() - 2);
        }
    }
}
bool Command::hasPermission(string username)
{
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            username = user.first;
            return true;
        }
    }
    return false;
}
void Command::setReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                         string *&end_time_ptr,
                         string *&foods_ptr)
{
    for (auto &restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            if ((checkRestaurantTimeConflic(restaurant, start_time_ptr, end_time_ptr, table_id_ptr) == true))
            {
                throw Exception(PERMISSION);
            }
            else if (is_logged_in() == false)
            {
                throw Exception(PERMISSION);
            }
            else if (checkUserTimeConflict(start_time_ptr, end_time_ptr) == true)
            {
                throw Exception(PERMISSION);
            }
            else if (checkWorkingHoursRange(restaurant, start_time_ptr, end_time_ptr) == true)
            {
                throw Exception(PERMISSION);
            }
            else if (checkFoodsTables(restaurant, foods_ptr, table_id_ptr) == true)
            {
                throw Exception(NOT_FOUND);
            }
            else
            {
                return;
            }
        }
    }
    throw Exception(NOT_FOUND);
}
bool Command::checkRestaurantTimeConflic(Restaurant &restaurant, string *&start_time_ptr, string *&end_time_ptr, string *&table_id_ptr)
{
    if (restaurant.checkConflict(end_time_ptr, start_time_ptr, table_id_ptr) == true)
    {
        return true;
    }
    return false;
}
void Command::delLastReserve(string &name)
{
    for (auto &r : restaurants)
    {
        if (r.getName() == name)
        {
            r.delLastReserve();
        }
    }
}
bool Command::checkUserTimeConflict(string *&start_time_ptr, string *&end_time_ptr)
{
    string owner = "";
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            owner = user.first;
        }
    }
    for (auto restaurant : restaurants)
    {
        if (restaurant.checkUserConflict(owner, start_time_ptr, end_time_ptr) == true)
        {
            return true;
        }
    }
    return false;
}
bool Command::checkWorkingHoursRange(Restaurant &restaurant, string *&start_time_ptr, string *&end_time_ptr)
{
    if (restaurant.workingHoursRange(end_time_ptr, start_time_ptr) == true)
    {
        return true;
    }
    return false;
}
bool Command::checkFoodsTables(Restaurant &restaurant, string *&foods_ptr, string *&table_id_ptr)
{
    if (restaurant.checkFoodsTables(foods_ptr, table_id_ptr) == true)
    {
        return true;
    }

    if (stoi((*table_id_ptr).substr(1, (*table_id_ptr).size() - 2)) > restaurant.getTableNo())
    {
        return true;
    }
    return false;
}
void Command::handleReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr, string *&end_time_ptr, string *&foods_ptr)
{
    string owner;
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            owner = user.first;
        }
    }
    for (auto &restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            restaurant.handleReserve(owner, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
        }
    }
}
Temp Command::printReserveMessage(string *&restaurant_name_ptr)
{
    int account_balance = 0;
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            account_balance = user.second.user_balance;
        }
    }
    for (auto restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            return restaurant.printReserveMessage(account_balance);
        }
    }
    return {{0, 0}, ""};
}
bool is_bad_delReserve_request(vector<string> &command_words, string *&restaurant_name_ptr, string *&reserve_id_ptr)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if ((*it == "restaurant_name") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            restaurant_name_ptr = &*(it + 1);
        }
        else if ((*it == "reserve_id") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            reserve_id_ptr = &*(it + 1);
        }
    }
    if ((restaurant_name_ptr == nullptr) or (reserve_id_ptr == nullptr) or (*restaurant_name_ptr == ""
                                                                                                    "") or
        (*reserve_id_ptr == ""
                            ""))
    {
        return true;
    }
    return false;
}
int Command::deleteReserve(vector<string> &command_words)
{
    string *restaurant_name_ptr = nullptr;
    string *reserve_id_ptr = nullptr;
    if (is_bad_delReserve_request(command_words, restaurant_name_ptr, reserve_id_ptr) == true)
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
    for (auto &restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            return restaurant.deleteReserve(owner, reserve_id_ptr);
        }
    }
    throw Exception(NOT_FOUND);
}
void Command::setLastReserveExpense(string *&restaurant_name_ptr, pair<int, int> &expense)
{
    for (auto &restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            restaurant.setLastReserveExpense(expense);
        }
    }
}
void Command::setBudget(int &amount)
{
    string username = "";
    for (auto user : users)
    {
        if (user.second.is_logged_in == true)
        {
            username = user.first;
        }
    }
    users[username].user_balance += amount;
}
void Command::printing()
{
}