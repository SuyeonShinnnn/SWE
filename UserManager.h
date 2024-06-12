#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Inventory.h"
using namespace std;

class UserManager {
private:
    vector<User*> users;
    const string userFile = "users.txt";

public:
    UserManager(Inventory& inv);
    ~UserManager();
    User* findUser(const string& id, const string& password);
    void addUser(User* user);
    bool isUserIdTaken(const string& id);
    void saveUsers();
    void loadUsers(Inventory& inv);
};
