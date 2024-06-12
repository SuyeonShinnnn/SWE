// UserManager Class
#include <fstream>
#include <sstream>
#include "Customer.h"
#include "Seller.h"
#include "Admin.h"
#include "UserManager.h"


UserManager::UserManager(Inventory& inv) {
    loadUsers(inv);
}

UserManager::~UserManager() {
    saveUsers();
    for (auto user : users) {
        delete user;
    }
}
void UserManager::addUser(User* user) {
    users.push_back(user);
    saveUsers();
}
User* UserManager::findUser(const string& id, const string& password) {
    for (auto user : users) {
        if (user->getId() == id && user->getPassword() == password) {
            return user;
        }
    }
    return nullptr;
}
bool UserManager::isUserIdTaken(const string& id) {
    for (const auto& user : users) {
        if (user->getId() == id) {
            return true;
        }
    }
    return false;
}
void UserManager::saveUsers() {
    ofstream file(userFile);
    for (const auto user : users) {
        string role = "customer"; // Default role
        if (dynamic_cast<Admin*>(user)) {
            role = "admin";
        }
        else if (dynamic_cast<Seller*>(user)) {
            role = "seller";
        }
        file << user->getId() << "," << user->getPassword() << "," << role << endl;
    }
    file.close();
}
void UserManager::loadUsers(Inventory& inv) {
    ifstream file(userFile);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, password, role;
        getline(ss, id, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');
        if (role == "customer") {
            users.push_back(new Customer(id, password, inv));
        }
        else if (role == "admin") {
            users.push_back(new Admin(id, password));
        }
        else if (role == "seller") {
            users.push_back(new Seller(id, password, inv));
        }
    }
    file.close();
}