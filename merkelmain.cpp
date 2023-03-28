#include <iostream>
#include <iomanip>
#include <ctype.h>
#include "merkelmain.h"
#include "tokenizer.h"
#include <limits>

MerkelMain::MerkelMain() : currentTime(""), run(true), wallet()
{

}

void MerkelMain::start()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10.0);
    while (run)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    std::cout << "\n***************************\n";
    std::cout << "|Menu:" << std::setw(22) << "|\n";
    std::cout << "| 1: Print help" << std::setw(13) << "|\n";
    std::cout << "| 2: Print exchange stats" << std::setw(3) << "|\n";
    std::cout << "| 3: Place an ask" << std::setw(11) << "|\n";
    std::cout << "| 4: Place a bid" << std::setw(12) << "|\n";
    std::cout << "| 5: Print wallet" << std::setw(11) << "|\n";
    std::cout << "| 6: Continue" << std::setw(15) << "|\n";
    std::cout << "| 7: Exit" << std::setw(19) << "|\n";
    std::cout << "***************************\n";
    std::cout << "Current time is: " << currentTime << '\n';
}

void MerkelMain::printHelp()
{
    std::cout << "\nHelp: choose options from the menu and follow the on screen instructions.\n";
}

void MerkelMain::printMarketStats()
{
    std::cout << "\nExchange stats are as follows:\n";

    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << '\n';
        std::vector<OrderBookEntry> entries = orderBook.getOrders(
            OrderBookType::ask, p, currentTime
        );
        std::cout << "Asks seen: " << entries.size() << '\n';
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << '\n';
        std::cout << "Min ask: " << OrderBook::getLowestPrice(entries) << '\n';
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "\nPlease place an ask below:\n";
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> ask = Tokenizer::tokenize(line, ',');
    OrderBookEntry obe = stringsToOBE(ask, OrderBookType::ask);
    if (wallet.canFulfullOrder(obe))
    {
        std::cout << "Order looks good!\n";
        orderBook.insertOrder(obe);
    }
    else
    {
        std::cout << "Insufficient funds!\n";
    }
}

void MerkelMain::enterBid()
{
    std::cout << "\nPlease place a bid below:\n";
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> bid = Tokenizer::tokenize(line, ',');
    OrderBookEntry obe = stringsToOBE(bid, OrderBookType::bid);
    if (wallet.canFulfullOrder(obe))
    {
        std::cout << "Order looks good!\n";
        orderBook.insertOrder(obe);
    }
    else
    {
        std::cout << "Insufficient funds!\n";
    }
}

void MerkelMain::printWallet()
{
    std::cout << "\nWallet contents are as follows:\n";
    std::cout << wallet.toString();
}

void MerkelMain::gotoNextTimeFrame()
{
    std::cout << "\nContinue to next time frame.\n";
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "Matching..." << p << '\n';
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << '\n';
            if (sale.userName == "simuser")
            {
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    std::cout << "Type in your choice (1 - 7): ";
    int userOption{ 0 };
    std::string line;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch(const std::exception& e)
    {
        std::cerr << "MerkelMain::getUserOption: Bad Input: " << e.what() << '\n';
    }
    std::cout << "You chose: " << line << '\n';
    return userOption;
}

void MerkelMain::quitting()
{
    std::cout << "Exiting programme!\n";
    run = false;
}

void MerkelMain::processUserOption(int userOption)
{
    switch (userOption)
    {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterAsk();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotoNextTimeFrame();
            break;
        case 7:
            quitting();
            break;
        default:
            std::cout << "\nUnrecognized option!\n";
    }
}

OrderBookEntry MerkelMain::stringsToOBE(std::vector<std::string> tokens, OrderBookType orderType)
{
    if (tokens.size() != 3)
    {
        std::cerr << "MerkelMain::stringsToOBE: Invalid entry!\n";
        throw std::exception{};
    }
    double price, amount;
    try
    {
        price = std::stod(tokens[1]);
        amount = std::stod(tokens[2]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "MerkelMain::stringsToOBE: Bad float: " << e.what() << '\n';
        throw std::exception{};
    }
    OrderBookEntry obe{price, amount, currentTime, tokens[0], orderType, "simuser"};
    return obe;
}