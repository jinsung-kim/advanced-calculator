//
//  Exponential.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/28/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# ifndef Exponential_hpp
# define Exponential_hpp

# include <iostream>

# include "Rational.hpp"
# include "Polynomial.hpp"
# include "Expression.hpp"

/*
 Separated into two cases:
 Typical case: In which the base is an rational number
 and the power contains a polynomial expression
 Special case: The base is a rational number that are
 commonly used as math symbols such as 'e' and 'π'
 in which we can represent a special exponential
 expression
 The base of the special case is irrelevant, and will not be used for calculations
 */

namespace RationalC { class Rational; }

namespace PolynomialC { class Polynomial; }

namespace ExpressionC { class Expression; }

namespace ExponentialC
{

class Exponential
{
    friend std::ostream& operator << (std::ostream&, const Exponential&);
public:
    // Constructors
    // Default constructor creates 0
    Exponential();
    Exponential(std::string);
    // Char as base indicates special case in which the base is 'e'
    Exponential(const std::string&, const PolynomialC::Polynomial&);
    Exponential(const RationalC::Rational&,
                const PolynomialC::Polynomial&);
    // Copy Constructor
    Exponential(const Exponential&);
    // Assignment Operator
    Exponential& operator = (const Exponential&);
    
    // Display function
    std::string display() const;
    
    // Integrate
    ExpressionC::Expression integrate() const;
    
    // Evaluate
    float evaluate(float x) const;
    
private:
    RationalC::Rational base;
    PolynomialC::Polynomial power;
    double val; // If there is a special case, we change the value of 'val'
    RationalC::Rational oneOver;
};

}

# endif
