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
