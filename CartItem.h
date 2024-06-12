#pragma once
#include <string>
using namespace std;

class CartItem {
private:
    string product;
    int count;
    double price;

public:
    CartItem(string product, int count, double price);
    string getProduct() const;
    int getCount() const;
    double getPrice() const;
    void showItem() const;
};
