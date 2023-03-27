#include "tokenizer.h"

Tokenizer::Tokenizer()
{

}

std::vector<std::string> Tokenizer::tokenize(std::string data, char seperator)
{
    std::vector<std::string> tokens;
    unsigned int start = 0, i = 0;
    for (; i < data.size(); ++i)
    {
        if ( (i > start) && (data[i] == seperator) )
        {
            tokens.push_back(data.substr(start, i - start));
            start = i + 1;
        }
    }
    tokens.push_back(data.substr(start, i - start));

    return tokens;
}