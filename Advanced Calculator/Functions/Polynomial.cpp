//
//  Polynomial.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <iostream>
# include <vector>
# include <math.h>

# include "Polynomial.hpp"
# include "Indeterminant.hpp"

// Polynomial relies on Rational numbers to build its constructor
using namespace RationalC;
using namespace IndeterminantC;

const std::string validVars = "abcdfghjklmnoqrstuvwxyz"; // Excluded e and pi

namespace PolynomialC
{

std::ostream& operator << (std::ostream& os, const Polynomial& rhs)
{
    os << rhs.display();
    return os;
}

// Constructor
Polynomial::Polynomial(): var('x'), oneOver(0) {}

Polynomial::Polynomial(std::string expression)
{
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    std::string split = "";
    std::vector<std::string> terms;
    if (expression.find("/(") != std::string::npos) // One over function
    {
        this->oneOver = Rational(expression.substr(0, expression.find("/(")));
        expression = expression.substr(expression.find("/(") + 2);
        expression.erase(std::remove(expression.begin(), expression.end(), ')'), expression.end());
    }
    else
    {
        this->oneOver = 0;
    }
    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '+' || expression[i] == '-') // A new term to separate
        {
            if (split != "") terms.push_back(split);
            split = expression[i];
        }
        else split += expression[i];
    }
    if (split != "") terms.push_back(split);
    for (const std::string& term: terms)
    {
        Rational* coeff = nullptr;
        Rational* degree = nullptr;
        if (term.find('^') != std::string::npos) // Degree is 2 or more
        {
            size_t ind = term.find('^');
            std::string degreeString = term.substr(ind + 1);
            this->var = term[ind - 1];
            std::string coeffString = term.substr(0, ind - 1);
            coeff = new Rational(coeffString);
            degree = new Rational(degreeString);
        }
        else // Degree is at most 1
        {
            if (term.find_first_of(validVars) == std::string::npos) // Constant
            {
                coeff = new Rational(term);
                degree = new Rational(0);
            }
            else
            {
                size_t ind = term.find_first_of(validVars);
                coeff = new Rational(term.substr(0, ind));
                degree = new Rational(1);
                this->var = term[term.find_first_of(validVars)];
            }
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
    this->oneOver = rhs.oneOver;
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
    this->oneOver = 0;
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
        this->var = rhs.var;
        this->oneOver = rhs.oneOver;
    }
    return *this;
}

Polynomial::~Polynomial()
{
    this->expressions.clear();
}

// Display
std::string Polynomial::display() const
{
    std::string output = "";
    for (size_t i = 0; i < this->expressions.size(); i++)
    {
        if (this->expressions[i].getCoeff() != 0)
        {
            if (this->expressions[i].getDegree() == 0) // Constant
            {
                if (this->expressions[i].getCoeff().getNegative())
                {
                    output = output + "-" + this->expressions[i].getCoeff().display();
                }
                else
                {
                    output = output + "+" + this->expressions[i].getCoeff().display();
                }
            }
            else if (this->expressions[i].getDegree() == 1) // Degree is linear
            {
                if (this->expressions[i].getCoeff().getNegative())
                {
                    if (this->expressions[i].getCoeff() == 1)
                    {
                        output = output + "-" + this->var;
                    }
                    else
                    {
                        output = output + "-" + this->expressions[i].getCoeff().display() + this->var;
                    }
                }
                else
                {
                    if (this->expressions[i].getCoeff() == 1)
                    {
                        output = output + "+" + this->var;
                    }
                    else
                    {
                        output = output + "+" + this->expressions[i].getCoeff().display() + this->var;
                    }
                }
            }
            else // Degree is quadratic or higher; indicating that it must be stated
            {
                if (this->expressions[i].getCoeff().getNegative())
                {
                    if (this->expressions[i].getCoeff() == 1)
                    {
                        output = output + "-" + this->var + "^" + this->expressions[i].getDegree().display();
                    }
                    else
                    {
                        output = output + "-" + this->expressions[i].getCoeff().display()
                        + this->var + "^" + this->expressions[i].getDegree().display();
                    }
                }
                else
                {
                    if (this->expressions[i].getCoeff() == 1)
                    {
                        output = output + "+" + this->var + "^" + this->expressions[i].getDegree().display();
                    }
                    else
                    {
                        output = output + "+" + this->expressions[i].getCoeff().display()
                        + this->var + "^" + this->expressions[i].getDegree().display();
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
    if (this->oneOver != 0) output = this->oneOver.displayWithNegative() + "/(" + output + ")";
    return output;
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
    if (this->oneOver == 0)
    {
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
    }
    else
    {
        for (size_t i = 0; i < this->expressions.size(); i++)
        {
            // Coeff Calculations
            auto newCoeff = Rational((this->expressions[i].getCoeff()) * (this->expressions[i].getDegree() * -1));
            // Degree Calculations
            auto newDegree = Rational(--(this->expressions[i].getDegree() * -1));
            
            // Constructor used: Indeterminant(degree, coeff)
            auto derived = new Indeterminant(newDegree, newCoeff);
            result.expressions.push_back(*derived);
        }
    }
    result.oneOver = this->oneOver;
    return result;
}

/**
   Integrates a given function, without altering the current polynomial
   @return A result polynomial (integrated)
*/
Polynomial Polynomial::integrate() const
{
    Polynomial result;
    if (this->oneOver == 0)
    {
        for (size_t i = 0; i < this->expressions.size(); i++)
        {
            auto newDegree = Rational(++(this->expressions[i].getDegree()));
            auto newCoeff = Rational(this->expressions[i].getCoeff() / newDegree);
            auto integrated = new Indeterminant(newDegree, newCoeff);
            result.expressions.push_back(*integrated);
        }
    }
    else
    {
        for (size_t i = 0; i < this->expressions.size(); i++)
        {
            auto newDegree = Rational(++(this->expressions[i].getDegree() * -1));
            auto newCoeff = Rational(this->expressions[i].getCoeff() / newDegree);
            auto integrated = new Indeterminant(newDegree, newCoeff);
            result.expressions.push_back(*integrated);
        }
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
    if (this->oneOver != 0) result = oneOver.evaluate() / result;
    return result;
}

}
