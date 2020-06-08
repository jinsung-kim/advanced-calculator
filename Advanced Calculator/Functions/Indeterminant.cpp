//
//  Indeterminant.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <iostream>

# include "Indeterminant.hpp"
# include "Rational.hpp"

using namespace RationalC;

namespace IndeterminantC
{

// For testing purposes, will never be called
std::ostream& operator << (std::ostream& os, const Indeterminant& rhs)
{
    os << "Coeff: " << rhs.coeff << ", Degree: " << rhs.degree;
    return os;
}

Indeterminant::Indeterminant(): degree(Rational()), coeff(Rational()) {}

Indeterminant::Indeterminant(int degree, int coeff):
degree(Rational(degree, 1)), coeff(Rational(coeff, 1)) {}

Indeterminant::Indeterminant(const Rational& degree, const Rational& coeff):
degree(degree), coeff(coeff) {}

// Copy Constructor
Indeterminant::Indeterminant(const Indeterminant& rhs): degree(rhs.degree), coeff(rhs.coeff) {}

// Assignment Operator
Indeterminant& Indeterminant::operator = (const Indeterminant& rhs)
{
    if (&rhs != this)
    {
        this->coeff = rhs.coeff;
        this->degree = rhs.degree;
    }
    return *this;
}

// Getters
Rational Indeterminant::getDegree() const { return this->degree; }

Rational Indeterminant::getCoeff() const { return this->coeff; }

// Setters
void Indeterminant::setDegree(const Rational& degree) { this->degree = degree; }

void Indeterminant::setCoeff(const Rational& coeff) { this->coeff = coeff; }

}
