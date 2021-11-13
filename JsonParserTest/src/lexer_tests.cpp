#include <gtest/gtest.h>
#include <Lexer.h>

TEST(LexerTests, StringValue)
{
    Lexer lexer("\"O Meu Nome e Mauro\"");

    std::vector<Token> tokens;
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_TRUE(tokens[0] == Token("O Meu Nome e Mauro"));
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

TEST(LexerTests, BooleanValue)
{
    Lexer lexer("  true   false");

    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens[0], Token(true));
    ASSERT_EQ(tokens[1], Token(false));
}

TEST(LexerTests, NullValue)
{
    Lexer lexer("null null      null");

    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0], Token(nullptr));
    ASSERT_EQ(tokens[1], Token(nullptr));
    ASSERT_EQ(tokens[2], Token(nullptr));
}