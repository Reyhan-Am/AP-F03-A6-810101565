#ifndef DISCOUNT_HPP
#define DISCOUNT_HPP

#include "head.hpp"

class Discount
{
public:
    Discount(string type_ = "", int value_ = 0);
    Discount(const Discount &other) = default;
    void update_values(string type_, int value_)
    {
        value = value_;
        type = type_;
    }
    virtual void printing();
    void calc_first_dis(int &temp_price, int &result);

protected:
    string type;
    int value;
};

#endif