#include "discount.hpp"
Discount::Discount(string type_, int value_)
{
    type = type_;
    value = value_;
}
void Discount::printing()
{
    if (type != "")
    {
        cout << "First Order Discount: ";
        if (type == "percent")
        {
            cout << "percentage, ";
        }
        else
        {
            cout << "amount, ";
        }
        cout << value << endl;
    }
}
void Discount::calc_first_dis(int &temp_price, int &result)
{
    if (type == AMOUNT)
    {
        result = value;
    }
    else
    {
        result = ((value * temp_price) / 100);
    }
}