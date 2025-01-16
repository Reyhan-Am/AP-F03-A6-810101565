#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include "head.hpp"

class Exception
{
public:
    Exception(string discription_);
    string getErrorMessage() { return discription; }
    void handleException();

private:
    string discription;
};
#endif