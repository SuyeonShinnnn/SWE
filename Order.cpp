#include "Order.h"
#include <iostream>

Order::Order(string _orderId, string _product, int _count, string _customerId, string _status, string _date)
    : orderId(_orderId), product(_product), count(_count), customerId(_customerId), status(_status), date(_date) {}
string Order::getOrderId() const
{
    return orderId;
}
string Order::getProduct() const
{
    return product;
}
int Order::getCount() const
{
    return count;
}
string Order::getCustomerId() const
{
    return customerId;
}
string Order::getStatus() const
{
    return status;
}
string Order::getDate() const
{
    return date;
}

void Order::setStatus(const string& newStatus)
{
    status = newStatus;
}
void Order::showOrder() const {
    cout << "주문번호: " << orderId << ", 상품: " << product << ", 수량: " << count << ", 고객ID: " << customerId << ", 상태: " << status << ", 날짜: " << date << endl;
}