#ifndef PUT_HPP
#define PUT_HPP

#include "command.hpp"
#include "head.hpp"
class UTaste;

class Putter : public Command
{
public:
    Putter(string districts_path, string restaurants_path, UTaste& utaste_ref);
    virtual void checkCommand(vector<string> command_words);
    void putMyDistrict(vector<string> &command_words);

private:
        UTaste* utaste;
};

#endif