#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <map>
#include "orderbookentry.h"

class Wallet
{
    public:
        Wallet();
        void insertCurrency(std::string type, double amount);
        bool removeCurrency(std::string type, double amount);
        
        /** Check if wallet contains the amount of currency or more*/
        bool containsCurrency(std::string type, double amount);

        /** Check if order can be fulfilled */
        bool canFulfullOrder(const OrderBookEntry& obe);

        /** Update the contents of the wallet*/
        void processSale(OrderBookEntry& sale);
        std::string toString();

    private:
        std::map<std::string, double> contents;
};

#endif /* WALLET_H */