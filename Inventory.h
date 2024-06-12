#pragma once
#include "Product.h"
#include <vector>

class Inventory {
private:
    vector<Product> products;
    const string productFile = "products.txt";

public:
    Inventory();
    ~Inventory();
    void addProduct(const string& name, double price, int stock, const string& limitedFlag);
    double searchProductPrice(const string& search);
    double searchProductStock(const string& search);
    bool updateStock(const string& product, int quantity);
    bool showProducts() const;
    void showLimitedProducts() const;
    void saveProducts();
    void loadProducts();
};
