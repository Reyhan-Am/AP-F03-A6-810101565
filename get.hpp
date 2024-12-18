#ifndef GET_HPP
#define GET_HPP

#include "command.hpp"
#include "head.hpp"

class Getter : public Command{
public:
    Getter(string districts_path, string restaurants_path);

};

#endif