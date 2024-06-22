#pragma once
#include "User.h"
#include "ShoppingCart.h"
#include "ReviewManager.h"

class Customer : public User {
private:
    ShoppingCart cart;
    OrderManager orderManager;
    ReviewManager reviewManager;

public:
    Customer(string id, string password, Inventory& inv);
    ShoppingCart& getCart();
    void showMenu() const override;
    void handleMenu(Inventory& inventory) override;
    void addToCart(Inventory& inventory);
    void manageReviews();
    void writeReview();
};
