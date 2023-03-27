#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer
{
    public:
        Tokenizer();

        static std::vector<std::string> tokenize(std::string data, char seperator);
};

#endif /* TOKENIZER_H */