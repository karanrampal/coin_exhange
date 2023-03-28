#include <iostream>
#include <fstream>
#include "csvreader.h"
#include "tokenizer.h"

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile)
{
    std::ifstream csvFileStream{csvFile};
    std::string line;
    std::vector<OrderBookEntry> entries;

    if (csvFileStream.is_open())
    {
        std::cout << "File opened successfully!\n";
        while(std::getline(csvFileStream, line))
        {
            std::vector<std::string> tokens = Tokenizer::tokenize(line, ',');
            try
            {
                OrderBookEntry obe = stringsToOBE(tokens);
                entries.push_back(obe);
            }
            catch(const std::exception& e)
            {
                std::cerr << "CSVReader::readCSV: " << e.what() << '\n';
            }
        }
        csvFileStream.close();
    }
    else
    {
        std::cout <<"CSVReader::readCSV: File could not open!\n";
    }
    
    std::cout << "Read " << entries.size() << " entries.\n";
    return entries;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    if (tokens.size() != 5)
    {
        std::cerr << "CSVReader::stringsToOBE: Bad line!\n";
        throw std::exception{};
    }
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4 ]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "CSVReader::stringsToOBE: Bad float: " << e.what() << '\n';
        throw;
    }

    OrderBookEntry obe{
        price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])
    };
    
    return obe;
}