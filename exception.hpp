#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include "head.hpp"


class Exception
{
public:
    Exception(string discription_);
    void handleException ();

private:
    string discription;
};
#endif