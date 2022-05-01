#include "tokenizer.h"

Tokenizer::Tokenizer(std::string& filename) {
    this->m_inputFile.open(filename);
}

Tokenizer::~Tokenizer() {
    this->m_inputFile.close();
}

