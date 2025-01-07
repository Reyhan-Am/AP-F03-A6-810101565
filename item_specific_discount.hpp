#ifndef Item_Specific_Discount_HPP
#define Item_Specific_Discount_HPP

#include "discount.hpp"
#include "head.hpp"

class ItemSpecificDiscount : public Discount
{
public:
    ItemSpecificDiscount(string type_ = "", int value_ = 0, string food_ = "");
    ItemSpecificDiscount(const ItemSpecificDiscount &other) = default;
    string getFood() { return food; }
    void calc_food_dis(int &dis, int &food_price);
    void printing();

private:
    string food;
};

#endif