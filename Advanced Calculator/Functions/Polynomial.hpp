//
//  Polynomial.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# ifndef Polynomial_hpp
# define Polynomial_hpp

# include "Rational.hpp"
# include "Indeterminant.hpp"
# include <iostream>
# include <vector>
# include <string>

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

class Polynomial
{
    friend std::ostream& operator << (std::ostream& os, const Polynomial& rhs);
public:
    // Constructors
    Polynomial();

    // Takes in a VALID string input and reforms it into a valid Polynomial object
    Polynomial(std::string);
    
    // Takes in Rational vectors to represent coefficients and degrees
    Polynomial(const std::vector<RationalC::Rational>&, const std::vector<RationalC::Rational>&);

    // Copy Constructor
    Polynomial(const Polynomial& rhs);
    
    // Assignment Operator
    Polynomial& operator = (const Polynomial& rhs);
    
    // Sorting degrees in order
    void sortExpression();
    
    // Calculus Operations
    Polynomial derive() const;
    Polynomial integrate() const;
    
    // Algebraic Operations
    float evaluate(float);
    
private:
    std::vector<IndeterminantC::Indeterminant> expressions;
    // The variable used
    char var;
};

}

# endif
