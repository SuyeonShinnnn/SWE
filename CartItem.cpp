#include "CartItem.h"
#include <iostream>

CartItem::CartItem(string product, int count, double price)
    : product(product), count(count), price(price) {}

string CartItem::getProduct() const
{
    return product;
}
int CartItem::getCount() const
{
    return count;
}
double CartItem::getPrice() const
{
    return price;
}
void CartItem::showItem() const
{
    cout << "상품: " << product << ", 수량: " << count << ", 가격: " << price << endl;
}