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

    cout << "경매에 참여할 상품명을 입력해주세요." << endl << " >> ";
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
        cout << "이미 경매에 참여했습니다. 경매는 딱 한번만 참여 가능합니다." << endl;
        cout << "현재 최고가 : " << highestBid << "원" << endl;
        return;
    }
    else {
        cout << "경매에 참여하지 않았습니다. 참여가 가능합니다." << endl;
    }

    if (found) {
        int cost;
        cout << "현재 " << productName << "의 최고 입찰가: " << highestBid << "입니다." << endl;
        cout << "입찰할 가격을 입력해주세요: " << endl << ">> ";
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
            cout << "최고 입찰가보다 입력하신 금액이 작습니다. 다시 경매에 참여해주세요." << endl;
        }
    }
    else {
        cout << "상품명 " << productName << "에 대한 입찰 기록이 없습니다." << endl;
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
        resultFile << "상품명: " << productName << ", 최종 입찰가: " << finalBid << ", 낙찰자 ID: " << winnerId << endl;
        resultFile.close();
    }
    else {
        cerr << "Error opening file: auctionResults.txt" << endl;
    }
}

void Auction::showAuctionResults() {
    ifstream resultFile("auctionResults.txt");
    if (resultFile.is_open()) {
        cout << "==== 역대 경매 결과 ====" << endl;
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
            cout << "파일 읽기 오류" << endl;
        }
    }
    file.close();

    if (highestBids.empty()) {
        cout << "현재 경매에 참여 중인 상품이 없습니다." << endl;
        return false;
    }

    for (const auto& bid : highestBids) {
        cout << bid.first << "의 현재 최고 입찰가: " << bid.second << "입니다" << endl;
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
