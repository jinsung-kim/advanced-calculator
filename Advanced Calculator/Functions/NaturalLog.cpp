//
//  NaturalLog.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/2/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <iostream>
# include <math.h>
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

float NaturalLog::evaluate(float x) const
{
    float result = this->coeff.evaluate() * log(this->base.evaluate(x));
    return result;
}

}
