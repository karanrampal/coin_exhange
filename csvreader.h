#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>
#include "orderbookentry.h"

class CSVReader
{
    public:
        CSVReader();
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};

#endif /* CSVREADER_H */