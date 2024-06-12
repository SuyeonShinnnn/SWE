#pragma once
#include "Review.h"
#include <vector>

class ReviewManager {
private:
    vector<Review> reviews;
    const string reviewFile = "review.txt";

public:
    ReviewManager();
    ~ReviewManager();
    void addReview(const string& orderId, const string& product, int score, const string& content);
    void showReviews() const;
    void saveReviews();
    void loadReviews();
};
