#include "command.hpp"
#include "Utaste.hpp"
Command::Command(string districts_path, string restaurants_path)
{
    readDistricts(districts_path);
    readRestaurants(restaurants_path);
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
void Command::readRestaurants(string restaurants_path)
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
            Restaurant temp_restaurant(temp_line[0], temp_line[1], temp_foods, stoi(temp_line[3]), stoi(temp_line[4]), stoi(temp_line[5]));
            restaurants.push_back(temp_restaurant);
            temp_foods.clear();
            temp_line.clear();
        }
    }
}
void Command::setNewUser(pair<USERNAME, USER_DATA> &new_user)
{
    users[new_user.first] = {false, new_user.second.password, new_user.second.user_district};
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
void Command::printReserveMessage(string *&restaurant_name_ptr)
{
    for (auto restaurant : restaurants)
    {
        if (restaurant.getName() == (*restaurant_name_ptr).substr(1, (*restaurant_name_ptr).size() - 2))
        {
            restaurant.printReserveMessage();
        }
    }
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
void Command::deleteReserve(vector<string> &command_words)
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
            restaurant.deleteReserve(owner, reserve_id_ptr);
            return;
        }
    }
    throw Exception(NOT_FOUND);
}
void Command::printing()
{
}