#ifndef DELETE_HPP
#define DELETE_HPP

#include "command.hpp"
#include "head.hpp"
class UTaste;

class Deleter : public Command
{
public:
    Deleter(string districts_path, string restaurants_path, string discounts_path, UTaste& utaste_ref);
    virtual void checkCommand(vector<string> command_words, string &test);
    void deleteReservefunc(vector<string> &command_words);
private:
    UTaste* utaste;
};

#endif