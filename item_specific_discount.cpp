#include "item_specific_discount.hpp"
ItemSpecificDiscount::ItemSpecificDiscount(string type_, int value_, string food_) : Discount(type_, value_) { food = food_; }
void ItemSpecificDiscount::printing()
{
    cout << food << "(";
    if (type == PERCENT)
    {
        cout << "percentage: ";
    }
    else
    {
        cout << "amount: ";
    }
    cout << value << ")";
}
void ItemSpecificDiscount::calc_food_dis(int &dis, int &food_price)
{
    if (type == AMOUNT)
    {
        dis += value;
    }
    else
    {
        dis += ((value * food_price) / 100);
    }
}