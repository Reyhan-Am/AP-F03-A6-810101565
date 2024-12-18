#ifndef UTASTE_HPP
#define UTASTE_HPP
#include "head.hpp"
#include "put.hpp"
#include "post.hpp"
#include "delete.hpp"
#include "get.hpp"

class UTaste
{
public:
    UTaste(string districts_path, string restaurants_path);
    void printing();

protected:
    Putter putter;
    Poster poster;
    Deleter deleter;
    Getter getter;
};
#endif