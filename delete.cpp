#include "delete.hpp"
#include "Utaste.hpp"
Deleter::Deleter(string districts_path, string restaurants_path, string discounts_path, UTaste &utaste_ref) : Command(districts_path, restaurants_path, discounts_path, utaste_ref), utaste(&utaste_ref) {}
void Deleter::checkCommand(vector<string> command_words, string &test)
{
    if (this->hasPermission("") == false)
    {
        throw Exception(PERMISSION);
    }
    if (command_words[1] == RESERVE)
    {
        this->deleteReservefunc(command_words);
    }
    else if (command_words[1] == GET_RESTAURANT)
    {
    }
    else
    {
        throw Exception(NOT_FOUND);
    }
}
void Deleter::deleteReservefunc(vector<string> &command_words)
{
    utaste->deleteReserve(command_words);
}