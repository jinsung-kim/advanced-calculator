//
//  Exponential.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/28/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include <iostream>
# include <exception>
# include "Exponential.hpp"
# include "Rational.hpp"
# include "Polynomial.hpp"

// Special Cases
# define e 2.718281828459
# define pi 3.14159265359

namespace RationalC { class Rational; }

namespace PolynomialC { class Polynomial; }

namespace ExponentialC
{

std::ostream& operator << (std::ostream& os, const Exponential& rhs)
{
    if (rhs.val == e) os << "e^(" << rhs.pow << ")";
    else if (rhs.val == pi) os << "π^(" << rhs.pow << ")";
    else os << rhs.base << "^(" << rhs.pow << ")";
    return os;
}

// Default constructor creates 0
// Nothing needs to be done as the default polynomial constructor
// creates this case
Exponential::Exponential(): val(0.0) {}

Exponential::Exponential(const std::string& c, const PolynomialC::Polynomial& pow)
{
    // 'e' -> Euler's Number
    // 'pi' -> π
    if (c != "e" && c != "pi") throw std::invalid_argument("Base cannot be a variable");
    if (c == "e") this->val = e;
    else this->val = pi;
    this->base = 0;
    this->pow = pow; // Refers to Polynomial assignment operator
}

Exponential::Exponential(const RationalC::Rational& base,
                         const PolynomialC::Polynomial& pow): base(base), pow(pow), val(0.0) {}

// Copy Constructor
Exponential::Exponential(const Exponential& rhs): base(rhs.base), pow(rhs.pow), val(rhs.val) {}

Exponential& Exponential::operator = (const Exponential& rhs)
{
    if (&rhs != this)
    {
        this->base = rhs.base;
        this->pow = rhs.pow;
        this->val = rhs.val;
    }
    return *this;
}

}
