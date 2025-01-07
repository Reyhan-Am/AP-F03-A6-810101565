#include "total_discount.hpp"
TotalDiscount::TotalDiscount(string type_, int value_, int min_) : Discount(type_, value_) { min = min_; }
void TotalDiscount::printing()
{
    if (type != "")
    {
        cout << "Order Amount Discount: ";
        if (type == "percent")
        {
            cout << "percentage, ";
        }
        else
        {
            cout << "amount, ";
        }
        cout << min << ", " << value << endl;
    }
}
void TotalDiscount::calc_total_dis(int &temp_price, int &result)
{
    if (temp_price > min)
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
}