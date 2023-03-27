#ifndef MERKELMAIN_H
#define MERKELMAIN_H

#include <vector>
#include "orderbook.h"
#include "orderbookentry.h"
#include "wallet.h"

class MerkelMain
{
    public:
        MerkelMain();
        /**Call this to start the simulation*/
        void start();
    private:
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
        void quitting();
        int getUserOption();
        void processUserOption(int userOption);
        OrderBookEntry stringsToOBE(std::vector<std::string> tokens, OrderBookType orderType);

        std::string currentTime;
        OrderBook orderBook{"data/databook.csv"};
        bool run;
        Wallet wallet;
};

#endif /* MERKELMAIN_H */