//
//  NaturalLog.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/2/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <exception>
# include <math.h>
# include <iostream>
# include <algorithm>

# include "NaturalLog.hpp"
# include "Rational.hpp"
# include "Polynomial.hpp"

using namespace RationalC;
using namespace PolynomialC;

namespace NaturalLogC
{

std::ostream& operator << (std::ostream& os, const NaturalLog& rhs)
{
    if (rhs.coeff == 1) os << "ln(" << rhs.base << ")";
    else if (rhs.coeff == -1) os << "-ln(" << rhs.base << ")";
    else os << rhs.coeff << "ln(" << rhs.base << ")";
    return os;
}

NaturalLog::NaturalLog(): coeff(0), base(Polynomial({1}, {1})) {}

NaturalLog::NaturalLog(const Rational& coeff, const Polynomial& base): base(base), coeff(coeff) {}

NaturalLog::NaturalLog(const std::string& input)
{
    std::string coeff = input.substr(0, input.find("ln"));
    std::string inner = input.substr(input.find("ln") + 3);
    inner.erase(std::remove(inner.begin(), inner.end(), ')'), inner.end());
    if (coeff == "") this->coeff = 1;
    else this->coeff = Rational(coeff);
    if (inner == "") throw std::invalid_argument("Natural log cannot be empty");
    else this->base = Polynomial(inner);
}

NaturalLog::NaturalLog(const NaturalLog& rhs): base(rhs.base), coeff(rhs.coeff) {}

NaturalLog& NaturalLog::operator = (const NaturalLog& rhs)
{
    if (&rhs != this)
    {
        this->base = rhs.base;
        this->coeff = rhs.coeff;
    }
    return *this;
}

std::string NaturalLog::display() const
{
    std::string result = "";
    if (this->coeff == 1) result = "ln(" + this->base.display() + ")";
    else if (this->coeff == -1) result = "-ln(" + this->base.display() + ")";
    else result = this->coeff.display() + "ln(" + this->base.display() + ")";
    return result;
}

float NaturalLog::evaluate(float x) const
{
    float result = this->coeff.evaluate() * log(this->base.evaluate(x));
    return result;
}

}
