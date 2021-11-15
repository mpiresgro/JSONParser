#include <gtest/gtest.h>
#include <Lexer.h>

TEST(LexerTests, StringValueNoSpaces)
{
    Lexer lexer("\"O Meu Nome e Foo\"");

    std::vector<Token> tokens;
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_TRUE(tokens[0] == Token("O Meu Nome e Foo"));
}

TEST(LexerTests, StringValueSpaces)
{
    Lexer lexer("    \"O Meu Nome e Foo\"     ");

    std::vector<Token> tokens;
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 1);
    ASSERT_TRUE(tokens[0] == Token("O Meu Nome e Foo"));
}

TEST(LexerTests, StringMultipleValueSpaces)
{
    Lexer lexer("    \"O Meu Nome e Foo\"  , \"O Meu Nome e Qwerty\"    ");

    std::vector<Token> tokens;
    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 3);
    ASSERT_TRUE(tokens[0] == Token("O Meu Nome e Foo"));
    ASSERT_TRUE(tokens[1].GetType() == Token::Type::Comma);
    ASSERT_TRUE(tokens[2] == Token("O Meu Nome e Qwerty"));
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

TEST(LexerTests, EmptyObject)
{
    Lexer lexer("{}");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 2);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBrace);
    ASSERT_EQ(tokens[1].GetType(), Token::Type::RightBrace);
}

TEST(LexerTests, ObjectWithNull)
{
    std::vector<Token> tokens;

    std::string test_string = "{\"foo\":null}";
    Lexer lexer(test_string);

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBrace);
    ASSERT_EQ(tokens[1], Token("foo"));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Colon);
    ASSERT_EQ(tokens[3], Token(nullptr));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBrace);
}

TEST(LexerTests, ObjectWithBoolean)
{
    std::vector<Token> tokens;

    std::string test_string = "{\"foo\":true}";
    Lexer lexer(test_string);

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBrace);
    ASSERT_EQ(tokens[1], Token("foo"));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Colon);
    ASSERT_EQ(tokens[3], Token(true));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBrace);
}

TEST(LexerTests, ObjectWithString)
{
    std::vector<Token> tokens;

    Lexer lexer("{\"foo\" : \"bar\" }");

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBrace);
    ASSERT_EQ(tokens[1], Token("foo"));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Colon);
    ASSERT_EQ(tokens[3], Token("bar"));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBrace);
}

TEST(LexerTests, ObjectWithNumber)
{
    std::vector<Token> tokens;

    Lexer lexer("{\"Foo\" : 28 }");

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBrace);
    ASSERT_EQ(tokens[1], Token("Foo"));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Colon);
    ASSERT_EQ(tokens[3], Token(28));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBrace);
}

TEST(LexerTests, ObjectWithArray)
{
    Lexer lexer("{\"Foo\" : [] }");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 6);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBrace);
    ASSERT_EQ(tokens[1], Token("Foo"));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Colon);
    ASSERT_EQ(tokens[3].GetType(), Token::Type::LeftBracket);
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBracket);
    ASSERT_EQ(tokens[5].GetType(), Token::Type::RightBrace);
}

TEST(LexerTests, EmptyArray)
{
    Lexer lexer("[]");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 2);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBracket);
    ASSERT_EQ(tokens[1].GetType(), Token::Type::RightBracket);
}

TEST(LexerTests, ArrayWithNumbers)
{
    Lexer lexer("[1, 2,     3,4   ]");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 9);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBracket);
    ASSERT_EQ(tokens[1], Token(1));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Comma);
    ASSERT_EQ(tokens[3], Token(2));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::Comma);
    ASSERT_EQ(tokens[5], Token(3));
    ASSERT_EQ(tokens[6].GetType(), Token::Type::Comma);
    ASSERT_EQ(tokens[7], Token(4));
    ASSERT_EQ(tokens[8].GetType(), Token::Type::RightBracket);
}


TEST(LexerTests, ArrayWitStrings)
{
    Lexer lexer("[\"Foo\" , \"Bar\" ]");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBracket);
    ASSERT_EQ(tokens[1], Token("Foo"));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Comma);
    ASSERT_EQ(tokens[3], Token("Bar"));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBracket);
}

TEST(LexerTests, ArrayWitBoolean)
{
    Lexer lexer("[ true ,            false ]");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBracket);
    ASSERT_EQ(tokens[1], Token(true));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Comma);
    ASSERT_EQ(tokens[3], Token(false));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBracket);
}

TEST(LexerTests, ArrayWitNull)
{
    Lexer lexer("[ null ,            null ]");
    std::vector<Token> tokens;

    tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].GetType(), Token::Type::LeftBracket);
    ASSERT_EQ(tokens[1], Token(nullptr));
    ASSERT_EQ(tokens[2].GetType(), Token::Type::Comma);
    ASSERT_EQ(tokens[3], Token(nullptr));
    ASSERT_EQ(tokens[4].GetType(), Token::Type::RightBracket);
}

