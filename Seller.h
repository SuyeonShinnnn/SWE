#pragma once
#include "User.h"

class Seller : public User {
private:
    Inventory& inventory;
public:
    Seller(string id, string password, Inventory& inv);
    void showMenu() const override;
    void handleMenu(Inventory& inventory) override;
    void manageDeliveries();
    Inventory& getInventory();
};