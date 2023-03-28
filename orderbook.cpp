#include "orderbook.h"
#include "csvreader.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string filename) : orders(CSVReader::readCSV(filename))
{

}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::map<std::string, bool> prodMap;
    for (OrderBookEntry& obe : orders)
    {
        prodMap[obe.product] = true;
    }
    std::vector<std::string> products;
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(
    OrderBookType type, std::string product, std::string timestamp
)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& obe : orders)
    {
        if ( (obe.orderType == type) && (obe.product == product) && (obe.timestamp == timestamp) )
        {
            orders_sub.push_back(obe);
        }
    }
    return orders_sub;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next = orders[0].timestamp;
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next = e.timestamp;
            break;
        }
    }

    return next;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& obe : orders)
    {
        if (obe.price > max) { max = obe.price;}
    }
    return max;
}

double OrderBook::getLowestPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (OrderBookEntry& obe : orders)
    {
        if (obe.price < min) { min = obe.price;}
    }
    return min;
}

void OrderBook::insertOrder(OrderBookEntry& obe)
{
    orders.push_back(obe);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTime);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry& a : asks)
    {
        for (OrderBookEntry& b : bids)
        {
            if (b.price >= a.price)
            {
                OrderBookEntry sale{a.price, 0.0, timestamp, product, OrderBookType::asksale};
                if (b.userName == "simuser")
                {
                    sale.orderType = OrderBookType::bidsale;
                    sale.userName = "simuser";
                }
                if (a.userName == "simuser")
                {
                    sale.orderType = OrderBookType::asksale;
                    sale.userName = "simuser";
                }
                if (b.amount >= a.amount)
                {
                    sale.amount = a.amount;
                    sales.push_back(sale);
                    b.amount = b.amount - a.amount;
                    break;
                }
                else
                {
                    sale.amount = b.amount;
                    sales.push_back(sale);
                    a.amount = a.amount - b.amount;
                    b.amount = 0.0;
                    continue;
                }
            }
        }
    }
    return sales;
}