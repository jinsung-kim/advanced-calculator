//
//  Polynomial.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include "Polynomial.hpp"
# include "Indeterminant.hpp"
# include <iostream>
# include <vector>
# include <math.h>

// Polynomial relies on Rational numbers to build its constructor
using namespace RationalC;
using namespace IndeterminantC;

namespace PolynomialC
{

std::ostream& operator << (std::ostream& os, const Polynomial& rhs)
{
    std::string output = "";
    for (size_t i = 0; i < rhs.expressions.size(); i++)
    {
        if (rhs.expressions[i].getCoeff() != 0)
        {
            if (rhs.expressions[i].getDegree() == 0) // Constant
            {
                if (rhs.expressions[i].getCoeff().getNegative())
                {
                    output = output + "-" + rhs.expressions[i].getCoeff().display();
                }
                else
                {
                    output = output + "+" + rhs.expressions[i].getCoeff().display();
                }
            }
            else if (rhs.expressions[i].getDegree() == 1) // Degree is linear
            {
                if (rhs.expressions[i].getCoeff().getNegative())
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + "-" + rhs.var;
                    }
                    else
                    {
                        output = output + "-" + rhs.expressions[i].getCoeff().display() + rhs.var;
                    }
                }
                else
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + "+" + rhs.var;
                    }
                    else
                    {
                        output = output + "+" + rhs.expressions[i].getCoeff().display() + rhs.var;
                    }
                }
            }
            else // Degree is quadratic or higher; indicating that it must be stated
            {
                if (rhs.expressions[i].getCoeff().getNegative())
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + "-" + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                    else
                    {
                        output = output + "-" + rhs.expressions[i].getCoeff().display()
                        + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                }
                else
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + "+" + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                    else
                    {
                        output = output + "+" + rhs.expressions[i].getCoeff().display()
                        + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                }
            }
        }
    }
    // If the polynomial is empty, there is nothing else to be done except print 0
    if (output == "") output = "0";
    // If there is a negative, then do not splice the negative away
    // If there is a plus, then cut out the first index
    else if (output[0] != '-') output = output.substr(1);
    os << output;
    return os;
}

// Constructor
Polynomial::Polynomial(): var('x') {}

Polynomial::Polynomial(std::string expression)
{
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    std::string split = "";
    std::vector<std::string> terms;
    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '+' || expression[i] == '-') // A new term to separate
        {
            if (split != "") terms.push_back(split);
            split = expression[i];
        }
        else
        {
            split += expression[i];
        }
    }
    if (split != "") terms.push_back(split);
    for (const std::string& term: terms)
    {
        Rational* coeff = nullptr;
        Rational* degree = nullptr;
        size_t ind = term.find('^');
        std::string degreeString = term.substr(ind + 1);
        this->var = term[ind - 1];
        std::string coeffString = term.substr(0, ind - 1);
        if (coeffString.find('/') == std::string::npos) // No fraction within the coefficient
        {
            coeff = new Rational(std::stoi(coeffString));
        }
        else // Fraction is found and needs to be divided
        {
            std::string before = coeffString.substr(0, coeffString.find('/'));
            std::string after = coeffString.substr(coeffString.find('/') + 1);
            coeff = new Rational(std::stoi(before), std::stoi(after));
        }
        if (degreeString.find('/') == std::string::npos) // No fraction within the degree
        {
            degree = new Rational(std::stoi(degreeString));
        }
        else // Fraction is found and needs to be divided
        {
            std::string before = degreeString.substr(0, degreeString.find('/'));
            std::string after = degreeString.substr(degreeString.find('/') + 1);
            degree = new Rational(std::stoi(before), std::stoi(after));
        }
        Indeterminant* toAdd = new Indeterminant(*degree, *coeff);
        this->expressions.push_back(*toAdd); // Add to the expressions list
    }
    terms.clear();
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial& rhs)
{
    this->var = rhs.var;
    for (size_t i = 0; i < rhs.expressions.size(); i++)
    {
        auto toAdd = new Indeterminant(rhs.expressions[i]);
        this->expressions.push_back(*toAdd);
    }
}

/**
 An alternate way to create Polynomials
 Precondition: The two parameters must match
 @param coeffs Rational vector containing all of the coefficients
 @param degrees Rational vector containing all of the degrees
 */
Polynomial::Polynomial(const std::vector<Rational>& coeffs,
                       const std::vector<Rational>& degrees)
{
    for (size_t i = 0; i < coeffs.size(); i++)
    {
        // Constructor being called: Indeterminant(degree, coeff);
        auto toAdd = new Indeterminant(degrees[i], coeffs[i]);
        this->expressions.push_back(*toAdd);
    }
    this->var = 'x';
}

// Assignment Operator
Polynomial& Polynomial::operator = (const Polynomial& rhs)
{
    if (&rhs != this)
    {
        this->expressions.clear();
        for (size_t i = 0; i < rhs.expressions.size(); i++)
        {
            auto toAdd = new Indeterminant(rhs.expressions[i].getDegree(),
                                           rhs.expressions[i].getCoeff());
            this->expressions.push_back(*toAdd);
        }
    }
    return *this;
}

Polynomial::~Polynomial()
{
    this->expressions.clear();
}

// Sorting degrees in order - A simple selection sort
// Highest degree first, lowest degree last
void Polynomial::sortExpression()
{
    size_t maxInd;
    for (size_t i = 0; i < this->expressions.size(); i++)
    {
        maxInd = i;
        for (size_t j = i + 1; j < this->expressions.size(); j++)
        {
            if (this->expressions[j].getDegree() > this->expressions[maxInd].getDegree())
            {
                auto temp = this->expressions[j];
                this->expressions[j] = this->expressions[maxInd];
                this->expressions[maxInd] = temp;
            }
        }
    }
}

// Calculus Operations
/**
    Derives a given function, without altering the current polynomial
    @return A result polynomial (derived)
 */
Polynomial Polynomial::derive() const
{
    Polynomial result;
    for (size_t i = 0; i < this->expressions.size(); i++)
    {
        // Coeff Calculations
        auto newCoeff = Rational((this->expressions[i].getCoeff()) * (this->expressions[i].getDegree()));
        // Degree Calculations
        auto newDegree = Rational(--(this->expressions[i].getDegree()));
        
        // Constructor used: Indeterminant(degree, coeff)
        auto derived = new Indeterminant(newDegree, newCoeff);
        result.expressions.push_back(*derived);
    }
    return result;
}

/**
   Integrates a given function, without altering the current polynomial
   @return A result polynomial (integrated)
*/
Polynomial Polynomial::integrate() const
{
    Polynomial result;
    for (size_t i = 0; i < this->expressions.size(); i++)
    {
        auto newDegree = Rational(++(this->expressions[i].getDegree()));
        auto newCoeff = Rational(this->expressions[i].getCoeff() / newDegree);
        auto integrated = new Indeterminant(newDegree, newCoeff);
        result.expressions.push_back(*integrated);
    }
    return result;
}

// Algebraic Operations
/**
   Derives a given function, without altering the current polynomial
   @param x Whatever value that should be evaluated
   @return Whatever value results from entering the value within the polynomial
*/
float Polynomial::evaluate(float x) const
{
    float result = 0;
    for (size_t i = 0; i < this->expressions.size(); i++)
    {
        result += (this->expressions[i].getCoeff().evaluate() *
                   pow(x, this->expressions[i].getDegree().evaluate()));
    }
    return result;
}

}
