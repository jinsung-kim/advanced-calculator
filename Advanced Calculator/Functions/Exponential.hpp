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

namespace RationalC { class Rational; }

namespace PolynomialC { class Polynomial; }

namespace ExponentialC
{

class Exponential
{
    friend std::ostream& operator << (std::ostream&, const Exponential&);
public:
    // Constructors
    // Default constructor creates 0
    Exponential();
    // Char as base indicates special case in which the base is 'e'
    Exponential(char, const PolynomialC::Polynomial&);
    Exponential(const RationalC::Rational&,
                const PolynomialC::Polynomial&);
    
    
private:
    RationalC::Rational base;
    PolynomialC::Polynomial pow;
};

}

# endif
