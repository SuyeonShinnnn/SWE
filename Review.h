#pragma once
#include <string>
using namespace std;

class Review {
private:
    string orderId;
    string product;
    string content;
    string id;
    int score;

public:
    Review(string _orderId, string _product, int _score, string _content, string _id);
    string getOrderId() const;
    string getProduct() const;
    string getContent() const;
    string getId() const;
    void showReview() const;
    int getScore() const;
};
