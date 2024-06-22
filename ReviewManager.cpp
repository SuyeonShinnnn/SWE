#include "ReviewManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
ReviewManager::ReviewManager()
{
    loadReviews();
}
ReviewManager::~ReviewManager()
{

}

void ReviewManager::addReview(const string& orderId, const string& product, int score, const string& content, const string& id)
{
    reviews.emplace_back(orderId, product, score, content, id);
    saveReviews();
}

void ReviewManager::showReviews() const
{
    for (const auto& review : reviews) {
        review.showReview();
    }
}

void ReviewManager::saveReviews()
{
    ofstream file(reviewFile);
    for (const auto& review : reviews) {
        file << review.getOrderId() << "," << review.getProduct() << "," << review.getScore() << "," << review.getContent() << "," << review.getId() << endl;
    }
    file.close();
}

void ReviewManager::loadReviews()
{
    ifstream file(reviewFile);
    reviews.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string orderId, product, scoreStr, content, id;
        getline(ss, orderId, ',');
        getline(ss, product, ',');
        getline(ss, scoreStr, ',');
        getline(ss, content, ',');
        int score = stoi(scoreStr);
        getline(ss, id, ',');

        reviews.emplace_back(orderId, product, score, content, id);
    }
    file.close();
}
void ReviewManager::deleteReview(int number) {
    ifstream inputFile(reviewFile);
    if (!inputFile.is_open()) {
        cerr << "파일을 열 수 없습니다: " << reviewFile << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string orderId, product, scoreStr, content, id;
        getline(ss, orderId, ',');
        getline(ss, product, ',');
        getline(ss, scoreStr, ',');
        getline(ss, content, ',');
        getline(ss, id, ',');


        if (stoi(orderId) != number) {
            lines.push_back(line);
        }
        else {
            found = true;
        }
    }
    inputFile.close();

    if (!found) {
        cout << "해당 영수증 번호를 찾을 수 없습니다: " << number << endl;
        return;
    }


    ofstream outputFile(reviewFile, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "파일을 열 수 없습니다: " << reviewFile << endl;
        return;
    }

    for (const auto& ln : lines) {
        outputFile << ln << '\n';
    }
    outputFile.close();
}