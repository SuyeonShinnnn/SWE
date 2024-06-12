// User Class
#include "User.h"
#include <string>
#include <iostream>
using namespace std;

User::User(string id, string password) : id(id), password(password) {}
User::~User() {}

string User::getId() const { return id; }
string User::getPassword() const { return password; }
