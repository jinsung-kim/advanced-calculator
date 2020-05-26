//
//  Rational.hpp
//  Advanced Calculator
//
//  Created by Jin Kim on 5/25/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//

# ifndef Rational_hpp
# define Rational_hpp

# include <iostream>

namespace RationalC
{

class Rational
{
    friend std::ostream& operator << (std::ostream& os, const Rational& rhs);
    friend bool operator == (const Rational& lhs, const Rational& rhs);
    friend bool operator == (const Rational& lhs, int constant);
    friend bool operator != (const Rational& lhs, const Rational& rhs);
    friend bool operator != (const Rational& lhs, int constant);
    friend Rational operator + (const Rational& lhs, const Rational& rhs);
    friend Rational operator - (const Rational& lhs, const Rational& rhs);
    friend Rational operator * (const Rational& lhs, const Rational& rhs);
    friend Rational operator / (const Rational& lhs, const Rational& rhs);
    friend bool operator < (const Rational& lhs, int constant);
    friend bool operator > (const Rational& lhs, int constant);
public:
    // Constructors
    Rational();
    Rational(int, int);
    
    // Copy Control
    // Assignment Operator
    Rational& operator = (const Rational& rhs);
    
    // Copy Constructor
    Rational(const Rational& rhs);
    
    // Increment and decrement operators
    // Pre increment
    Rational& operator ++ ();
    // Post increment
    Rational operator ++ (int);
    // Pre decrement
    Rational& operator -- ();
    // Post decrement
    Rational operator -- (int);
    
    bool getNegative() const;
    
    // Reduces the fraction to its simplest form
    Rational reduce() const;
    void reduce();
    
    // String display
    std::string display() const;
    
    // Rational to Double Convert (For Polynomial Evaluation)
    double evaluate() const;
private:
    int num;
    int den;
    bool negative;
};

}

# endif
