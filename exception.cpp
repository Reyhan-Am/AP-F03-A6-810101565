#include "exception.hpp"
Exception::Exception(string discription_)
{
    discription = discription_;
}
void Exception::handleException()
{
    cout<< discription<<endl;
}