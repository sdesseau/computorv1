#include "EquationSolver.hpp"

EquationSolver::EquationSolver(const std::string& equation)
    : equation(equation), coefficient(0), exponent(0), isNegativeCoefficient(false),
      hasCoefficient(false), hasDecimal(false), decimalMultiplier(0.1),
      isRightSide(false), NextCoefficient('+') {}

std::vector<EquationSolver::Term> EquationSolver::ParseInput() {
    for (int i = 0; equation[i]; i++) {
        if (equation[i]) {
            char ch = equation[i];
// std::cout << "Error: Unknown Character: " << i << std::endl;
// std::cout<< "In ParseInput: ch: " << ch << std::endl;
            if (isEqualsSign(ch)) {
                processEqualsSign(parsedTerms);
                isRightSide = true;
            } else if (isOperator(ch)) {
                processOperator(parsedTerms, ch);
            } else if (isVariable(ch)) {
                processVariable(equation, i);
            } else if (isExponentIndicator(ch)) {
                i = processExponentIndicator(equation, i);
                if (rewind(equation[i]))
                    i--;
            } else if (std::isdigit(ch) || isDecimalPoint(ch)) {
               i = processDigit(equation, i);
               if (rewind(equation[i]))
                    i--;
            } else if (ch != ' ' && ch != '*') {
                if (equation[i - 1] == '\0')
                    break;
                std::cout << "Error: Unknown Character: " << ch << std::endl;
                exit(3);
            }
        }
    }
    if (coefficient != 0)
        addTermToList(parsedTerms);

    return (parsedTerms);
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

std::vector<EquationSolver::Term> EquationSolver::ReduceTerms(const std::vector<Term>& parsedTerms) {
    std::vector<Term> reducedTerms;

    for (const Term& term : parsedTerms) {
        bool found = false;

        for (Term& reducedTerm : reducedTerms) {
            if (reducedTerm.exponent == term.exponent) {
                reducedTerm.coefficient += term.coefficient;
                found = true;
                break;
            }
        }
        if (!found)
            reducedTerms.push_back(term);
    }

    return (reducedTerms);
}

std::string EquationSolver::WriteReducedEquation(const std::vector<Term>& reducedTerms) {
    std::vector<Term> sortedTerms = reducedTerms;
    std::sort(sortedTerms.begin(), sortedTerms.end(), [](const Term& a, const Term& b) {
        return a.exponent < b.exponent;
    });

    std::ostringstream equationStream;
    bool isFirstTerm = true;
    bool allCoefficientsZero = true;

    for (const Term& term : sortedTerms) {
        if (term.coefficient != 0) {
            allCoefficientsZero = false;
            if (term.coefficient > 0) {
                if (!isFirstTerm)
                    equationStream << " + ";
            } else {
                equationStream << " - ";
            }
            double absCoefficient = std::abs(term.coefficient);
            if (absCoefficient != 1 || term.exponent == 0) {
                equationStream << absCoefficient;
            }
            if (term.exponent > 0) {
                equationStream << "X";
                if (term.exponent > 1) {
                    equationStream << "^" << term.exponent;
                }
            }
            isFirstTerm = false;
        }
    }
    if (!allCoefficientsZero)
        equationStream << " = 0";

    return (equationStream.str());
}

void EquationSolver::SolveQuadratic(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double root2 = (-b - std::sqrt(discriminant)) / (2 * a);
        std::cout << "Discriminant is positive, two real roots:" << std::endl;
        std::cout << "Root 1: " << root1 << std::endl;
        std::cout << "Root 2: " << root2 << std::endl;
    } 
    else if (discriminant == 0) {
        double root = -b / (2 * a);
        std::cout << "Discriminant is zero, one real root:" << std::endl;
        std::cout << "Root: " << root << std::endl;
    } 
    else {
        std::cout << "Discriminant is negative, two complex roots:" << std::endl;
        std::complex<double> root1(-b / (2 * a), std::sqrt(-discriminant) / (2 * a));
        std::complex<double> root2(-b / (2 * a), -std::sqrt(-discriminant) / (2 * a));
        std::cout << "Root 1: " << root1 << std::endl;
        std::cout << "Root 2: " << root2 << std::endl;
    }
}

std::vector<EquationSolver::Term> EquationSolver::SortTermsByExponent(const std::vector<Term>& terms) {    std::vector<Term> sortedTerms = terms;

    std::sort(sortedTerms.begin(), sortedTerms.end(), [](const Term& a, const Term& b) {
        return a.exponent < b.exponent; // Trie par ordre décroissant des exponents
    });

    return sortedTerms;
}

