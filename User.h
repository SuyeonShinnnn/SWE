#pragma once
#include "Inventory.h"

class User {
protected:
    string id;
    string password;

public:
    User(string id, string password);
    virtual ~User();

    string getId()const;
    string getPassword()const;

    virtual void showMenu()const = 0;
    virtual void handleMenu(Inventory& inventory) = 0;
};