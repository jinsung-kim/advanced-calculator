//
//  Expression.cpp
//  Advanced Calculator
//
//  Created by Jin Kim on 6/1/20.
//  Copyright © 2020 Jin Kim. All rights reserved.
//
# include <iostream>
# include <string>
# include <vector>
# include <stack>
# include <exception>
# include <algorithm>
# include <unordered_map>

# include "Expression.hpp"
# include "Exponential.hpp"
# include "Indeterminant.hpp"
# include "Polynomial.hpp"
# include "Rational.hpp"

using namespace ExponentialC;
using namespace IndeterminantC;
using namespace RationalC;
using namespace PolynomialC;
using namespace LogarithmC;
using namespace NaturalLogC;

const std::string validVariables = "abcdefghijklmnopqrstuvwxyz";

namespace ExpressionC
{

std::ostream& operator << (std::ostream& os, Expression& rhs)
{
    std::string result = "";
    for (size_t i = 0; i < rhs.negative.size(); i++)
    {
        for (size_t j = 0; j < rhs.rationals[i].size(); j++)
        {
            if (j == rhs.rationals[i].size() - 1) result = result + "(" + rhs.rationals[i][j].display() + ")";
            else result = result + "(" + rhs.rationals[i][j].display() + ")*";
        }
        for (size_t j = 0; j < rhs.exponentials[i].size(); j++)
        {
            if (j == rhs.exponentials[i].size() - 1) result = result + "(" + rhs.exponentials[i][j].display() + ")";
            else result = result + "(" + rhs.exponentials[i][j].display() + ")*";
        }
        for (size_t j = 0; j < rhs.logs[i].size(); j++)
        {
            if (j == rhs.logs[i].size() - 1) result = result + "(" + rhs.logs[i][j].display() + ")";
            else result = result + "(" + rhs.logs[i][j].display() + ")*";
        }
        for (size_t j = 0; j < rhs.naturals[i].size(); j++)
        {
            if (j == rhs.naturals[i].size() - 1) result = result + "(" + rhs.naturals[i][j].display() + ")";
            else result = result + "(" + rhs.naturals[i][j].display() + ")*";
        }
        for (size_t j = 0; j < rhs.polynomials[i].size(); j++)
        {
            if (j == rhs.polynomials[i].size() - 1) result = result + "(" + rhs.polynomials[i][j].display() + ")";
            else result = result + "(" + rhs.polynomials[i][j].display() + ")*";
        }
        if (rhs.negative[i] == true) result += "-";
        else result += "+";
    }
    size_t last = rhs.negative.size();
    for (size_t j = 0; j < rhs.rationals[last].size(); j++)
    {
        if (j == rhs.rationals[last].size() - 1) result = result + "(" + rhs.rationals[last][j].display() + ")";
        else result = result + "(" + rhs.rationals[last][j].display() + ")*";
    }
    for (size_t j = 0; j < rhs.exponentials[last].size(); j++)
    {
        if (j == rhs.exponentials[last].size() - 1) result = result + "(" + rhs.exponentials[last][j].display() + ")";
        else result = result + "(" + rhs.exponentials[last][j].display() + ")*";
    }
    for (size_t j = 0; j < rhs.logs[last].size(); j++)
    {
        if (j == rhs.logs[last].size() - 1) result = result + "(" + rhs.logs[last][j].display() + ")";
        else result = result + "(" + rhs.logs[last][j].display() + ")*";
    }
    for (size_t j = 0; j < rhs.naturals[last].size(); j++)
    {
        if (j == rhs.naturals[last].size() - 1) result = result + "(" + rhs.naturals[last][j].display() + ")";
        else result = result + "(" + rhs.naturals[last][j].display() + ")*";
    }
    for (size_t j = 0; j < rhs.polynomials[last].size(); j++)
    {
        if (j == rhs.polynomials[last].size() - 1) result = result + "(" + rhs.polynomials[last][j].display() + ")";
        else result = result + "(" + rhs.polynomials[last][j].display() + ")*";
    }
    if (result == "") os << "0";
    else os << result;
    return os;
}

/*
 Example inputs:
 (2^x)*(x^3+2x) + (log(x))*(3/4)
 (ln(2x))*(e^3x) + (1/3)*(3/4x^3)
 */
Expression::Expression(std::string input)
{
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    std::string split = "";
    std::vector<std::string> terms;
    std::vector<size_t> termIndex;
    std::stack<char> start;
    size_t currTerm = 0;
    bool validLog = false;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] == '(') // Start of a term
        {
            if (start.empty() == false) // There is a ln or log function here
            {
                if (start.top() == '(') split += input[i]; validLog = true;
            }
            else if (start.empty()) // There is a regular term here (Polynomial, exponential, rational)
            {
                start.push('('); // We want to recognize that this starts a new valid term
            }
        }
        else if (input[i] == ')') // End of a term
        {
            if (validLog) split += input[i]; validLog = false;
            if (split != "")
            {
                terms.push_back(split);
                termIndex.push_back(currTerm);
                split = "";
                start.pop();
            }
        }
        else if (input[i] == '+' || input[i] == '-') // Term has ended
        {
            if (start.empty() == false) // In the middle of a polynomial function
            {
                split += input[i];
            }
            else
            {
                if (input[i] == '+') this->negative.push_back(false);
                else this->negative.push_back(true);
                currTerm++;
            }
        }
        else // In between a term
        {
            if (input[i] != '*') split += input[i];
        }
    }
    size_t i = 0;
    for (const std::string& term: terms)
    {
        if (term.find('^') != std::string::npos) // Polynomial or Exponential
        {
            /*
             Ex: x^2+3x^4+2x
             Ex: 2^x
             If a character is found before the first '^', it must be a polynomial
             If the character is found after, then it must be exponential
             */
            if (term.find_first_of(validVariables) < term.find_first_of('^'))
            {
                auto toAdd = new Polynomial(term);
                auto vec = this->polynomials[termIndex[i]];
                vec.push_back(*toAdd);
                this->polynomials[termIndex[i]] = vec;
            }
            else
            {
                auto toAdd = new Exponential(term);
                auto vec = this->exponentials[termIndex[i]];
                vec.push_back(*toAdd);
                this->exponentials[termIndex[i]] = vec;
                
            }
        }
        else if (term.find("log") != std::string::npos) // Log Function
        {
            // Ex: log(3x)
            auto toAdd = new Logarithm(term);
            auto vec = this->logs[termIndex[i]];
            vec.push_back(*toAdd);
            this->logs[termIndex[i]] = vec;
        }
        else if (term.find("ln") != std::string::npos) // Natural log Function
        {
            // Ex: ln(x)
            auto toAdd = new NaturalLog(term);
            auto vec = this->naturals[termIndex[i]];
            vec.push_back(*toAdd);
            this->naturals[termIndex[i]] = vec;
        }
        else // Assuming there is no exponent, this must be a rational
        {
            // Ex: 1/3
            auto toAdd = new Rational(term);
            auto vec = this->rationals[termIndex[i]];
            vec.push_back(*toAdd);
            this->rationals[termIndex[i]] = vec;
        }
        i++;
    }
}

}
