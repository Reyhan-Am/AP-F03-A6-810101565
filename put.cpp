#include "put.hpp"
#include "Utaste.hpp"
Putter::Putter(string districts_path, string restaurants_path, string discounts_path, UTaste &utaste_ref) : Command(districts_path, restaurants_path, discounts_path), utaste(&utaste_ref) {}
void Putter::checkCommand(vector<string> command_words)
{
    if (command_words[1] == PUT_MY_DISTRICT)
    {
        this->putMyDistrict(command_words);
    }
    else
    {
        throw Exception(NOT_FOUND);
    }
}
void Putter::putMyDistrict(vector<string> &command_words)
{
    string username = "";
    if (this->hasPermission(username) == false)
    {
        throw Exception(PERMISSION);
    }
    string *districti_ptr = nullptr;
    for (auto it = command_words.begin() + CONST_WORD_NO; it != command_words.end(); it++)
    {
        if ((*it == "district") && (it + 1 != command_words.end()) && (isStartWithComma(*(it + 1)) == true))
        {
            districti_ptr = &*(it + 1);
        }
    }
    if ((districti_ptr == nullptr) or (*districti_ptr == ""
                                                         ""))
    {
        throw Exception(BAD_REQ);
    }
    for (auto district : districts)
    {
        if (district.first == (*districti_ptr).substr(1, (*districti_ptr).size()-2))
        {
            utaste->setUserDistrict(districti_ptr, username);
            return;
        }
    }
    throw Exception(NOT_FOUND);
}