#include "EquationSolver.hpp"

void EquationSolver::processEqualsSign(std::vector<Term>& parsedTerms) {
    if (coefficient != 0)
        addTermToList(parsedTerms);
    resetVariables();
}

void EquationSolver::processOperator(std::vector<Term>& parsedTerms, char ch) {
    if (ch == '-'){
        if (NextCoefficient == '+')
            NextCoefficient = '-';
        else
            NextCoefficient = '+';
    }
    if (coefficient != 0)
        addTermToList(parsedTerms);
    else
        resetVariables();
}

int EquationSolver::processVariable(const std::string& equation, int i) {
    if (hasCoefficient == false) {
        coefficient = 1;
        if (NextCoefficient == '-')
            coefficient *= -1;
    }
    if (equation[i + 1] != '^') {
        exponent = 1;
        if (equation[i + 1] == 'X' || equation[i + 1] == 'x') {
            i++;
            while (equation[i] == 'X' || equation[i] == 'x') {
                exponent++;
                i++;
            }
        }
    }
    hasCoefficient = true;
    NextCoefficient = '+';
    return (i);
}

int EquationSolver::processExponentIndicator(const std::string& equation, int i) {
    int nextExponent = 0;
    
    i++;
    if (equation[i] == '-')
        throw std::runtime_error("Error: By definition, a polynomial has non-negative integer exponents of variables");
    while (isspace(equation[i]))
        i++;
    if (!std::isdigit(equation[i]))
            throw std::runtime_error("Error: Unknown Exponent Character: " + std::string(1, equation[i]));
    while (equation[i] && std::isdigit(equation[i])) {
        if (nextExponent > (2147483647 - (equation[i] - '0')) / 10)
            throw std::runtime_error("Error: Exponent out of range for signed 32-bit integer.");
        nextExponent = nextExponent * 10 + (equation[i] - '0');
        i++;
        if (equation[i] == '.' || equation[i] == '*')
            throw std::runtime_error("Error: Sorry, not implemented yet !");
    }
    if (equation[i] && !canProcessExponent(equation[i]))
        throw std::runtime_error("Unknown Exponent Character: " + std::string(1, equation[i]));

    if (exponent != 0)
        exponent *= nextExponent;
    else
        exponent = nextExponent;

    return (i);
}

int EquationSolver::processDigit(const std::string& equation, int i) {
    bool isNegatif = false;
    bool oldCoeff = false;
    double oldCoeffDouble = 0;

    if (coefficient) {
        oldCoeff = true;
        oldCoeffDouble = coefficient;
        coefficient = 0;
    }
    while (canProcess(equation[i]) && equation[i]) {
        if (equation[i] == '.') {
            i++;
            while (canProcess(equation[i]) && equation[i]) {
                if (equation[i] == '.')
                    throw std::runtime_error("Error: Multiple Decimal Point");
                else if (!std::isdigit(equation[i]))
                    throw std::runtime_error("Error: Bad Coeff Character: " + std::string(1, equation[i]));
                coefficient += (equation[i] - '0') * decimalMultiplier;
                decimalMultiplier *= 0.1;
                i++;
            }
            break;
        } else if (!std::isdigit(equation[i])) {
            throw std::runtime_error("Error: Bad Coeff Character: " + std::string(1, equation[i]));
        }
        coefficient = coefficient * 10 + (equation[i] - '0');
        i++;
    }
    if (isNegatif || NextCoefficient == '-')
        coefficient *= -1;
    NextCoefficient = '+';
    hasCoefficient = true;


    if (oldCoeff)
        coefficient *= oldCoeffDouble;
    return (i);
}

bool EquationSolver::canProcess(char c) {
    if (c == ' ' || c == '*' || c == 'X' || c == '=' || c == 'x' || c == '^' || c == '+' || c == '-')
        return (false);
    return (true);
}

bool EquationSolver::canProcessExponent(char c) {
    if (c != ' ' && c != '+' && c != '-' && c != '=' && c != '^')
        return (false);
    return (true);
}