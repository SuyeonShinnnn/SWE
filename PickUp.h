#pragma once
#include <string>
#include <vector>
using namespace std;

class PickUp {

private:
    vector<PickUp> pickUp;
    const string pickUpFile = "pickup.txt";
    string id;
public:
    string getId() const;
    void setId(string id);
    void displayPickupReservations(string type) const;
    void updatePickUpStatus(int lineNumber);
    void reservePickUp(string date, string productName, int count, string id);
    int getLastLineNumber();
};
