#include "Review.h"
#include <iostream>

Review::Review(string _orderId, string _product, int _score, string _content)
    : orderId(_orderId), product(_product), score(_score), content(_content) {}

string Review::getOrderId() const
{
    return orderId;
}
string Review::getProduct() const
{
    return product;
}
int Review::getScore() const
{
    return score;
}
string Review::getContent() const
{
    return content;
}
void Review::showReview() const
{
    cout << "영수증 번호: " << orderId << ", 상품명: " << product
        << ", 별점: " << score << ", 내용: " << content << endl;
}
