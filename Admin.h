#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin(string id, string password);
    void showMenu() const override;
    void handleMenu(Inventory& inventory) override;
};
