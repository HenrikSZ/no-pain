#ifndef INPUT_H
#define INPUT_H


#include <string>
#include <fstream>


class Input {
public:
    virtual int getCurrentLineNumber() const = 0;
    virtual bool hasNext() const = 0;
    virtual void advance() = 0;
    virtual char getCurrentChar() const = 0;
};


class FileInput : public Input {
public:
    FileInput(std::string& filename);
    ~FileInput();
    
    int getCurrentLineNumber() const;
    bool hasNext() const;
    void advance();
    char getCurrentChar() const;

private:
    std::ifstream filestream;
    std::string currentLine;
    char currentChar;
    bool hasNextChar;
    bool nextCharAdvLineNumber;
    int pointer;
    int currentLineNumber;
};


class StringInput : public Input {
public:
    StringInput(std::string& input);
    
    int getCurrentLineNumber() const;
    bool hasNext() const;
    void advance();
    char getCurrentChar() const;

private:
    std::string input;
    int pointer;
    int currentLineNumber;
};


#endif
