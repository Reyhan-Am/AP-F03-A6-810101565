#ifndef DELETE_HPP
#define DELETE_HPP

#include "command.hpp"
#include "head.hpp"

class Deleter : public Command{
public:
    Deleter(string districts_path, string restaurants_path);

};

#endif