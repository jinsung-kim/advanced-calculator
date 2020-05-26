//
//  main.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include <iostream>
# include "Rational.hpp"
# include "Polynomial.hpp"
# include "Indeterminant.hpp"

using namespace RationalC;
using namespace IndeterminantC;
using namespace PolynomialC;

int main()
{
    std::cout << "Testing Rationals" << std::endl;
    auto test = Rational(2, 6);
    auto test2 = Rational(-2, 4);
    std::cout << test << std::endl;
    std::cout << test2 << std::endl;
//    std::cout << test + test2 << std::endl;
//    std::cout << test - test2 << std::endl;
    std::cout << test.display() << std::endl;
    std::cout << test2.display() << std::endl;
    auto test3 = Indeterminant(3, 4);
    std::cout << test3.getCoeff() << "x^" << test3.getDegree() << std::endl;
    auto test4 = Polynomial("3 x ^2 + 3x  ^3");
//    std::cout << test4 << std::endl;
    return 0;
}
