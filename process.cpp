#include "EquationSolver.hpp"

void EquationSolver::processEqualsSign(std::vector<Term>& parsedTerms) {
    if (coefficient != 0)
        addTermToList(parsedTerms);
}

void EquationSolver::processOperator(std::vector<Term>& parsedTerms, char ch) {
    if (ch == '-')
        NextCoefficient = '-';
    if (coefficient != 0)
        addTermToList(parsedTerms);
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
    i++;
    if (equation[i] == '-') {
        std::cout << "Error: By definition, a polynomial has non-negative integer exponents of variables" << std::endl;
        exit(1);
    }
    while (isspace(equation[i]))
        i++;
    if (!std::isdigit(equation[i])) {
        std::cout << "Error: Unknown Exponent Character: " << equation[i] << std::endl;
        exit(4);
    }
    while (std::isdigit(equation[i])) {
        exponent = exponent * 10 + (equation[i] - '0');
        i++;
    }
    return (i);
}

int EquationSolver::processDigit(const std::string& equation, int i) {
    bool isNegatif = false;

    if (i != 0 && equation[i - 1] == '-')
        isNegatif = true;
    while (canProcess(equation[i]) && equation[i]) {
        if (equation[i] == '.') {
            i++;
            while (canProcess(equation[i]) && equation[i]) {
                if (equation[i] == '.') {
                    std::cout << "Error: Multiple Decimal Point" << std::endl;
                    exit(2);
                }
                coefficient += (equation[i] - '0') * decimalMultiplier;
                decimalMultiplier *= 0.1;
                i++;
            }
            break;
        }
        coefficient = coefficient * 10 + (equation[i] - '0');
        i++;
    }
    if (isNegatif || NextCoefficient == '-')
        coefficient *= -1;
    NextCoefficient = '+';
    hasCoefficient = true;

    return (i);
}