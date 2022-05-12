#include "input.h"


FileInput::FileInput(std::string& filename) {
    filestream.open(filename);
    currentLineNumber = 1;
    nextCharAdvLineNumber = false;
    peeked = false;
    pointer = -1;

    advanceToNonEmptyLine();
}

FileInput::~FileInput() {
    filestream.close();
}

void FileInput::advanceToNonEmptyLine() {
    hasNextChar = false;
    while (std::getline(filestream, currentLine)) {
        if (currentLine.length() > 0) {
            hasNextChar = true;
            break;
        }
    }
}

char FileInput::getNextChar() {
    if (peeked) {
        peeked = false;
    } else {
        if (nextCharAdvLineNumber) {
            currentLineNumber++;
            nextCharAdvLineNumber = false;
        }

        pointer++;
        nextChar = currentLine[pointer];

        if (pointer + 1 >= currentLine.length()) {
            advanceToNonEmptyLine();

            pointer = -1;
            nextCharAdvLineNumber = true;
        }
    }

    return nextChar;
}

bool FileInput::hasNext() const {
    return peeked || hasNextChar;
}

char FileInput::peekNextChar() {
    if (!peeked) {
        nextChar = getNextChar();
        peeked = true;
    }

    return nextChar;
}

int FileInput::getCurrentLineNumber() const {
    return currentLineNumber;
}


StringInput::StringInput(const char* input) {
    this->input = std::string(input);
    peeked = false;
    pointer = -1;
}

StringInput::StringInput(std::string& input) {
    this->input = input;
    peeked = false;
    pointer = -1;
}

bool StringInput::hasNext() const {
    return peeked || pointer + 1 < input.length();
}

char StringInput::getNextChar() {
    if (peeked) {
        peeked = false;
        return nextChar;
    }
    
    if (hasNext()) {
        if (input[pointer] == '\n') {
            currentLineNumber++;
        }

        pointer++;
    }

    return input[pointer];
}

char StringInput::peekNextChar() {
    if (!peeked) {
        nextChar = getNextChar();
        peeked = true;
    }

    return nextChar;
}

int StringInput::getCurrentLineNumber() const {
    return currentLineNumber;
}
