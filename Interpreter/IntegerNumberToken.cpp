#include "IntegerNumberToken.h"
#include "MessageException.h"
#include "FloatNumberToken.h"
#include "StringToken.h"
#include <cmath>

IntegerNumberToken::IntegerNumberToken(const IntegerNumberToken& other) : DataToken(other), value(other.value)
{
}

DataToken* IntegerNumberToken::operator+(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        int res = this->getValue() + right->getValue();
        std::string alias = std::to_string(res);
        return new IntegerNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        float res = (float)this->getValue() + right->getValue();
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }
    if (StringToken* right = dynamic_cast<StringToken*>(&other)) {
        std::string res = std::to_string(this->getValue()) + right->getAlias();
        return new StringToken(res);
    }

    throw MessageException("An operator + for " + other.getAlias() + " is not exist");
}

DataToken* IntegerNumberToken::operator-(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        int res = this->getValue() - right->getValue();
        std::string alias = std::to_string(res);
        return new IntegerNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        float res = (float)this->getValue() - right->getValue();
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }

    throw MessageException("An operator - for " + other.getAlias() + " is not exist");
}

DataToken* IntegerNumberToken::operator*(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        int res = this->getValue() * right->getValue();
        std::string alias = std::to_string(res);
        return new IntegerNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        float res = (float)this->getValue() * right->getValue();
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }

    throw MessageException("An operator * for " + other.getAlias() + " is not exist");
}

DataToken* IntegerNumberToken::operator/(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        float res = (float)this->getValue() / (float)right->getValue();
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        float res = (float)this->getValue() / right->getValue();
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }

    throw MessageException("An operator / for " + other.getAlias() + " is not exist");

}

DataToken* IntegerNumberToken::pow(DataToken& pow) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&pow)) {
        int res = std::pow(this->getValue(), right->getValue());
        std::string alias = std::to_string(res);
        return new IntegerNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&pow)) {
        float res = std::pow(this->getValue(), right->getValue());
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }

    throw MessageException("An operator pow() for " + pow.getAlias() + " is not exist");
}

DataToken* IntegerNumberToken::abs() const
{
    int res = std::abs(this->getValue());
    std::string alias = std::to_string(res);
    return new IntegerNumberToken(alias, res);
}

DataToken* IntegerNumberToken::max(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        int res = std::max(this->getValue(), right->getValue());
        std::string alias = std::to_string(res);
        return new IntegerNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        float res = std::max((float)this->getValue(), right->getValue());
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }
    throw MessageException("An operator max() for " + other.getAlias() + " is not exist");
}

DataToken* IntegerNumberToken::min(DataToken& other) const
{
    if (IntegerNumberToken* right = dynamic_cast<IntegerNumberToken*>(&other)) {
        int res = std::min(this->getValue(), right->getValue());
        std::string alias = std::to_string(res);
        return new IntegerNumberToken(alias, res);
    }
    if (FloatNumberToken* right = dynamic_cast<FloatNumberToken*>(&other)) {
        float res = std::min((float)this->getValue(), right->getValue());
        std::string alias = std::to_string(res);
        return new FloatNumberToken(alias, res);
    }
    throw MessageException("An operator min() for " + other.getAlias() + " is not exist");

}
