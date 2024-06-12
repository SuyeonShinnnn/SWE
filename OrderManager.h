#pragma once
#include "Order.h"
#include <vector>

class OrderManager {
private:
    vector<Order> orders;
    const string orderFile = "orders.txt";

public:
    OrderManager();
    ~OrderManager();
    void updateOrderStatus(const string& orderId, const string& newStatus);
    void showPendingOrders() const;
    void addOrder(const string& orderId, const string& product, const int count, const string& customerId, const string& status);
    void showOrders(const string& customerId) const;
    void saveOrders();
    void loadOrders();
};
