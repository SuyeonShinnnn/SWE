#include "PickUp.h"
#include <fstream>
#include <iostream>
#include <sstream>

string PickUp::getId() const
{
    return id;
}
void PickUp::setId(string id)
{
    this->id = id;
}
void PickUp::displayPickupReservations() const
{
    ifstream file("pickup.txt");
    if (!file) {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    string line;
    cout << "현재 예약 목록:\n";
    cout << "-------------------------\n";
    cout << "|   날짜   | 상품명 | 갯수 |\n";
    cout << "-------------------------\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string date, productName, quantity, userId;
        getline(ss, date, ',');
        getline(ss, productName, ',');
        getline(ss, quantity, ',');
        getline(ss, userId, ',');
        if (userId == getId()) {
            cout << "| " << date << " | " << productName << " | " << quantity << " | \n";
        }
    }

    cout << "-------------------------\n";
    file.close();
}

void PickUp::reservePickUp(string date, string productName, int count, string id) {
    ofstream file(pickUpFile);
    file << date << "," << productName << "," << count << "," << id << endl;
    file.close();
}
