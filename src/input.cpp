#include "input.h"


FileInput::FileInput(std::string& filename) {
    filestream.open(filename);
    currentLineNumber = 1;
    nextCharAdvLineNumber = false;
    pointer = -1;

    std::getline(filestream, currentLine);
    hasNextChar = currentLine.length() > 0;
}

FileInput::~FileInput() {
    filestream.close();
}

void FileInput::advance() {
    pointer++;
    currentChar = currentLine[pointer];

    if (nextCharAdvLineNumber) {
        currentLineNumber++;
        nextCharAdvLineNumber = false;
    }

    if (pointer + 1 >= currentLine.length()) {
        std::getline(filestream, currentLine);
        if (currentLine.length() == 0) {
            hasNextChar = false;
        }

        pointer = -1;
        nextCharAdvLineNumber = true;
    }
}

bool FileInput::hasNext() const {
    return hasNextChar;
}

char FileInput::getCurrentChar() const {
    return currentChar;
}

int FileInput::getCurrentLineNumber() const {
    return currentLineNumber;
}


StringInput::StringInput(std::string& input) {
    this->input = input;
    pointer = -1;
}

void StringInput::advance() {
    if (hasNext()) {
        if (input[pointer] == '\n') {
            currentLineNumber++;
        }

        pointer++;
    }
}

bool StringInput::hasNext() const {
    return pointer + 1 < input.length();
}

char StringInput::getCurrentChar() const {
    return input[pointer];
}

int StringInput::getCurrentLineNumber() const {
    return currentLineNumber;
}
