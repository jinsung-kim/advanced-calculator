//
//  Rational.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <iostream>
# include <exception>

# include "Rational.hpp"

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
        if (max % a == 0 && max % b == 0) return max;
        else ++max;
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
    if (result.num < 0) result.negative = true;
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
    if (lhs.negative && rhs.negative) result.negative = false;
    else if (lhs.negative) result.negative = true;
    else if (rhs.negative) result.negative = true;
    else result.negative = false;
    result.reduce();
    return result;
}

// Division
Rational operator / (const Rational& lhs, const Rational& rhs)
{
    Rational result;
    result.num = lhs.num * rhs.den;
    result.den = lhs.den * rhs.num;
    if (lhs.negative && rhs.negative) result.negative = false;
    else if (lhs.negative) result.negative = true;
    else if (rhs.negative) result.negative = true;
    else result.negative = false;
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

Rational::Rational(const std::string& input)
{
    if (input == "-")
    {
        this->num = 1;
        this->den = 1;
        this->negative = true;
    }
    else if (input == "")
    {
        this->num = 1;
        this->den = 1;
        this->negative = false;
    }
    else if (input.find('-') != std::string::npos) // Negatives
    {
        if (input.find('/') != std::string::npos) // Fraction
        {
            int num = std::stoi(input.substr(0, input.find('/')));
            int den = std::stoi(input.substr(input.find('/') + 1));
            if (num < 0 || den < 0)
            {
                num *= -1;
                den *= -1;
                this->negative = false;
            }
            else if (num < 0)
            {
                num *= -1;
                this->negative = true;
            }
            else if (den < 0)
            {
                den *= -1;
                this->negative = true;
            }
            else
            {
                this->negative = false;
            }
            this->num = num;
            this->den = den;
        }
        else // Whole number
        {
            int num = std::stoi(input);
            if (num < 0)
            {
                num *= -1;
                this->negative = true;
            }
            else
            {
                this->negative = false;
            }
            this->num = num;
            this->den = 1;
        }
    }
    else if (input.find('/') != std::string::npos) // Positive Fraction
    {
        int num = std::stoi(input.substr(0, input.find('/')));
        int den = std::stoi(input.substr(input.find('/') + 1));
        this->num = num;
        this->den = den;
        this->negative = false;
    }
    else // Whole number
    {
        this->num = std::stoi(input);
        this->den = 1;
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

// Getters
bool Rational::getNegative() const { return this->negative; }
int Rational::getNum() const { return this->num; }
int Rational::getDen() const { return this->den; }

// Setters
void Rational::setNegative(bool negative) { this->negative = negative; }
void Rational::setNum(int num) { this->num = num; }
void Rational::setDen(int den) { this->den = den; }

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
// Does not consider negative signs
std::string Rational::display() const
{
    int n = abs(num);
    int d = abs(den);
    int gcd = GCD(n, d);
    n /= gcd;
    d /= gcd;
    if (d == 1) // Number is not a fraction
    {
        return std::to_string(n);
    }
    else // Result will be a fraction
    {
        return std::to_string(n) + "/" + std::to_string(d);
    }
}

std::string Rational::displayWithNegative() const
{
    if (this->den == 1)
    {
        if (this->negative) return "-" + std::to_string(this->num);
        else return std::to_string(this->num);
    }
    else
    {
        if (this->negative) return "-" + std::to_string(this->num) + "/" + std::to_string(this->den);
        else return std::to_string(this->num) + "/" + std::to_string(this->den);
    }
}

// Rational to Double
float Rational::evaluate() const
{
    float result = float(num) / float(den);
    if (this->negative) result *= -1;
    return result;
}

}

