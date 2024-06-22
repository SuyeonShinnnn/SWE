#pragma once
#include "User.h"
#include "Auction.h"

class Seller : public User {
private:
    Inventory& inventory;
    Auction a;
public:
    Seller(string id, string password, Inventory& inv);
    void showMenu() const override;
    void handleMenu(Inventory& inventory) override;
    void manageDeliveries();
    void managePickUp();
    Inventory& getInventory();
};