//
//  Exponential.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/28/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include <iostream>
# include <exception>
# include <math.h>
# include "Exponential.hpp"
# include "Rational.hpp"
# include "Polynomial.hpp"

// Special Cases
# define e 2.718281828459
# define pi 3.14159265359

using namespace PolynomialC;
using namespace RationalC;

namespace ExponentialC
{

std::ostream& operator << (std::ostream& os, const Exponential& rhs)
{
    if (rhs.val == e) os << "e^(" << rhs.power << ")";
    else if (rhs.val == pi) os << "π^(" << rhs.power << ")";
    else os << rhs.base << "^(" << rhs.power << ")";
    return os;
}

// Default constructor creates 0
// Nothing needs to be done as the default polynomial constructor
// creates this case
Exponential::Exponential(): val(0.0) {}

Exponential::Exponential(const std::string& input)
{
    std::string base = input.substr(0, input.find('^'));
    std::string after = input.substr(input.find('^') + 1);
    this->power = Polynomial(after);
    this->base = Rational(base);
}

Exponential::Exponential(const std::string& c, const Polynomial& pow)
{
    // 'e' -> Euler's Number
    // 'pi' -> π
    if (c != "e" && c != "pi") throw std::invalid_argument("Base cannot be a variable");
    if (c == "e") this->val = e;
    else this->val = pi;
    this->base = 0;
    this->power = pow; // Refers to Polynomial assignment operator
}

Exponential::Exponential(const Rational& base,
                         const Polynomial& pow): base(base), power(pow), val(0.0) {}

// Copy Constructor
Exponential::Exponential(const Exponential& rhs): base(rhs.base), power(rhs.power), val(rhs.val) {}

Exponential& Exponential::operator = (const Exponential& rhs)
{
    if (&rhs != this)
    {
        this->base = rhs.base;
        this->power = rhs.power;
        this->val = rhs.val;
    }
    return *this;
}

// Integrate

// Derive

float Exponential::evaluate(float x) const
{
    float result = 0.0;
    if (this->val == 0.0) // Normal case
    {
        result = this->base.evaluate();
        result = pow(result, this->power.evaluate(x));
    }
    else // Special case
    {
        result = pow(this->val, this->power.evaluate(x));
    }
    return result;
}

}
