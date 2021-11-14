#include <Token.h>

bool Token::operator==(const Token &other) const
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