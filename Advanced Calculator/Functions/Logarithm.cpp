//
//  Logarithm.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/1/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include "Logarithm.hpp"
# include "Rational.hpp"
# include "Polynomial.hpp"

# include <iostream>
# include <math.h>
# include <exception>

using namespace RationalC;
using namespace PolynomialC;

namespace LogarithmC
{

std::ostream& operator << (std::ostream& os, const Logarithm& rhs)
{
    if (rhs.coeff == 1) os << "log(" << rhs.base << ")";
    else if (rhs.coeff == -1) os << "-log(" << rhs.base << ")";
    else os << rhs.coeff << "log(" << rhs.base << ")";
    return os;
}

Logarithm::Logarithm(): coeff(0), base(Polynomial({1}, {1})) {}

Logarithm::Logarithm(const std::string& input)
{
    std::string coeff = input.substr(0, input.find("log"));
    std::string inner = input.substr(input.find("log") + 4);
    inner.erase(std::remove(inner.begin(), inner.end(), ')'), inner.end());
    if (coeff == "") this->coeff = 1;
    else this->coeff = Rational(coeff);
    if (inner == "") throw std::invalid_argument("Log cannot be empty");
    else this->base = Polynomial(inner);
}

Logarithm::Logarithm(const Rational& coeff, const Polynomial& base): base(base), coeff(coeff) {}

Logarithm::Logarithm(const Logarithm& rhs): base(rhs.base), coeff(rhs.coeff) {}

Logarithm& Logarithm::operator = (const Logarithm& rhs)
{
    if (&rhs != this)
    {
        this->base = rhs.base;
        this->coeff = rhs.coeff;
    }
    return *this;
}

float Logarithm::evaluate(float x) const
{
    float result = this->coeff.evaluate() * log10(this->base.evaluate(x));
    return result;
}

}
