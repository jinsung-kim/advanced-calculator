//
//  Expression.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/1/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# ifndef Expression_hpp
# define Expression_hpp

# include <iostream>
# include <vector>
# include <string>
# include <unordered_map>

# include "Exponential.hpp"
# include "Indeterminant.hpp"
# include "Polynomial.hpp"
# include "Rational.hpp"
# include "NaturalLog.hpp"
# include "Logarithm.hpp"

namespace ExponentialC { class Exponential; }
namespace IndeterminantC { class Indeterminant; }
namespace PolynomialC { class Polynomial; }
namespace RationalC { class Rational; }
namespace LogarithmC { class Logarithm; }
namespace NaturalLogC { class NaturalLog; }

namespace ExpressionC
{

class Expression
{
    friend std::ostream& operator << (std::ostream&, Expression&);
public:
    Expression(std::string);
    
private:
    // For each term in the expression, it will be placed in the corresponding map
    // The signs of the terms will be tracked in a separate vector
    std::vector<bool> negative;
    std::unordered_map<size_t, std::vector<PolynomialC::Polynomial>> polynomials;
    std::unordered_map<size_t, std::vector<ExponentialC::Exponential>> exponentials;
    std::unordered_map<size_t, std::vector<LogarithmC::Logarithm>> logs;
    std::unordered_map<size_t, std::vector<NaturalLogC::NaturalLog>> naturals;
    std::unordered_map<size_t, std::vector<RationalC::Rational>> rationals;
};

}

# endif
