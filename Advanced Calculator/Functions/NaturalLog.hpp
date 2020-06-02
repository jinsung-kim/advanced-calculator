//
//  NaturalLog.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/2/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# ifndef NaturalLog_hpp
# define NaturalLog_hpp
# include <iostream>
# include "Rational.hpp"
# include "Polynomial.hpp"

namespace RationalC { class Rational; }
namespace PolynomialC { class Polynomial; }

namespace NaturalLogC
{

class NaturalLog
{
    friend std::ostream& operator << (std::ostream&, const NaturalLog&);
public:
    NaturalLog();
    NaturalLog(const RationalC::Rational&, const PolynomialC::Polynomial&);
    // Copy Constructor
    NaturalLog(const NaturalLog&);
    NaturalLog& operator = (const NaturalLog&);
    // Algebraic Operations
    float evaluate(float) const;
    
private:
    PolynomialC::Polynomial base;
    RationalC::Rational coeff;
};

}

# endif
