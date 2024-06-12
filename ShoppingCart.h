#pragma once
#include "OrderManager.h"
#include "Inventory.h"
#include "CartItem.h"
class ShoppingCart {
private:
    vector<CartItem> items;
    Inventory& inventory;
    const string cartFile = "cart.txt";
    OrderManager orderManager;

public:
    ShoppingCart(Inventory& inv);
    ~ShoppingCart();
    void addItem(const CartItem& item);
    void showCart() const;
    void saveCart();
    void loadCart();
    bool checkout(string customerId);
};
