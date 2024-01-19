#ifndef EQUATION_SOLVER_HPP
#define EQUATION_SOLVER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <complex>

class EquationSolver {
public:
    struct Term {
        double coefficient;
        int exponent;
    };

    EquationSolver(const std::string& equation);

    std::vector<Term> ParseInput();

    int GetDegree() const;

    static std::vector<Term> ReduceTerms(const std::vector<Term>& parsedTerms);

    static std::string WriteReducedEquation(const std::vector<Term>& reducedTerms);

    static void SolveQuadratic(double a, double b, double c);

    static void SolvePolynomial(const std::vector<EquationSolver::Term>& reducedTerms);

    static std::vector<Term> SortTermsByExponent(const std::vector<Term>& terms);
private:
    std::vector<Term> parsedTerms;
    std::string equation;
    double coefficient;
    int exponent;
    bool isNegativeCoefficient;
    bool hasCoefficient;
    bool hasDecimal;
    double decimalMultiplier;
    bool isRightSide;
    char NextCoefficient;

    bool isOperator(char ch) const;

    bool isVariable(char ch) const;

    bool isExponentIndicator(char ch) const;

    bool isDecimalPoint(char ch) const;

    bool isEqualsSign(char ch) const;

    bool rewind(char c) const;

    static double GetCoefficient(const std::vector<EquationSolver::Term>& terms, int exponent);

    void addTermToList(std::vector<Term>& parsedTerms);

    void resetVariables();

    void processEqualsSign(std::vector<Term>& parsedTerms);

    void processOperator(std::vector<Term>& parsedTerms, char ch);

    void processVariable(const std::string& equation, int i);

    int processExponentIndicator(const std::string& equation, int i);

    bool canProcess(char c);

    int processDigit(const std::string& equation, int i);
};

#endif // EQUATION_SOLVER_HPP
