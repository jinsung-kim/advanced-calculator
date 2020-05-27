//
//  main.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include <iostream>
# include <vector>
# include "Rational.hpp"
# include "Polynomial.hpp"
# include "Indeterminant.hpp"

using namespace RationalC;
using namespace IndeterminantC;
using namespace PolynomialC;

int main()
{
    auto test = Rational(2, 6);
    auto test2 = Rational(-2, 4);
    auto test3 = Rational(2, 1);
    auto test4 = Rational(3, 1);
//    auto test4 = Polynomial("3 x ^2 + 3x  ^3");
//    std::cout << test4 << std::endl;
    auto test5 = Polynomial({test, test2}, {test3, test4});
    test5.sortExpression();
//    std::cout << test5 << std::endl;
    auto test5D = test5.derive();
    std::cout << test5D << std::endl;
    return 0;
}
