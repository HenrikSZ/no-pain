#ifndef INPUT_H
#define INPUT_H


#include <string>
#include <fstream>


class Input {
public:
    virtual int getCurrentLineNumber() const = 0;
    virtual bool hasNext() const = 0;
    virtual char getNextChar() = 0;
    virtual char peekNextChar() = 0;
};


class FileInput : public Input {
public:
    FileInput(std::string& filename);
    ~FileInput();
    
    int getCurrentLineNumber() const;
    bool hasNext() const;
    char getNextChar();
    char peekNextChar();

private:
    void advanceToNonEmptyLine();

    std::ifstream filestream;
    std::string currentLine;
    char nextChar;
    bool peeked;
    bool hasNextChar;
    bool nextCharAdvLineNumber;
    int pointer;
    int currentLineNumber;
};


class StringInput : public Input {
public:
    StringInput(const char* input);
    StringInput(std::string& input);
    
    int getCurrentLineNumber() const;
    bool hasNext() const;
    char getNextChar();
    char peekNextChar();

private:
    std::string input;
    bool peeked;
    char nextChar;
    int pointer;
    int currentLineNumber;
};


#endif
