#pragma once
#include <string>
using namespace std;

class Order {
private:
    string orderId;
    string product;
    string customerId;
    string status;
    string date;
    int count;

public:
    Order(string _orderId, string _product, int _count, string _customerId, string _status, string _date);
    string getOrderId() const;
    string getProduct() const;
    string getCustomerId() const;
    string getStatus() const;
    string getDate() const;

    void setStatus(const string& newStatus);
    void showOrder() const;

    int getCount() const;
};
