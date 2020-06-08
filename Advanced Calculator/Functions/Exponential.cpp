//
//  Exponential.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/28/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <iostream>
# include <exception>
# include <math.h>

# include "Exponential.hpp"
# include "Rational.hpp"
# include "Polynomial.hpp"
# include "Expression.hpp"

// Special Cases
# define e 2.718281828459
# define pi 3.14159265359

using namespace PolynomialC;
using namespace RationalC;
using namespace ExpressionC;

namespace ExponentialC
{

std::ostream& operator << (std::ostream& os, const Exponential& rhs)
{
    os << rhs.display();
    return os;
}

// Default constructor creates 0
// Nothing needs to be done as the default polynomial constructor
// creates this case
Exponential::Exponential(): val(0.0), oneOver(0) {}

Exponential::Exponential(std::string input)
{
    if (input.find("/(") != std::string::npos) // If over one
    {
        this->oneOver = Rational(input.substr(0, input.find("/(")));
        input = input.substr(input.find("/(") + 2);
        input.erase(std::remove(input.begin(), input.end(), ')'), input.end());
    }
    else
    {
        this->oneOver = 0;
    }
    std::string base = input.substr(0, input.find('^'));
    std::string after = input.substr(input.find('^') + 1);
    if (base == "e")
    {
        this->power = Polynomial(after);
        this->base = 0;
        this->val = e;
    }
    else if (base == "pi" || base == "π")
    {
        this->power = Polynomial(after);
        this->base = 0;
        this->val = pi;
        
    }
    else
    {
        this->power = Polynomial(after);
        this->base = Rational(base);
        this->val = 0.0;
    }
}

Exponential::Exponential(const std::string& c, const Polynomial& pow)
{
    // 'e' -> Euler's Number
    // 'pi' -> π
    if (c != "e" && c != "pi") throw std::invalid_argument("Base cannot be a variable");
    if (c == "e") this->val = e;
    else this->val = pi;
    this->base = 0;
    this->power = pow; // Refers to Polynomial assignment operator
    this->oneOver = 0;
}

Exponential::Exponential(const Rational& base,
                         const Polynomial& pow): base(base), power(pow), val(0.0), oneOver(0) {}

// Copy Constructor
Exponential::Exponential(const Exponential& rhs): base(rhs.base), power(rhs.power), val(rhs.val), oneOver(rhs.oneOver) {}

Exponential& Exponential::operator = (const Exponential& rhs)
{
    if (&rhs != this)
    {
        this->base = rhs.base;
        this->power = rhs.power;
        this->val = rhs.val;
        this->oneOver = rhs.oneOver;
    }
    return *this;
}

// Display
std::string Exponential::display() const
{
    std::string result = "";
    if (this->val == e) result = "e^(" + this->power.display() + ")";
    else if (this->val == pi) result = "π^(" + this->power.display() + ")";
    else result = this->base.display() + "^(" + this->power.display() + ")";
    if (this->oneOver != 0) result = this->oneOver.displayWithNegative() + "/(" + result + ")";
    return result;
}

// Integrate
//Expression Exponential::integrate() const
//{
//    std::string curr = this->display();
//    return ;
//}

// Derive
//Expression Exponential::derive() const
//{
//
//}

float Exponential::evaluate(float x) const
{
    float result = 0.0;
    if (this->val == 0.0) // Normal case
    {
        result = this->base.evaluate();
        result = pow(result, this->power.evaluate(x));
    }
    else // Special case
    {
        result = pow(this->val, this->power.evaluate(x));
    }
    if (this->oneOver != 0) result = this->oneOver.evaluate() / result;
    return result;
}

}
