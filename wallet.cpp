#include "wallet.h"
#include "tokenizer.h"
#include <iostream>

Wallet::Wallet() : contents()
{

}

void Wallet::insertCurrency(std::string type, double amount)
{
    if (amount < 0.0)
    {
        std::cerr << "Amount is negative!\n";
        throw std::exception{};
    }
    double balance;
    if (contents.count(type) == 0)
    {
        balance = 0.0;
    }
    else
    {
        balance = contents[type];
    }
    contents[type] += amount;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0.0)
    {
        return false;
    }
    if (contents.count(type) == 0)
    {
        return false;
    }
    else
    {
        if (containsCurrency(type, amount))
        {
            contents[type] -= amount;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (contents.count(type) == 0) return false;
    else return contents[type] >= amount;
}

bool Wallet::canFulfullOrder(const OrderBookEntry& obe)
{
    std::vector<std::string> tokens = Tokenizer::tokenize(obe.product, '/');
    if (obe.orderType == OrderBookType::ask)
    {
        std::cout << "Wallet::canFulfullOrder: " << tokens[0] << " : " << obe.amount << '\n';
        return containsCurrency(tokens[0], obe.amount);
    }
    else if (obe.orderType == OrderBookType::bid)
    {
        double amt = obe.amount * obe.price;
        std::cout << "Wallet::canFulfullOrder: " << tokens[1] << " : " << amt << '\n';
        return containsCurrency(tokens[1], amt);
    }
    return false;
}

std::string Wallet::toString()
{
    std::string content;
    for (std::pair<const std::string, double> p : contents)
    {
        content += p.first + " : " + std::to_string(p.second) + '\n';
    }
    return content;
}