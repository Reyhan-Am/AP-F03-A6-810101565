#ifndef POST_HPP
#define POST_HPP

#include "command.hpp"
#include "head.hpp"
class UTaste;

class Poster : public Command
{
public:
    Poster(string districts_path, string restaurants_path, string discounts_path, UTaste& utaste_ref);
    virtual void checkCommand(vector<string> command_words);
    void signUp(vector<string> &command_words);
    void logIn(vector<string> &command_words);
    void logOut(vector<string> &command_words);
    void reserveFunc(vector<string> &command_words);
    void increaseBudget(vector<string> &command_words);
    void printing();
private:
    UTaste* utaste;
};

#endif