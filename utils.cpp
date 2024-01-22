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

bool EquationSolver::canProcess(char c) {
    if (c == ' ' || c == '*' || c == 'X' || c == '=' || c == 'x' || c == '^')
        return (false);
    return (true);
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

int EquationSolver::pgcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Fonction pour déterminer si un double peut être représenté comme une fraction
bool EquationSolver::isFractionInteresting(double num) {
    const double epsilon = 1e-6; // Marge d'erreur acceptable

    // Vérifier si le nombre est proche d'un entier
    if (std::fabs(num - std::round(num)) < epsilon) {
        return true;
    }

    // Convertir le double en fraction
    int numerator = static_cast<int>(std::round(num * 1e6)); // Multiplier par 1e6 pour conserver les décimales
    int denominator = 1e6;

    // Simplifier la fraction en utilisant le PGCD
    int commonDivisor = pgcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;

    // Vérifier si la fraction simplifiée est proche du nombre d'origine
    return std::fabs(num - static_cast<double>(numerator) / denominator) < epsilon;
}

// double EquationSolver::printRoot(double root) {
//     if (isFractionInteresting(root))
//     {

//     }
// {