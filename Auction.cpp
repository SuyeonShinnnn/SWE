#include "Auction.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <unordered_map>

using namespace std;

Auction::Auction() : auctionEnded(false) {}

void Auction::setId(string currentId) {
    this->currentId = currentId;
}

string Auction::getId() {
    return currentId;
}

void Auction::joinAuction() {
    string productName;

    cout << "��ſ� ������ ��ǰ���� �Է����ּ���." << endl << " >> ";
    cin >> productName;

    string currentUserId = getId();

    unordered_set<string> participants;
    int highestBid = numeric_limits<int>::min();
    bool found = false;

    ifstream file(productFile2);
    if (!file.is_open()) {
        cerr << "Error opening file: " << productFile2 << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, userId;
        int bid;

        if (getline(ss, name, ',') && ss >> bid && ss.ignore() && getline(ss, userId)) {
            if (name == productName) {
                if (bid > highestBid) {
                    highestBid = bid;
                    found = true;
                }
                participants.insert(userId);
            }
        }
    }
    file.close();

    if (participants.find(currentUserId) != participants.end()) {
        cout << "�̹� ��ſ� �����߽��ϴ�. ��Ŵ� �� �ѹ��� ���� �����մϴ�." << endl;
        cout << "���� �ְ� : " << highestBid << "��" << endl;
        return;
    }
    else {
        cout << "��ſ� �������� �ʾҽ��ϴ�. ������ �����մϴ�." << endl;
    }

    if (found) {
        int cost;
        cout << "���� " << productName << "�� �ְ� ������: " << highestBid << "�Դϴ�." << endl;
        cout << "������ ������ �Է����ּ���: " << endl << ">> ";
        cin >> cost;

        if (highestBid < cost) {
            ofstream file2(productFile2, ios::app);
            if (file2.is_open()) {
                file2 << productName << "," << cost << "," << currentUserId << endl;
                file2.close();
            }
            else {
                cerr << "Error opening file: " << productFile2 << endl;
            }
        }
        else {
            cout << "�ְ� ���������� �Է��Ͻ� �ݾ��� �۽��ϴ�. �ٽ� ��ſ� �������ּ���." << endl;
        }
    }
    else {
        cout << "��ǰ�� " << productName << "�� ���� ���� ����� �����ϴ�." << endl;
    }
}

void Auction::startAuction(string productName, int cost, int durationMinutes) {
    ofstream file(productFile);
    if (file.is_open()) {
        file << productName << "," << cost << endl;
        file.close();
    }
    else {
        cerr << "Error opening file: " << productFile << endl;
    }

    ofstream file2(productFile2);
    if (file2.is_open()) {
        file2 << productName << "," << cost << ",NONE" << endl;
        file2.close();
    }
    else {
        cerr << "Error opening file: " << productFile2 << endl;
    }
}

void Auction::endAuction(string productName) {
    ifstream file(productFile2);
    int highestBid = -1;
    string winnerId = "NONE";

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, userId;
            int bid;

            if (getline(ss, name, ',') && ss >> bid && ss.ignore() && getline(ss, userId)) {
                if (name == productName && bid > highestBid) {
                    highestBid = bid;
                    winnerId = userId;
                }
            }
        }
        file.close();
    }

    saveAuctionResult(productName, highestBid, winnerId);

    ofstream clearFile1(productFile, ofstream::out | ofstream::trunc);
    ofstream clearFile2(productFile2, ofstream::out | ofstream::trunc);
}

void Auction::saveAuctionResult(string productName, int finalBid, string winnerId) {
    ofstream resultFile("auctionResults.txt", ios::app);
    if (resultFile.is_open()) {
        resultFile << "��ǰ��: " << productName << ", ���� ������: " << finalBid << ", ������ ID: " << winnerId << endl;
        resultFile.close();
    }
    else {
        cerr << "Error opening file: auctionResults.txt" << endl;
    }
}

void Auction::showAuctionResults() {
    ifstream resultFile("auctionResults.txt");
    if (resultFile.is_open()) {
        cout << "==== ���� ��� ��� ====" << endl;
        string line;
        while (getline(resultFile, line)) {
            cout << line << endl;
        }
        resultFile.close();
    }
    else {
        cerr << "Error opening file: auctionResults.txt" << endl;
    }
}
bool Auction::showAuctionItems() {
    ifstream file(productFile2);
    if (!file.is_open()) {
        cerr << "Error opening file: " << productFile2 << endl;
        return false;
    }

    unordered_map<string, int> highestBids;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int cost;
        string userId;

        if (getline(ss, name, ',') && ss >> cost && ss.ignore() && getline(ss, userId)) {
            if (highestBids.find(name) == highestBids.end() || highestBids[name] < cost) {
                highestBids[name] = cost;
            }
        }
        else {
            cout << "���� �б� ����" << endl;
        }
    }
    file.close();

    if (highestBids.empty()) {
        cout << "���� ��ſ� ���� ���� ��ǰ�� �����ϴ�." << endl;
        return false;
    }

    for (const auto& bid : highestBids) {
        cout << bid.first << "�� ���� �ְ� ������: " << bid.second << "�Դϴ�" << endl;
    }

    return true;
}

bool Auction::hasActiveAuctions() {
    ifstream file(productFile2);
    if (!file.is_open()) {
        cerr << "Error opening file: " << productFile2 << endl;
        return false;
    }

    string line;
    bool hasItems = false;
    while (getline(file, line)) {
        hasItems = true;
        break;
    }
    file.close();
    return hasItems;
}
