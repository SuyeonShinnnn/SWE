#include "Review.h"
#include <iostream>

Review::Review(string _orderId, string _product, int _score, string _content, string _id)
    : orderId(_orderId), product(_product), score(_score), content(_content), id(_id) {}

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
string Review::getId() const
{
    return id;
}
void Review::showReview() const
{
    cout << "�ֹ���ȣ: " << orderId << ", �ۼ��� : " << id << ", ��ǰ�� : " << product
        << ", ����: " << score << ", ����: " << content << endl;
}
