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
                    output = output + " - " + rhs.expressions[i].getCoeff().display();
                }
                else
                {
                    output = output + " + " + rhs.expressions[i].getCoeff().display();
                }
            }
            else if (rhs.expressions[i].getDegree() == 1) // Degree is linear
            {
                if (rhs.expressions[i].getCoeff().getNegative())
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + " - " + rhs.var;
                    }
                    else
                    {
                        output = output + " - " + rhs.expressions[i].getCoeff().display() + rhs.var;
                    }
                }
                else
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + " + " + rhs.var;
                    }
                    else
                    {
                        output = output + " + " + rhs.expressions[i].getCoeff().display() + rhs.var;
                    }
                }
            }
            else // Degree is quadratic or higher; indicating that it must be stated
            {
                if (rhs.expressions[i].getCoeff().getNegative())
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + " - " + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                    else
                    {
                        output = output + " - " + rhs.expressions[i].getCoeff().display()
                        + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                }
                else
                {
                    if (rhs.expressions[i].getCoeff() == 1)
                    {
                        output = output + " + " + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                    else
                    {
                        output = output + " + " + rhs.expressions[i].getCoeff().display()
                        + rhs.var + "^" + rhs.expressions[i].getDegree().display();
                    }
                }
            }
        }
    }
    // If the polynomial is empty, there is nothing else to be done except print 0
    if (output == "") output = "0";
    os << output;
    return os;
}

// Constructor
Polynomial::Polynomial(): var('x') {}

Polynomial::Polynomial(std::string expression)
{
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    std::cout << expression << std::endl;
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial& rhs)
{
    
}

// Assignment Operator
Polynomial& Polynomial::operator = (const Polynomial& rhs)
{
    return *this;
}

// Sorting degrees in order
void Polynomial::sortExpression()
{
    
}

// Calculus Operations
Polynomial Polynomial::derive() const
{
    Polynomial result;
    return result;
}

Polynomial Polynomial::integrate() const
{
    Polynomial result;
    return result;
}

// Algebraic Operations
double Polynomial::evaluate(double x)
{
    return 0.0;
}

}
