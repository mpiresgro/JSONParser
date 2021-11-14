#include <string> 

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

    bool operator==(const Token &other) const;

private:
    std::string StringValue;
    int IntegerValue;
    double DoubleValue;
    bool BooleanValue;

    Type type;
};