#ifndef TOTAL_DISCOUNT_HPP
#define TOTAL_DISCOUNT_HPP

#include "discount.hpp"
#include "head.hpp"

class TotalDiscount : public Discount
{
public:
    TotalDiscount(string type_ = "", int value_ = 0, int min_ = 0);
    TotalDiscount(const TotalDiscount &other) = default;
    void update_values(string type_, int min_, int value_)
    {
        min = min_;
        value = value_;
        type = type_;
    }
    void printing();
    void calc_total_dis(int &temp_price, int &result);

private:
    int min;
};

#endif