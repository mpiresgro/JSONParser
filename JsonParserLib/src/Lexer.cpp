#include "Lexer.h"

Lexer::Lexer(const std::string &input) : strValue(input) {}

std::vector<Token> Lexer::GetTokens()
{
    std::vector<Token> tokens = {};

    Token token;

    while (strValue.size() != 0)
    {

        token = LexString(strValue);
        if (token.GetType() == Token::Type::String)
        {
            tokens.push_back(token);
            continue;
        }

        token = LexNumber(strValue);
        if (token.GetType() == Token::Type::Integer || token.GetType() == Token::Type::Double)
        {
            tokens.push_back(token);
            continue;
        }

        token = LexBoolean(strValue);
        if (token.GetType() == Token::Type::Boolean)
        {
            tokens.push_back(token);
            continue;
        }

        token = LexNull(strValue);
        if (token.GetType() == Token::Type::Null)
        {
            tokens.push_back(token);
            continue;
        }

        token = LexJsonSyntax(strValue);
        if (token.GetType() != Token::Type::Invalid)
        {
            tokens.push_back(token);
            continue;
        }

        if (token.GetType() == Token::Type::Invalid)
            // TODO: Define a custom exception
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
Token Lexer::LexString(std::string &input)
{

    if (input[0] != QUOTE)
        return Token();

    // remove first quote mark
    input.erase(0, 1);

    // find next quote mark
    std::size_t found = input.find_first_of(QUOTE);

    if (found != input.npos)
    {
        // get string within the quotes and remove string from input
        Token token(input.substr(0, found));
        input.erase(0, found + 1);
        return token;
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
Token Lexer::LexNumber(std::string &input)
{
    std::string number;

    // find next not whitespace char
    std::size_t found_non_space = input.find_first_not_of(' ');

    if (found_non_space != std::string::npos)
    {
        // remove leading whitespace
        input.erase(0, found_non_space);

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
            return Token();

        input.erase(0, i);

        std::size_t end = input.find_first_not_of(' ');
        if (end != std::string::npos)
            input.erase(0, end);

        std::size_t found_dot = number.find_first_of('.');

        if (found_dot != std::string::npos)
        {
            // Floating point number
            return Token(std::stod(number));
        }
        else
        {
            // Integer number
            return Token(std::stoi(number));
        }
    }
    return Token();
}

Token Lexer::LexBoolean(std::string &input)
{
    // find next not whitespace char
    std::size_t found_non_space = input.find_first_not_of(' ');
    if (found_non_space != std::string::npos)
    {
        // remove leading whitespace
        input.erase(0, found_non_space);

        if (input.substr(0, 4) == "true")
        {
            input.erase(0, 4);
            return Token(true);
        }

        if (input.substr(0, 5) == "false")
        {
            input.erase(0, 5);
            return Token(false);
        }
    }
    return Token();
}

Token Lexer::LexNull(std::string &input)
{
    // find next not whitespace char
    std::size_t found_non_space = input.find_first_not_of(' ');
    if (found_non_space != std::string::npos)
    {
        // remove leading whitespace
        input.erase(0, found_non_space);

        if (input.substr(0, 4) == "null")
        {
            input.erase(0, 4);
            return Token(nullptr);
        }
    }

    return Token();
}

Token Lexer::LexJsonSyntax(std::string &input)
{
    Token token; 
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
        input.erase(0, 1);

    return token;
    
}