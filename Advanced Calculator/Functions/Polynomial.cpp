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

// Polynomial relies on Rational numbers to build its constructor
namespace RationalC
{
    class Rational;
}

namespace IndeterminantC
{
    class Indeterminant;
}

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
                        output = output + rhs.expressions[i].getCoeff().display() + rhs.var;
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
                        output = output + rhs.expressions[i].getCoeff().display()
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
    RationalC::Rational* degree = nullptr;
    RationalC::Rational* coeff = nullptr;
//    int hold = 0;
    size_t i = 0;
    // Ex: 3x^2+3x^3
    while (i < expression.size())
    {
        if (std::isdigit(expression[i])) // Checks if the value is numeric
        {
            
        }
        else // Not a numeric value
        {
            if (expression[i] == '-') // negative sign
            {
                degree->setNegative(true);
            }
            else if (expression[i] == '/') // Fraction
            {
                
            }
            else if (std::isalpha(expression[i])) // If not '+' or '-', must be the variable being held
            {
                this->var = expression[i];
            }
        }
        // Both degree + coefficient have been found
        if (true)
        {
            auto toAdd = new IndeterminantC::Indeterminant(*degree, *coeff);
            this->expressions.push_back(*toAdd);
        }
    }
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial& rhs)
{
    this->var = rhs.var;
    for (size_t i = 0; i < rhs.expressions.size(); i++)
    {
        auto toAdd = new IndeterminantC::Indeterminant(rhs.expressions[i]);
        this->expressions.push_back(*toAdd);
    }
}

/**
 An alternate way to create Polynomials
 Precondition: The two parameters must match
 @param coeffs Rational vector containing all of the coefficients
 @param degrees Rational vector containing all of the degrees
 */
Polynomial::Polynomial(const std::vector<RationalC::Rational>& coeffs,
                       const std::vector<RationalC::Rational>& degrees)
{
    for (size_t i = 0; i < coeffs.size(); i++)
    {
        // Constructor being called: Indeterminant(degree, coeff);
        auto toAdd = new IndeterminantC::Indeterminant(degrees[i], coeffs[i]);
        this->expressions.push_back(*toAdd);
    }
    this->var = 'x';
}

// Assignment Operator
Polynomial& Polynomial::operator = (const Polynomial& rhs)
{
    return *this;
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
        auto newCoeff = RationalC::Rational((this->expressions[i].getCoeff()) * (this->expressions[i].getDegree()));
        bool prevNegative = this->expressions[i].getCoeff().getNegative();
        bool prevDegreeNegative = this->expressions[i].getDegree().getNegative();
        // Setting the negative
        if (prevNegative && prevDegreeNegative) newCoeff.setNegative(false);
        else if (prevDegreeNegative) newCoeff.setNegative(true);
        else if (prevNegative) newCoeff.setNegative(true);
        else newCoeff.setNegative(false);
        // Degree Calculations
        auto newDegree = RationalC::Rational(--(this->expressions[i].getDegree()));

        // Constructor used: Indeterminant(degree, coeff)
        auto derived = new IndeterminantC::Indeterminant(newDegree, newCoeff);
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
    return result;
}

// Algebraic Operations
/**
   Derives a given function, without altering the current polynomial
   @param x Whatever value that should be evaluated
   @return Whatever value results from entering the value within the polynomial
*/
double Polynomial::evaluate(double x)
{
    return 0.0;
}

}
