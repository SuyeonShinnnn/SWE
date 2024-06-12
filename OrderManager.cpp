#include "OrderManager.h"
#include <fstream>
#include <sstream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

OrderManager::OrderManager() {
    loadOrders();
}
OrderManager::~OrderManager() {
    saveOrders();
}
void OrderManager::updateOrderStatus(const string& orderId, const string& newStatus) {
    for (auto& order : orders) {
        if (order.getOrderId() == orderId) {
            order.setStatus(newStatus);
            saveOrders();
            return;
        }
    }
}
void OrderManager::showPendingOrders() const {
    for (const auto& order : orders) {
        if (order.getStatus() == "¹ß¼ÛÀü") {
            order.showOrder();
        }
    }
}

void OrderManager::addOrder(const string& orderId, const string& product, const int count, const string& customerId, const string& status) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    orders.emplace_back(orderId, product, count, customerId, status, date);
    saveOrders();
}

void OrderManager::showOrders(const string& customerId) const {
    for (const auto& order : orders) {
        if (order.getCustomerId() == customerId) {
            order.showOrder();
        }
    }
}

void OrderManager::saveOrders() {
    ofstream file(orderFile);
    for (const auto& order : orders) {
        file << order.getOrderId() << "," << order.getProduct() << "," << order.getCount() << "," << order.getCustomerId() << "," << order.getStatus() << "," << order.getDate() << endl;
    }
    file.close();
}

void OrderManager::loadOrders() {
    ifstream file(orderFile);
    orders.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string orderId, product, customerId, status, date;
        string countStr;

        getline(ss, orderId, ',');
        getline(ss, product, ',');
        getline(ss, countStr, ',');
        int count = stoi(countStr);
        getline(ss, customerId, ',');
        getline(ss, status, ',');
        getline(ss, date, ',');
        orders.emplace_back(orderId, product, count, customerId, status, date);
    }

    file.close();
}