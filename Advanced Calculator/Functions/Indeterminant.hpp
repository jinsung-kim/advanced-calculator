//
//  Indeterminant.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# ifndef Indeterminant_hpp
# define Indeterminant_hpp

# include <iostream>

# include "Rational.hpp"

namespace RationalC { class Rational; }

namespace IndeterminantC
{

class Indeterminant
{
    friend std::ostream& operator << (std::ostream&, const Indeterminant&);
public:
    Indeterminant();
    Indeterminant(int, int);
    Indeterminant(const RationalC::Rational&, const RationalC::Rational&);
    Indeterminant(const Indeterminant&);
    
    // Assignment Operator
    Indeterminant& operator = (const Indeterminant& rhs);
    
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
