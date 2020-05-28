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

namespace RationalC { class Rational; }

namespace PolynomialC { class Polynomial; }

namespace ExponentialC
{

//std::ostream& operator << (std::ostream& os, const Exponential& rhs)
//{
//    if ()
//}

// Default constructor creates 0
// Nothing needs to be done as the default polynomial constructor
// creates this case
Exponential::Exponential() {}

Exponential::Exponential(char e, const PolynomialC::Polynomial& pow)
{
    if (e != 'e') throw std::invalid_argument("Base cannot be a variable");
    this->pow = pow; // Refers to Polynomial assignment operator
}

Exponential::Exponential(const RationalC::Rational& base,
                         const PolynomialC::Polynomial& pow): base(base), pow(pow) {}



}
