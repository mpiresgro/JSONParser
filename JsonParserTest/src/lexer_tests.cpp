#include <gtest/gtest.h>
#include <Lexer.h>

TEST(LexerTests, String)
{
    Lexer lexer("\"O Meu Nome e Mauro\"");

    std::vector<Token> tokens;
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0], Token("O Meu Nome e Mauro"));
}


TEST(LexerTests, IntegerNumber)
{
    Lexer lexer("123");

    std::vector<Token> tokens;
    
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0], Token(123));
}

TEST(LexerTests, DoubleNumber)
{
    Lexer lexer("  123.345   5");

    std::vector<Token> tokens;
    
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens[0], Token(123.345));
    ASSERT_EQ(tokens[1], Token(5));
}