#include "post.hpp"
#include "Utaste.hpp"
Poster::Poster(string districts_path, string restaurants_path, string discounts_path, UTaste &utaste_ref) : Command(districts_path, restaurants_path, discounts_path, utaste_ref), utaste(&utaste_ref) {}
void Poster::checkCommand(vector<string> command_words, string &test)
{
    if (command_words[1] == SIGNUP)
    {
        this->signUp(command_words);
    }
    else if (command_words[1] == LOGIN)
    {
        this->logIn(command_words);
    }
    else if (command_words[1] == LOGOUT)
    {
        this->logOut(command_words);
    }
    else if (command_words[1] == RESERVE)
    {
        this->reserveFunc(command_words , test);
    }
    else if (command_words[1] == INCREASE_BUDGET)
    {
        this->increaseBudget(command_words);
    }
    else
    {
        throw Exception(NOT_FOUND);
    }
}
bool check_pointers(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                    string *&end_time_ptr)
{
    if ((restaurant_name_ptr == nullptr) or (table_id_ptr == nullptr) or (start_time_ptr == nullptr) or (end_time_ptr == nullptr))
    {
        return false;
    }
    if ((*restaurant_name_ptr == ""
                                 "") or
        (*table_id_ptr == ""
                          "") or
        (*start_time_ptr == ""
                            "") or
        (*end_time_ptr == ""
                          ""))
    {
        return false;
    }
    return true;
}
bool isNumber(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
bool is_bad_budget_request(string *&amount_ptr, vector<string> &command_words)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if (*it == "amount" && (it + 1 != command_words.end()) && isNumber(*(it + 1)) == true)
        {
            amount_ptr = &*(it + 1);
        }
    }
    if ((amount_ptr == nullptr) or (*amount_ptr == ""
                                                   ""))
    {
        return true;
    }
    return false;
}
bool is_bad_reserve_request(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                            string *&end_time_ptr,
                            string *&foods_ptr, vector<string> &command_words)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if (*it == "restaurant_name" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            restaurant_name_ptr = &*(it + 1);
        }
        else if (*it == "table_id" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            table_id_ptr = &*(it + 1);
        }
        else if (*it == "start_time" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            start_time_ptr = &*(it + 1);
        }
        else if (*it == "end_time" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            end_time_ptr = &*(it + 1);
        }
        else if (*it == "foods" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            foods_ptr = &*(it + 1);
        }
    }
    if (check_pointers(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr) == true)
    {
        return false;
    }
    return true;
}
bool is_bad_request(string *&username_ptr, string *&password_ptr, vector<string> &command_words)
{
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if (*it == "username" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            username_ptr = &*(it + 1);
        }
        else if (*it == "password" && (it + 1 != command_words.end()) && isStartWithComma(*(it + 1)) == true)
        {
            password_ptr = &*(it + 1);
        }
    }
    if ((username_ptr == nullptr) or (password_ptr == nullptr) or (*username_ptr == ""
                                                                                    "") or
        (*password_ptr == ""
                          ""))
    {
        return true;
    }
    return false;
}
void Poster::signUp(vector<string> &command_words)
{
    string *username_ptr = nullptr;
    string *password_ptr = nullptr;
    if (is_bad_request(username_ptr, password_ptr, command_words) == true)
    {
        throw Exception(BAD_REQ);
    }
    else
    {
        for (auto user : users)
        {
            if (user.second.is_logged_in == true)
            {
                throw Exception(PERMISSION);
            }
            else if (user.first == *username_ptr)
            {
                throw Exception(BAD_REQ);
            }
        }
    }
    pair<USERNAME, USER_DATA> new_user = {*username_ptr, {false, *password_ptr, ""}};
    utaste->setNewUser(new_user);
    utaste->setLogin(*username_ptr);
    throw Exception(OK);
}
void Poster::logIn(vector<string> &command_words)
{
    string *username_ptr = nullptr;
    string *password_ptr = nullptr;
    if (is_bad_request(username_ptr, password_ptr, command_words) == true)
    {
        throw Exception(BAD_REQ);
    }
    else
    {
        for (auto &user : users)
        {
            if (user.second.is_logged_in == true)
            {
                throw Exception(PERMISSION);
            }
            else if (user.first == *username_ptr)
            {
                if (user.second.password != *password_ptr)
                {
                    throw Exception(PERMISSION);
                }
                else
                {
                    utaste->setLogin(*username_ptr);
                    throw Exception(OK);
                }
            }
        }
    }
    throw Exception(NOT_FOUND);
}
void Poster::logOut(vector<string> &command_words)
{
    if (command_words[2] != "?")
    {
        throw Exception(BAD_REQ);
    }
    for (auto &user : users)
    {
        if (user.second.is_logged_in == true)
        {
            utaste->setLogout(user.first);
            throw Exception(OK);
        }
    }
    throw Exception(PERMISSION);
}
void Poster::reserveFunc(vector<string> &command_words, string &test)
{
    string *restaurant_name_ptr = nullptr;
    string *table_id_ptr = nullptr;
    string *start_time_ptr = nullptr;
    string *end_time_ptr = nullptr;
    string *foods_ptr = nullptr;
    if (is_bad_reserve_request(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr, command_words) == true)
    {
        throw Exception(BAD_REQ);
    }
    else
    {
        utaste->setReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr, test);
    }
}
void Poster::increaseBudget(vector<string> &command_words)
{
    if (this->hasPermission("") == false)
    {
        throw Exception(PERMISSION);
    }
    string *amount_ptr = nullptr;
    if (is_bad_budget_request(amount_ptr, command_words) == true)
    {
        throw Exception(BAD_REQ);
    }
    else
    {
        int amount = stoi(*amount_ptr);
        utaste->increaseBudget(amount);
    }
}