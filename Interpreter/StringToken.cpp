#include "StringToken.h"
#include "MessageException.h"
#include "FloatNumberToken.h"
#include "IntegerNumberToken.h"
StringToken::StringToken(const StringToken& other) : DataToken(other)
{
}
DataToken* StringToken::operator+(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        std::string res = this->getAlias() + std::to_string(right->getValue());
        return new StringToken(res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        std::string res = this->getAlias() + std::to_string(right->getValue());
        return new StringToken(res);
    }
    if (StringToken* right = dynamic_cast<StringToken*>(&other)) {
        std::string res = this->getAlias() + right->getAlias();
        return new StringToken(res);
    }

    throw MessageException("An operator for " + other.getAlias() + " is not exist");
}

DataToken* StringToken::operator-(DataToken& other) const
{
    throw MessageException("An operator - for " + other.getAlias() + " is not exist");
}

DataToken* StringToken::operator*(DataToken& other) const
{
    throw MessageException("An operator * for " + other.getAlias() + " is not exist");
}

DataToken* StringToken::operator/(DataToken& other) const
{
    throw MessageException("An operator / for " + other.getAlias() + " is not exist");
}

DataToken* StringToken::pow(DataToken& pow) const
{
    throw MessageException("An operator pow() for " + pow.getAlias() + " is not exist");
}

DataToken* StringToken::abs() const
{
    throw MessageException("An operator abs() for " + this->getAlias() + " is not exist");
}

DataToken* StringToken::max(DataToken& other) const
{
    throw MessageException("An operator max() for " + other.getAlias() + " is not exist");
}

DataToken* StringToken::min(DataToken& other) const
{
    throw MessageException("An operator min() for " + other.getAlias() + " is not exist");
}
