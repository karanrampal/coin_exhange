#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H

#include <string>

enum class OrderBookType{bid, ask, unknown, bidsale, asksale};

class OrderBookEntry
{
    public:
        OrderBookEntry(
            double _price,
            double _amount,
            std::string _timestamp,
            std::string _product,
            OrderBookType _orderType,
            std::string userName = "dataset"
        );
        
        static OrderBookType stringToOrderBookType(std::string s);
        static bool compareByTime(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.timestamp > e2.timestamp;
        }
        static bool compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        static bool compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string userName;
};

#endif /* ORDERBOOKENTRY_H */