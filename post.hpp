#ifndef POST_HPP
#define POST_HPP

#include "command.hpp"
#include "head.hpp"

class Poster : public Command{
public:
    Poster(string districts_path, string restaurants_path);

};

#endif