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
    friend std::ostream& operator << (std::ostream&, const Rational&);
    friend bool operator == (const Rational&, const Rational&);
    friend bool operator == (const Rational&, int);
    friend bool operator != (const Rational&, const Rational&);
    friend bool operator != (const Rational&, int);
    friend Rational operator + (const Rational&, const Rational&);
    friend Rational operator - (const Rational&, const Rational&);
    friend Rational operator * (const Rational&, const Rational&);
    friend Rational operator / (const Rational&, const Rational&);
    friend bool operator < (const Rational&, const Rational&);
    friend bool operator < (const Rational&, int);
    friend bool operator > (const Rational&, const Rational&);
    friend bool operator > (const Rational&, int);
public:
    // Constructors
    Rational();
    Rational(int);
    Rational(int, int);
    Rational(const std::string&);
    
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
    
    // Getters
    bool getNegative() const;
    int getNum() const;
    int getDen() const;
    
    // Setters
    void setNegative(bool);
    void setNum(int);
    void setDen(int);
    
    // Reduces the fraction to its simplest form
    Rational reduce() const;
    void reduce();
    
    // String display
    std::string display() const;
    
    // Rational to Double Convert (For Polynomial Evaluation)
    float evaluate() const;
private:
    int num;
    int den;
    bool negative;
};

}

# endif
