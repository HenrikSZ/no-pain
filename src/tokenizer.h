#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <fstream>

class Tokenizer {
    private:
    std::ifstream m_inputFile;

    Tokenizer(std::string& filename);
    ~Tokenizer();
};

#endif
