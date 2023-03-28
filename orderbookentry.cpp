#include "orderbookentry.h"

OrderBookEntry::OrderBookEntry(
    double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _orderType,
    std::string _userName
) : price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    orderType(_orderType),
    userName(_userName)
{

}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    else if (s == "bid")
    {
        return OrderBookType::bid;
    }
    else if (s == "asksale")
    {
        return OrderBookType::asksale;
    }
    else if (s == "bidsale")
    {
        return OrderBookType::bidsale;
    }
    else
    {
        return OrderBookType::unknown;
    }
}