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
void PickUp::displayPickupReservations(string type) const
{
    ifstream file(pickUpFile);
    if (!file) {
        cout << "������ �� �� �����ϴ�.\n";
        return;
    }

    string line;
    cout << "��ȣ |   ��¥   | ��ǰ�� | ���� \n";

    while (getline(file, line)) {
        stringstream ss(line);
        string count, date, productName, quantity, userId, pickUpState;
        getline(ss, count, ',');
        getline(ss, date, ',');
        getline(ss, productName, ',');
        getline(ss, quantity, ',');
        getline(ss, userId, ',');
        getline(ss, pickUpState, ',');
       
        if (type == "customer" && userId == getId() && pickUpState == "No") {
            cout << count << "| " << date << " | " << productName << " | " << quantity << endl;
        }
        else if(type == "seller" && pickUpState == "No")
            cout << count << "| " << date << " | " << productName << " | " << quantity << endl;
    }
    cout << "==============================" << endl;
    file.close();
}
void PickUp::updatePickUpStatus(int lineNumber) {
 
    ifstream inputFile(pickUpFile);
    if (!inputFile.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << pickUpFile << endl;
        exit(0);
    }

    vector<string> lines;
    string line;
    string newLine;

    int count = 0;
    while (getline(inputFile, line)) {
        count++;
        lines.push_back(line);

        if (count == lineNumber) {
            stringstream ss(line);
            string pickUpNumber, date, productName, quantity, customerId, status;

            getline(ss, pickUpNumber, ',');
            getline(ss, date, ',');
            getline(ss, productName, ',');
            getline(ss, quantity, ',');
            getline(ss, customerId, ',');
            getline(ss, status, ',');

            newLine = pickUpNumber + "," + date + "," + productName + "," + quantity +
                "," + customerId + "," + "Yes";
        }
    }
    inputFile.close();

    if (lineNumber < 0 || lineNumber - 1 >= lines.size()) {
        cerr << "��ȿ���� ���� ��ȣ�Դϴ�: " << lineNumber << endl;
    }

    lines[lineNumber - 1] = newLine;

    ofstream outputFile(pickUpFile);
    if (!outputFile.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << pickUpFile << endl;
    }

    for (const auto& ln : lines) {
        outputFile << ln << '\n';
    }
    outputFile.close();
}
void PickUp::reservePickUp(string date, string productName, int count, string id) {

    int number = getLastLineNumber();

    ofstream file(pickUpFile);
    file << number << "," << date << "," << productName << "," << count << "," << id << ",No" << endl;
    file.close();
}

int PickUp::getLastLineNumber()
{
    ifstream file(pickUpFile, ios::in | ios::ate);
    string line;

    int count = 1;
    while (getline(file, line))
    {
        count++;
    }
    file.close();

    return count;
}