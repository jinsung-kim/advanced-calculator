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
# include "Exponential.hpp"

using namespace RationalC;
using namespace IndeterminantC;
using namespace PolynomialC;
using namespace ExponentialC;

void rationalPolynomialTest()
{
    auto test = Rational(2, 6);
    auto test2 = Rational(-2, 4);
    auto test3 = Rational(2, 1);
    auto test4 = Rational(3, 1);
    auto test5 = Polynomial({test, test2}, {test3, test4});
    std::cout << test5 << std::endl;
    test5.sortExpression();
    std::cout << test5 << std::endl;
    auto test5D = test5.derive();
    auto test5DD = test5.derive().derive();
    auto test5DDD = test5.derive().derive().derive();
    std::cout << test5D << std::endl;
    std::cout << test5DD << std::endl;
    std::cout << test5DDD << std::endl;
    std::cout << test5DDD.derive() << std::endl;
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << test5.evaluate(i) << std::endl;
    }
}

void exponentialTest()
{
    auto test = Rational(2, 6);
    auto test2 = Rational(-2, 4);
    auto test3 = Rational(2, 1);
    auto test4 = Rational(3, 1);
    auto test5 = Polynomial({test, test2}, {test3, test4});
    auto test6 = Exponential(test, test5);
    auto test7 = Exponential("pi", test5);
    auto test8 = Exponential("e", test5);
    std::cout << test6 << std::endl;
    std::cout << test7 << std::endl;
    std::cout << test8 << std::endl;
}

void runTestCases()
{
//    rationalPolynomialTest();
    exponentialTest();
}

int main()
{
    runTestCases();
    return 0;
}
