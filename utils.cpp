#include "EquationSolver.hpp"

bool EquationSolver::isOperator(char ch) const {
    return ch == '-' || ch == '+';
}

bool EquationSolver::isVariable(char ch) const {
    return ch == 'X' || ch == 'x';
}

bool EquationSolver::isExponentIndicator(char ch) const {
    return ch == '^';
}

bool EquationSolver::isDecimalPoint(char ch) const {
    return ch == '.';
}

bool EquationSolver::isEqualsSign(char ch) const {
    return ch == '=';
}

void EquationSolver::resetVariables() {
    coefficient = 0;
    exponent = 0;
    hasCoefficient = false;
    hasDecimal = false;
    decimalMultiplier = 0.1;
}

bool EquationSolver::rewind(char c) const
{
    if (c == '=' || c == 'x' || c == 'X' || c == '+' || c == '-' || c == '^')
        return (true);
    return (false);
}

bool EquationSolver::isThereRight(std::vector<Term>& parsedTerms) {
    for (const auto& term : parsedTerms) {
            if (term.isRightSideReduced) {
                return (true);
            }
        }

    return (false);
}

int EquationSolver::GetDegree() const {
    int degree = 0;

    for (const Term& term : parsedTerms) {
        if (term.exponent > degree) {
            degree = term.exponent;
        }
    }

    return (degree);
}

double EquationSolver::GetCoefficient(const std::vector<EquationSolver::Term>& terms, int exponent) {
    auto it = std::find_if(terms.begin(), terms.end(), [exponent](const EquationSolver::Term& term) {
        return term.exponent == exponent;
    });
    if (it != terms.end()) {
        return (it->coefficient);
    } else {
        return (0.0);
    }
}

void EquationSolver::addTermToList(std::vector<Term>& parsedTerms) {
    bool right = false;
    if (isRightSide)
        right = true;
    parsedTerms.push_back({coefficient, exponent, right});
    resetVariables();
}

std::vector<EquationSolver::Term> EquationSolver::SortTermsByExponent(const std::vector<Term>& terms) {
    std::vector<Term> sortedTerms = terms;

    std::sort(sortedTerms.begin(), sortedTerms.end(), [](const Term& a, const Term& b) {
        return a.exponent < b.exponent;
    });

    return (sortedTerms);
}