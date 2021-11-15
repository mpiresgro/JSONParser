#include "Lexer.h"

Lexer::Lexer(const std::string &input) : strValue(input) {}

std::vector<Token> Lexer::GetTokens()
{
    std::vector<Token> tokens = {};

    while (strValue.size() != 0)
    {

        // find next not whitespace char
        std::size_t found_non_space = strValue.find_first_not_of(SPACE);

        if (found_non_space != std::string::npos)
        {
            // remove leading whitespace
            strValue.erase(0, found_non_space);
        }
        else
        {
            break;
        }

        Token token;

        if (LexString(strValue, token))
        {
            tokens.push_back(token);
            continue;
        }

        if (LexNumber(strValue, token))
        {
            tokens.push_back(token);
            continue;
        }

        if (LexBoolean(strValue, token))
        {
            tokens.push_back(token);
            continue;
        }

        if (LexNull(strValue, token))
        {
            tokens.push_back(token);
            continue;
        }

        if (LexJsonSyntax(strValue, token))
        {
            tokens.push_back(token);
            continue;
        }

        // Should not get here!
        throw std::invalid_argument("Unexpected character!");
    }

    return tokens;
}

/*
Check if the first character is a quote.
If it is, iterate over the input string until you find an ending quote. 

If you don't find an initial quote, return None and the original list. 
If you find an initial quote and an ending quote, 
return the string within the quotes and the rest of the unchecked input string.
*/
bool Lexer::LexString(std::string &input, Token &token)
{

    if (input[0] != QUOTE)
        return false;

    // remove first quote mark
    input.erase(0, 1);

    // find next quote mark
    std::size_t found = input.find_first_of(QUOTE);

    if (found != input.npos)
    {
        // get string within the quotes and remove string from input
        token = Token(input.substr(0, found));
        input.erase(0, found + 1);
        return true;
    }
    else
    {
        throw std::invalid_argument("Expected end of string quote");
    }
}

/*
For the lex_number function, the gist will be to iterate over the input until you find
a character that cannot be part of a number. After finding a character that cannot be 
part of a number, either return a float or int if the characters 
you've accumulated number more than 0. 
Otherwise return None and the original string input.
*/
bool Lexer::LexNumber(std::string &input, Token &token)
{
    std::string number;
    std::size_t i;

    // TODO: change to find_last_not_of
    for (i = 0; i < input.size(); i++)
    {
        // find characters 0-9 - .
        bool isDigit = (input[i] >= 48 && input[i] <= 57);
        bool isSign = (input[i] == '.' || input[i] == '-');
        if (isDigit || isSign)
        {
            number.push_back(input[i]);
        }
        else
        {
            break;
        }
    }

    if (!number.size())
        return false;

    input.erase(0, i);

    std::size_t end = input.find_first_not_of(SPACE);
    if (end != std::string::npos)
        input.erase(0, end);

    std::size_t found_float_point = number.find_first_of(POINT);

    if (found_float_point != std::string::npos)
    {
        // Floating point number
        token = Token(std::stod(number));
    }
    else
    {
        // Integer number
        token = Token(std::stoi(number));
    }

    return true;
}

bool Lexer::LexBoolean(std::string &input, Token &token)
{

    if (input.substr(0, 4) == "true")
    {
        input.erase(0, 4);
        token = Token(true);
        return true;
    }
    else if (input.substr(0, 5) == "false")
    {
        input.erase(0, 5);
        token = Token(false);
        return true;
    }
    else
    {
        return false;
    }
}

bool Lexer::LexNull(std::string &input, Token &token)
{

    if (input.substr(0, 4) == "null")
    {
        input.erase(0, 4);
        token = Token(nullptr);
        return true;
    }

    return false;
}

bool Lexer::LexJsonSyntax(std::string &input, Token &token)
{
    switch (input[0])
    {
    case LEFT_BRACKET:
        token = Token(Token::Type::LeftBracket);
        break;
    case RIGHT_BRACKET:
        token = Token(Token::Type::RightBracket);
        break;
    case LEFT_BRACE:
        token = Token(Token::Type::LeftBrace);
        break;
    case RIGHT_BRACE:
        token = Token(Token::Type::RightBrace);
        break;
    case COMMA:
        token = Token(Token::Type::Comma);
        break;
    case COLON:
        token = Token(Token::Type::Colon);
        break;
    default:
        token = Token();
        break;
    }

    if (token.GetType() != Token::Type::Invalid)
    {
        input.erase(0, 1);
        return true;
    }

    return false;
}