//
//  Indeterminant.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# ifndef Indeterminant_hpp
# define Indeterminant_hpp
# include "Rational.hpp"
# include <iostream>

namespace RationalC
{
    class Rational;
}

namespace IndeterminantC
{

class Indeterminant
{
public:
    Indeterminant();
    Indeterminant(int, int);
    Indeterminant(const RationalC::Rational&, const RationalC::Rational&);
    
    // Getters
    RationalC::Rational getDegree() const;
    RationalC::Rational getCoeff() const;
    
    // Setters
    void setDegree(const RationalC::Rational&);
    void setCoeff(const RationalC::Rational&);
    
private:
    RationalC::Rational degree;
    RationalC::Rational coeff;
};

}

# endif
