#pragma once
#include <string>
using namespace std;

class PickUp {

private:
    const string pickUpFile = "pickup.txt";
    string id;
public:
    string getId() const;
    void setId(string id);
    void displayPickupReservations() const;
    void reservePickUp(string date, string productName, int count, string id);
};
