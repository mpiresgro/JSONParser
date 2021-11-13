#include <iostream>
#include <string>     // std::string, std::stod
#include <vector>

class Token
{
public:
    enum class Type
    {
        Invalid,
        String,
        Integer,
        Double,
    };

    Token() : type(Type::Invalid){};
    Token(std::string Value) : StringValue(Value), type(Type::String){};
    Token(int Value) : IntegerValue(Value), type(Type::Integer){};
    Token(double Value) : DoubleValue(Value), type(Type::Double){};

    Type GetType() const { return type; }

    bool operator==(const Token &other) const
    {
        if (GetType() != other.GetType())
        {
            return false;
        }
        else
        {
            switch (GetType())
            {
            case Type::String:
                return StringValue == other.StringValue;
            case Type::Integer:
                return IntegerValue == other.IntegerValue;
            case Type::Double:
                return DoubleValue == other.DoubleValue;
            default:
                break;
            }

            return false;
        }
    }

private:
    std::string StringValue;
    int IntegerValue;
    double DoubleValue;

    Type type;
};

class Lexer
{
public:
    Lexer(const std::string &input);
    ~Lexer() = default;

    std::vector<Token> GetTokens();

private:
    std::string strValue;

    Token LexString(std::string &input);
    Token LexNumber(std::string &input);
};