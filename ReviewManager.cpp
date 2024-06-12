#include "ReviewManager.h"
#include <fstream>
#include <sstream>

ReviewManager::ReviewManager()
{
    loadReviews();
}
ReviewManager::~ReviewManager() 
{
    saveReviews();
}

void ReviewManager::addReview(const string& orderId, const string& product, int score, const string& content)
{
    reviews.emplace_back(orderId, product, score, content);
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
        file << review.getOrderId() << "," << review.getProduct() << "," << review.getScore() << "," << review.getContent() << endl;
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
        string orderId, product, scoreStr, content;
        getline(ss, orderId, ',');
        getline(ss, product, ',');
        getline(ss, scoreStr, ',');
        getline(ss, content, ',');
        int score = stoi(scoreStr);
        reviews.emplace_back(orderId, product, score, content);
    }
    file.close();
}