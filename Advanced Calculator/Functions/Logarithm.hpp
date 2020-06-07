//
//  Logarithm.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/1/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# ifndef Logarithm_hpp
# define Logarithm_hpp
# include <iostream>

# include "Rational.hpp"
# include "Polynomial.hpp"

namespace RationalC { class Rational; }
namespace PolynomialC { class Polynomial; }

namespace LogarithmC
{

class Logarithm
{
    friend std::ostream& operator << (std::ostream&, const Logarithm&);
public:
    Logarithm();
    Logarithm(const std::string&);
    Logarithm(const RationalC::Rational&, const PolynomialC::Polynomial&);
    
    // Copy Constructor
    Logarithm(const Logarithm&);
    Logarithm& operator = (const Logarithm&);
    
    // Display
    std::string display() const;
    
    // Algebraic Operations
    float evaluate(float) const;
private:
    PolynomialC::Polynomial base;
    RationalC::Rational coeff;
};

}

# endif
