#include <iostream>
#include <string> // std::string, std::stod
#include <vector>
#include "Token.h"

// -----------------------------------
// Constants
const char Invalid = 0;
const char QUOTE = '"';
const char COMMA = ',';
const char COLON = ':';
const char LEFT_BRACKET = '[';
const char RIGHT_BRACKET = ']';
const char LEFT_BRACE = '{';
const char RIGHT_BRACE = '}';
// -----------------------------------

class Lexer
{
public:
    Lexer(const std::string &input);
    ~Lexer() = default;

    std::vector<Token> GetTokens();

private:
    std::string strValue;

    bool LexString(std::string &input, Token& token);
    bool LexNumber(std::string &input, Token& token);
    bool LexBoolean(std::string &input, Token& token);
    bool LexNull(std::string &input, Token& token);
    bool LexJsonSyntax(std::string &input, Token& token);
};