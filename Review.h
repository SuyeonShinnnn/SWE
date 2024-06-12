#pragma once
#include <string>
using namespace std;

class Review {
private:
    string orderId;
    string product;
    string content;
    int score;

public:
    Review(string _orderId, string _product, int _score, string _content);
    string getOrderId() const;
    string getProduct() const;
    string getContent() const;
    void showReview() const;
    int getScore() const;
};
