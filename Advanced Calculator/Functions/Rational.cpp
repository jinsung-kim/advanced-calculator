//
//  Rational.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# include "Rational.hpp"
# include <iostream>
# include <exception>

// Used to reduce
// Does not work with negative integers
int GCD(int a, int b)
{
    // When a % b == 0
    if (a == 0) return b;
    if (b == 0) return a;
    // Base Case:
    if (a == b) return a;
    // Recursive Case:
    return GCD(b, a % b);
}

int LCM(int a, int b)
{
    int max = (a > b) ? a : b;
    do
    {
        if (max % a == 0 && max % b == 0)
        {
            return max;
            break;
        }
        else
            ++max;
    } while (true);
}

namespace RationalC
{

// Operator Overloading
std::ostream& operator << (std::ostream& os, const Rational& rhs)
{
    Rational rhsReduced = rhs.reduce();
    if (rhs.negative) os << "-";
    if (rhsReduced.den == 1) os << rhsReduced.num;
    else os << rhsReduced.num << "/" << rhsReduced.den;
    return os;
}

bool operator == (const Rational& lhs, const Rational& rhs)
{
    Rational lhsReduced = lhs.reduce();
    Rational rhsReduced = rhs.reduce();
    return (lhsReduced.num == rhsReduced.num) && (lhsReduced.den == rhsReduced.den)
            && (rhs.negative == lhs.negative);
}

bool operator == (const Rational& lhs, int constant)
{
    float c = float(lhs.num) / float(lhs.den);
    if (lhs.negative) c *= -1;
    return c == constant;
}

bool operator != (const Rational& lhs, const Rational& rhs)
{
    return !(lhs == rhs);
}

bool operator != (const Rational& lhs, int constant)
{
    return !(lhs == constant);
}

// Addition
Rational operator + (const Rational& lhs, const Rational& rhs)
{
    Rational result;
    int lcm = LCM(lhs.den, rhs.den);
    int lhsMult = (lcm / lhs.den);
    int rhsMult = (lcm / rhs.den);
    if (lhs.negative) lhsMult *= -1;
    if (rhs.negative) rhsMult *= -1;
    result.num = (lhs.num * lhsMult) + (rhs.num * rhsMult);
    // Fix back if there are inconsistencies
    if (result.num < 0) result.negative = true; result.num *= -1;
    result.den = lcm;
    result.reduce();
    return result;
}

// Subtraction
Rational operator - (const Rational& lhs, const Rational& rhs)
{
    Rational result;
    int lcm = LCM(lhs.den, rhs.den);
    int lhsMult = (lcm / lhs.den);
    int rhsMult = (lcm / rhs.den);
    if (lhs.negative) lhsMult *= -1;
    if (rhs.negative) rhsMult *= -1;
    result.num = (lhs.num * lhsMult) - (rhs.num * rhsMult);
    // Fix back if there are inconsistencies
    if (result.num < 0) result.negative = true;
    result.den = lcm;
    result.reduce();
    return result;
}

// Multiplication
Rational operator * (const Rational& lhs, const Rational& rhs)
{
    Rational result;
    result.num = lhs.num * rhs.num;
    result.den = lhs.den * rhs.den;
    result.negative = (lhs.negative && rhs.negative);
    result.reduce();
    return result;
}

// Division
Rational operator / (const Rational& lhs, const Rational& rhs)
{
    Rational result;
    result.num = lhs.num * rhs.den;
    result.den = lhs.den * rhs.num;
    result.negative = (lhs.negative && rhs.negative);
    result.reduce();
    return result;
}

bool operator < (const Rational& lhs, const Rational& rhs)
{
    float lhsFloat = float(lhs.num) / float(lhs.den);
    float rhsFloat = float(rhs.num) / float(rhs.den);
    if (lhs.negative) lhsFloat *= -1;
    if (rhs.negative) rhsFloat *= -1;
    return lhsFloat < rhsFloat;
}

bool operator < (const Rational& lhs, int constant)
{
    if ((lhs.num / lhs.den) < constant) return true;
    else return false;
}

bool operator > (const Rational& lhs, const Rational& rhs)
{
    float lhsFloat = float(lhs.num) / float(lhs.den);
    float rhsFloat = float(rhs.num) / float(rhs.den);
    if (lhs.negative) lhsFloat *= -1;
    if (rhs.negative) rhsFloat *= -1;
    return lhsFloat > rhsFloat;
}

bool operator > (const Rational& lhs, int constant)
{
    if ((lhs.num / lhs.den) > constant) return true;
    else return false;
}

// Constructors
Rational::Rational(): num(0), den(1), negative(false) {}

Rational::Rational(int num)
{
    if (num < 0)
    {
        this->num = (num * -1);
        this->negative = true;
    }
    else
    {
        this->num = num;
        this->negative = false;
    }
    this->den = 1;
    
}

Rational::Rational(int num, int den)
{
    if (den == 0) throw std::invalid_argument("Division by zero");
    this->num = num;
    this->den = den;
    // Track negatives
    if (this->num < 0 && this->den > 0)
    {
        this->num *= -1;
        this->negative = true;
    }
    else if (this->num > 0 && this->den < 0)
    {
        this->den *= -1;
        this->negative = true;
    }
    else if (this->num < 0 && this->den < 0)
    {
        this->num *= -1;
        this->den *= -1;
        this->negative = false;
    }
    else
    {
        this->negative = false;
    }
}

// Copy Constructor
Rational::Rational(const Rational& rhs): num(rhs.num), den(rhs.den), negative(rhs.negative) {}

// Assignment Operator
Rational& Rational::operator = (const Rational& rhs)
{
    if (this != &rhs) {
        this->num = rhs.num;
        this->den = rhs.den;
        this->negative = rhs.negative;
    }
    return *this;
}

// Increment (Pre)
Rational& Rational::operator ++ ()
{
    *this = *this + Rational(1);
    return *this;
}

// Increment (Post)
Rational Rational::operator ++ (int dummy)
{
    Rational result = *this;
    *this = *this + Rational(1);
    return result;
}

// Decrement (Pre)
Rational& Rational::operator -- ()
{
    *this = *this - Rational(1);
    return *this;
}

// Decrement (Post)
Rational Rational::operator -- (int dummy)
{
    Rational result = *this;
    *this = *this - Rational(1);
    return result;
}

bool Rational::getNegative() const { return this->negative; }

void Rational::setNegative(bool negative) { this->negative = negative; }

Rational Rational::reduce() const
{
    int gcd = GCD(num, den);
    Rational result = Rational(num / gcd, den / gcd);
    return result;
}

void Rational::reduce()
{
    int gcd = GCD(num, den);
    num /= gcd;
    den /= gcd;
}

// Used for displaying polynomials
std::string Rational::display() const
{
    if (den != 1) {
        int gcd = GCD(num, den);
        if ((den / gcd) == 1) // Denominator when simplified is 1
        {
            if (this->negative)
            {
                return "-" + std::to_string(num / gcd);
            }
            else
            {
                return std::to_string(num / gcd);
            }
        }
        else // Denominator is not 1 when simplified
        {
            if (this->negative) return "-" + std::to_string(num / gcd) + "/" + std::to_string(den / gcd);
            else return std::to_string(num / gcd) + "/" + std::to_string(den / gcd);
        }
    } else {
        if (this->negative) return "-" + std::to_string(num);
        else return std::to_string(num);
    }
}

// Rational to Double
double Rational::evaluate() const
{
    double result = num / double(den);
    return result;
}

}

