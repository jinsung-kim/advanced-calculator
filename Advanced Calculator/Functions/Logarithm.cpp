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
    std::string result = "";
    if (rhs.oneOver == 0)
    {
        if (rhs.coeff == 1) result = "log(" + rhs.base.display() + ")";
        else if (rhs.coeff == -1) result = "-log(" + rhs.base.display() + ")";
        else result = rhs.coeff.display() + "log(" + rhs.base.display() + ")";
    }
    else
    {
        if (rhs.coeff == 1) result = rhs.oneOver.displayWithNegative() + "/log(" + rhs.base.display() + ")";
        else if (rhs.coeff == -1) result = rhs.oneOver.displayWithNegative() + "/-log(" + rhs.base.display() + ")";
        else result = rhs.oneOver.displayWithNegative() + "/" + rhs.coeff.displayWithNegative() + "log(" + rhs.base.display() + ")";
    }
    os << result;
    return os;
}

Logarithm::Logarithm(): coeff(0), base(Polynomial({1}, {1})) {}

Logarithm::Logarithm(const std::string& input)
{
    if (input.find("/(") != std::string::npos)
    {
        std::string overOne = input.substr(0, input.find("/"));
        std::string coeff = input.substr(input.find("/") + 2, input.find("log") - 3);
        std::string inner = input.substr(input.find("log") + 4);
        inner.erase(std::remove(inner.begin(), inner.end(), ')'), inner.end());
        if (overOne == "") throw std::invalid_argument("Numerator is empty");
        else this->oneOver = Rational(overOne);
        if (coeff == "") this->coeff = 1;
        else this->coeff = Rational(coeff);
        if (inner == "") throw std::invalid_argument("Log cannot be empty");
        else this->base = Polynomial(inner);
    }
    else
    {
        std::string coeff = input.substr(0, input.find("log"));
        std::string inner = input.substr(input.find("log") + 4);
        inner.erase(std::remove(inner.begin(), inner.end(), ')'), inner.end());
        this->oneOver = 0;
        if (coeff == "") this->coeff = 1;
        else this->coeff = Rational(coeff);
        if (inner == "") throw std::invalid_argument("Log cannot be empty");
        else this->base = Polynomial(inner);
    }
}

Logarithm::Logarithm(const Rational& coeff, const Polynomial& base, const Rational& oneOver):
base(base), coeff(coeff), oneOver(oneOver) {}

Logarithm::Logarithm(const Logarithm& rhs): base(rhs.base), coeff(rhs.coeff), oneOver(rhs.oneOver) {}

Logarithm& Logarithm::operator = (const Logarithm& rhs)
{
    if (&rhs != this)
    {
        this->base = rhs.base;
        this->coeff = rhs.coeff;
        this->oneOver = rhs.oneOver;
    }
    return *this;
}

std::string Logarithm::display() const
{
    std::string result = "";
    if (this->oneOver == 0)
    {
        if (this->coeff == 1) result = "log(" + this->base.display() + ")";
        else if (this->coeff == -1) result = "-log(" + this->base.display() + ")";
        else result = this->coeff.display() + "log(" + this->base.display() + ")";
    }
    else
    {
        if (this->coeff == 1) result = this->oneOver.display() + "/log(" + this->base.display() + ")";
        else if (this->coeff == -1) result = this->oneOver.display() + "/-log(" + this->base.display() + ")";
        else result = this->oneOver.display() + "/" + this->coeff.display() + "log(" + this->base.display() + ")";
    }
    return result;
}

float Logarithm::evaluate(float x) const
{
    float result = this->coeff.evaluate() * log10(this->base.evaluate(x));
    if (this->oneOver != 0) result = float(this->oneOver.evaluate()) / result;
    return result;
}

}
