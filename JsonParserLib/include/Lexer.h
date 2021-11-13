#include <iostream>
#include <string> // std::string, std::stod
#include <vector>

const char Invalid = 0;
const char QUOTE = '"';
const char COMMA = ',';
const char COLON = ':';
const char LEFT_BRACKET = '[';
const char RIGHT_BRACKET = ']';
const char LEFT_BRACE = '{';
const char RIGHT_BRACE = '}';


class Token
{
public:

    enum class Type
    {
        // Values
        Invalid,
        String,
        Integer,
        Double,
        Boolean,
        Null,
        // Syntax
        Comma, 
        Colon, 
        LeftBracket, 
        RightBracket, 
        LeftBrace, 
        RightBrace, 
    };

    Token() : type(Type::Invalid){};
    Token(const char *Value) : StringValue(std::string(Value)), type(Type::String){};
    Token(std::string Value) : StringValue(Value), type(Type::String){};
    Token(int Value) : IntegerValue(Value), type(Type::Integer){};
    Token(double Value) : DoubleValue(Value), type(Type::Double){};
    Token(bool Value) : BooleanValue(Value), type(Type::Boolean){};
    Token(std::nullptr_t) : type(Type::Null){};

    Token(Type Type_) : type(Type_){};

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
            case Type::Null:
                return true;
            case Type::String:
                return StringValue == other.StringValue;
            case Type::Integer:
                return IntegerValue == other.IntegerValue;
            case Type::Double:
                return DoubleValue == other.DoubleValue;
            case Type::Boolean:
                return BooleanValue == other.BooleanValue;
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
    bool BooleanValue;

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
    Token LexBoolean(std::string &input);
    Token LexNull(std::string &input);
    Token LexJsonSyntax(std::string &input);
};