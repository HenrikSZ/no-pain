#ifndef INPUT_H
#define INPUT_H


#include <string>
#include <fstream>


/**
 * @brief Abstract class for inputs to the tokenizer. 
 * 
 */
class Input {
public:
    /**
     * @brief Get the line number of the currently peeked/retrieved character.
     * 
     * @return int the current line number.
     */
    virtual int getCurrentLineNumber() const = 0;

    /**
     * @brief Indicate whether there is another character available to retrieve
     * with a call to getNextChar.
     * 
     * @return true there is another character to retrieve.
     * @return false there are no more characters available (end of file).
     */
    virtual bool hasNext() const = 0;

    /**
     * @brief Get the next characater.
     * 
     * @return char the next character, which is the same as the peeked one
     * (if it has been peeked).
     */
    virtual char getNextChar() = 0;
    
    /**
     * @brief Peeks the next character. This means the pointer is not advanced
     * yet, but the next character is provided upfront.
     * 
     * @return char the peeked character.
     */
    virtual char peekNextChar() = 0;
};


class FileInput : public Input {
public:
    /**
     * @brief Construct a new File Input from a file with name <filename>.
     * 
     * @param filename the filename of the file to open.
     */
    FileInput(std::string& filename);

    /**
     * @brief Destroy the File Input object.
     * 
     */
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
    /**
     * @brief Construct a new StringInput from a C style string.
     * 
     * @param input the input as C style string.
     */
    StringInput(const char* input);

    /**
     * @brief Construct a new StringInput from a C++ style string.
     * 
     * @param input the input as C++ style string.
     */
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
