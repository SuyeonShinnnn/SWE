#include "ShoppingCart.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ShoppingCart Class
ShoppingCart::ShoppingCart(Inventory& inv) : inventory(inv)
{
    loadCart();
}

ShoppingCart ::~ShoppingCart() 
{
    saveCart();
}

void ShoppingCart::addItem(const CartItem& item)
{
    items.push_back(item);
    saveCart();
}

bool ShoppingCart::checkout(string customerId) {
    bool success = true;
    string orderId = to_string(time(0));

    for (auto& item : items) {
        int currentStock = inventory.searchProductStock(item.getProduct());


        if (currentStock < item.getCount()) {
            cout << "재고가 부족하여 결제에 실패하였습니다. " << item.getProduct() << endl;
            success = false;
        }
        else {
            orderManager.addOrder(orderId, item.getProduct(), item.getCount(), customerId, "발송전");
            inventory.updateStock(item.getProduct(), currentStock - item.getCount());
        }

    }
    if (success) {
        items.clear();
    }
    saveCart();
    return success;
}

void ShoppingCart::showCart() const
{
    for (const auto& item : items) {
        item.showItem();
    }
}

void ShoppingCart::saveCart()
{
    ofstream file(cartFile);
    for (const auto& item : items) {
        file << item.getProduct() << "," << item.getCount() << "," << item.getPrice() << endl;
    }
    file.close();
}
void ShoppingCart::loadCart() {
    ifstream file(cartFile);
    items.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string product, countStr, priceStr;
        getline(ss, product, ',');
        getline(ss, countStr, ',');
        getline(ss, priceStr, ',');
        int count = stoi(countStr);
        double price = stod(priceStr);
        items.emplace_back(product, count, price);
    }
    file.close();
}

