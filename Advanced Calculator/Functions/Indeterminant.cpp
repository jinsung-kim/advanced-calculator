//
//  Indeterminant.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include "Indeterminant.hpp"
# include "Rational.hpp"
# include <iostream>

using namespace RationalC;

class Rational;

namespace IndeterminantC
{

std::ostream& operator << (std::ostream& os, const Indeterminant& rhs)
{
    os << "Coeff: " << rhs.coeff << ", Degree: " << rhs.degree;
    return os;
}

Indeterminant::Indeterminant(): degree(RationalC::Rational()), coeff(RationalC::Rational()) {}

Indeterminant::Indeterminant(int degree, int coeff):
degree(RationalC::Rational(degree, 1)), coeff(RationalC::Rational(coeff, 1)) {}

Indeterminant::Indeterminant(const RationalC::Rational& degree, const RationalC::Rational& coeff):
degree(degree), coeff(coeff) {}

Indeterminant::Indeterminant(const Indeterminant& rhs): degree(rhs.degree), coeff(rhs.coeff) {}

// Assignment Operator
Indeterminant& Indeterminant::operator=(const Indeterminant& rhs)
{
    if (&rhs != this)
    {
        this->coeff = rhs.coeff;
        this->degree = rhs.degree;
    }
    return *this;
}

// Getters
RationalC::Rational Indeterminant::getDegree() const { return this->degree; }

RationalC::Rational Indeterminant::getCoeff() const { return this->coeff; }

// Setters
void Indeterminant::setDegree(const RationalC::Rational& degree) { this->degree = degree; }

void Indeterminant::setCoeff(const RationalC::Rational& coeff) { this->coeff = coeff; }

}