void EquationSolver::SolvePolynomial(const std::vector<EquationSolver::Term>& reducedTerms) {
    if (reducedTerms.empty()) {
        std::cout << "The polynomial is zero everywhere." << std::endl;
        return ;
    }
    std::vector<Term> sortedTerms = SortTermsByExponent(reducedTerms);
    int maxExponent = 0;
    for (auto it = sortedTerms.begin(); it != sortedTerms.end(); ) {
        if (it->coefficient == 0) {
            it = sortedTerms.erase(it);
        } else {
            maxExponent = std::max(maxExponent, it->exponent);
            ++it;
        }
    }
    std::cout << "Polynomial Degree : " << maxExponent << std::endl;
    if (maxExponent > 2)
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
    else if (maxExponent == 2) {
        double a = GetCoefficient(sortedTerms, 2);
        double b = GetCoefficient(sortedTerms, 1);
        double c = GetCoefficient(sortedTerms, 0);
        std::cout << "Solving quadratic equation: ";
        if (a != 0) {
            std::cout << a << "X^2";
        }
        if (b != 0) {
            if (a != 0) {
                std::cout << (b > 0 ? " + " : " - ");
            }
            std::cout << std::abs(b) << "X";
        }
        if (c != 0) {
            if (a != 0 || b != 0) {
                std::cout << (c > 0 ? " + " : " - ");
            }
            std::cout << std::abs(c);
        }
        std::cout << " = 0" << std::endl;
        SolveQuadratic(a, b, c);
    }
    else if (maxExponent == 1) {
        double a = GetCoefficient(sortedTerms, 1);
        double b = GetCoefficient(sortedTerms, 0);
        std::cout << "Solving linear equation: ";
        if (a != 0) {
            std::cout << a << "X";
        }
        if (b != 0) {
            if (a != 0) {
                std::cout << (b > 0 ? " + " : " - ");
            }
            std::cout << std::abs(b);
        }
        std::cout << " = 0" << std::endl;        if (a == 0) {
            if (b == 0)
                std::cout << "The equation has infinitely many solutions." << std::endl;
            else
                std::cout << "The equation has no solution." << std::endl;
        } else {
            double root = -b / a;
            std::cout << "The solution is X = " << root << std::endl;
        }
    }
    else
        std::cout << "The equation is constant, no variable X." << std::endl;
}

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

double EquationSolver::GetCoefficient(const std::vector<EquationSolver::Term>& terms, int exponent) {
    auto it = std::find_if(terms.begin(), terms.end(), [exponent](const EquationSolver::Term& term) {
        return term.exponent == exponent;
    });

    if (it != terms.end()) {
        return it->coefficient;
    } else {
        return 0.0;
    }
}

void EquationSolver::addTermToList(std::vector<Term>& parsedTerms) {
    if (isRightSide) {
        coefficient *= -1;
    }
// std::cout<< "Added Term: Coefficient = " << coefficient << ", Exponent = " << exponent << std::endl;
    parsedTerms.push_back({coefficient, exponent});
    resetVariables();
}

void EquationSolver::resetVariables() {
    coefficient = 0;
    exponent = 0;
    isNegativeCoefficient = false;
    hasCoefficient = false;
    hasDecimal = false;
    decimalMultiplier = 0.1;
}

void EquationSolver::processEqualsSign(std::vector<Term>& parsedTerms) {
// std::cout<< "Processing Equals Sign" << std::endl;
    addTermToList(parsedTerms);
}

void EquationSolver::processOperator(std::vector<Term>& parsedTerms, char ch) {
// std::cout<< "Processing Operator" << std::endl;
    if (ch == '-')
        NextCoefficient = '-';
    addTermToList(parsedTerms);
    isNegativeCoefficient = (equation[equation.find_last_of("+-") - 1] == '-');
}

void EquationSolver::processVariable(const std::string& equation, int i) {
// std::cout<< "Processing Variable" << std::endl;
    if (hasCoefficient == false)
        coefficient = 1;
    if (NextCoefficient == '-')
        coefficient *= -1;
    if (equation[i + 1] != '^')
        exponent = 1;
// std::cout << "Coefficient: " << coefficient << std::endl;
    hasCoefficient = true;
    NextCoefficient = '+';
}

int EquationSolver::processExponentIndicator(const std::string& equation, int i) {
// std::cout<< "Processing Exponent Indicator" << std::endl;
    i++;
    if (equation[i] == '-') {
        std::cout << "Error: By definition, a polynomial has non-negative integer exponents of variables" << std::endl;
        exit(1);
    }
    if (!std::isdigit(equation[i])) {
        std::cout << "Error: Unknown Exponent Character: " << equation[i] << std::endl;
        exit(4);
    }
    while (std::isdigit(equation[i])) {
        exponent = exponent * 10 + (equation[i] - '0');
        i++;
    }
// std::cout << "Exponent: " << exponent << std::endl;
    return (i);
}

bool EquationSolver::canProcess(char c) {
    if (c == ' ' || c == '*' || c == 'X' || c == '=' || c == 'x' || c == '^')
        return (false);
    return (true);
}

int EquationSolver::processDigit(const std::string& equation, int i) {
// std::cout<< "Processing Digit: " << equation[i] << std::endl;
// std::cout<< "Coeff " << coefficient << std::endl;
// std::cout<< "decimalMultiplier: " << decimalMultiplier << std::endl;
// std::cout<< "Exponent: " << exponent << std::endl;
    bool isNegatif = false;

    if (equation[i - 1] == '-')
        isNegatif = true;
    while (canProcess(equation[i]) && equation[i]) {
        if (equation[i] == '.') {
            i++;
// std::cout<< "Decimal Found" << std::endl;
            while (canProcess(equation[i]) && equation[i]) {
                if (equation[i] == '.') {
                    std::cout << "Error: Multiple Decimal Point" << std::endl;
                    exit(2);
                }
                coefficient += (equation[i] - '0') * decimalMultiplier;
                decimalMultiplier *= 0.1;
                i++;
// std::cout<< "Coeff Decimal:" << coefficient << std::endl;
            }
            break;
        }
//  std::cout << "NewCoeff1: " << coefficient << std::endl;
        coefficient = coefficient * 10 + (equation[i] - '0');
//  std::cout << "NewCoeff2: " << coefficient << std::endl;
// std::cout<< "I1: " << i << std::endl;
        i++;
// std::cout<< "2I: " << i << std::endl;
    }

    if (isNegatif)
        coefficient *= -1;

    if (NextCoefficient == '-')
        coefficient *= -1;

    NextCoefficient = '+';
// std::cout<< "Processing Digit2: " << equation[i] << std::endl;
    hasCoefficient = true;
    return (i);
}

bool EquationSolver::rewind(char c) const
{
    if (c == '=' || c == 'x' || c == 'X' || c == '+' || c == '-' || c == '^')
        return (true);
    return (false);
}
