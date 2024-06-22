#pragma once
#include <string>
using namespace std;
class Product {
private:
    string name;
    string limitedFlag;
    int stock;
    double price;

public:
    Product(string _name, double _price, int _stock, string _limitedFlag);

    string getName()const;
    string getLimited()const;
    int getStock()const;
    double getPrice()const;
    void setStock(int newStock);
    void showProduct()const;
};
