#ifndef AUCTION_H
#define AUCTION_H

#include <string>
#include <unordered_set>
#include <chrono>

class Auction {
public:
    Auction();

    void setId(std::string currentId);
    std::string getId();

    void joinAuction();
    void startAuction(std::string productName, int cost, int durationMinutes);
    void endAuction(std::string productName);
    void saveAuctionResult(std::string productName, int finalBid, std::string winnerId);
    void showAuctionResults();
    bool showAuctionItems();
    bool hasActiveAuctions();

private:
    std::string currentId;
    std::unordered_set<std::string> participants;
    std::string productFile = "auction_products.txt";
    std::string productFile2 = "bids.txt";
    std::chrono::system_clock::time_point endTime;
    bool auctionEnded;
};

#endif 