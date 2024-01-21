#include "EquationSolver.hpp"

EquationSolver::EquationSolver(const std::string& equation)
    : equation(equation), coefficient(0), exponent(0),
      hasCoefficient(false), hasDecimal(false), decimalMultiplier(0.1),
      isRightSide(false), NextCoefficient('+') {}

std::vector<EquationSolver::Term> EquationSolver::ParseInput() {
    for (int i = 0; equation[i]; i++) {
        if (equation[i]) {
            char ch = equation[i];
            if (isEqualsSign(ch)) {
                processEqualsSign(parsedTerms);
                isRightSide = true;
            } else if (isOperator(ch)) {
                processOperator(parsedTerms, ch);
            } else if (isVariable(ch)) {
                i = processVariable(equation, i);
                if (exponent == 1)
                    addTermToList(parsedTerms);
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

void EquationSolver::WriteEquation(const std::vector<Term>& terms) {
    bool isFirstTerm = true;
    int i = 0;

    for (const auto& term : terms) {
        if (!term.isRightSideReduced) {
            if (!isFirstTerm || term.coefficient < 0) {
                if (term.coefficient >= 0) {
                    std::cout << " + ";
                } else {
                    if (!isFirstTerm)
                        std::cout << " - ";
                    else
                        std::cout << "-";
                }
            }
            std::cout << std::abs(term.coefficient);
            if (term.exponent > 0) {
                std::cout << " * X^" << term.exponent;
            }
            isFirstTerm = false;
        }
        i++;
    }
    if (i == 0)
        std::cout << "0";
    i = 0;
    std::cout << " = ";
    isFirstTerm = true;
    for (const auto& term : terms) {
        if (term.isRightSideReduced) {
            if (!isFirstTerm || term.coefficient < 0) {
                if (term.coefficient >= 0) {
                    std::cout << " + ";
                } else {
                    if (!isFirstTerm)
                        std::cout << " - ";
                    else
                        std::cout << "-";
                }
            }
            std::cout << std::abs(term.coefficient);
            if (term.exponent > 0) {
                std::cout << " * X^" << term.exponent;
            }
            isFirstTerm = false;
            i++;
        }
    }
    if (i == 0)
        std::cout << "0";
    std::cout << std::endl;
}

bool EquationSolver::isThereRight(std::vector<Term>& parsedTerms) {
    for (const auto& term : parsedTerms) {
            if (term.isRightSideReduced) {
                return (true);
            }
        }

    return (false);
}

std::vector<EquationSolver::Term> EquationSolver::ReduceVector(const std::vector<Term>& parsedTerms) {
    std::vector<Term> reducedTerms;

    for (const Term& term : parsedTerms) {
        bool found = false;
        for (Term& reducedTerm : reducedTerms) {
            if (reducedTerm.exponent == term.exponent && reducedTerm.isRightSideReduced == term.isRightSideReduced) {
                reducedTerm.coefficient += term.coefficient;
                reducedTerm.isRightSideReduced = term.isRightSideReduced;
                found = true;
                break;
            }
        }
        if (!found)
            reducedTerms.push_back(term);
    }
    reducedTerms.erase(std::remove_if(reducedTerms.begin(), reducedTerms.end(),
        [](const Term& term) { return term.coefficient == 0; }),
        reducedTerms.end());

    return (reducedTerms);
}

std::vector<EquationSolver::Term> EquationSolver::ReduceTerms(std::vector<Term>& parsedTerms) {
    std::vector<Term> updatedTerms;

    for (const auto& term : parsedTerms) {;
        if (!term.isRightSideReduced)
            updatedTerms.push_back(term);
    }
    for (const auto& term : parsedTerms) {
        if (term.isRightSideReduced)
            updatedTerms.push_back(term);
    }
    std::cout << "Equation: ";
    WriteEquation(updatedTerms);
    std::cout << std::endl;
    while (isThereRight(parsedTerms)) {
        for (const auto& term : parsedTerms) {
            if (term.isRightSideReduced) {
            updatedTerms.push_back({-term.coefficient, term.exponent, false});
            updatedTerms.push_back({-term.coefficient, term.exponent, true});
            #if STEPS
                std::cout << "Equation Reduced Intermediaire Step: ";
                WriteEquation(updatedTerms);
                std::cout << std::endl;
            #endif
            updatedTerms = ReduceVector(updatedTerms);
            #if STEPS
                std::cout << "Equation Reduced Intermediaire Step: ";
                WriteEquation(updatedTerms);
                std::cout << std::endl;
            #endif
            }
        }
        parsedTerms = updatedTerms;
    }
    parsedTerms = ReduceVector(parsedTerms);

    return (parsedTerms);
}

std::string EquationSolver::WriteReducedEquation(const std::vector<Term>& reducedTerms) {
    std::vector<Term> sortedTerms = reducedTerms;
    std::ostringstream equationStream;
    bool isFirstTerm = true;
    bool allCoefficientsZero = true;

    std::sort(sortedTerms.begin(), sortedTerms.end(), [](const Term& a, const Term& b) {
        return a.exponent < b.exponent;
    });
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
    else
        equationStream << "0 = 0";

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

std::vector<EquationSolver::Term> EquationSolver::SortTermsByExponent(const std::vector<Term>& terms) {
    std::vector<Term> sortedTerms = terms;

    std::sort(sortedTerms.begin(), sortedTerms.end(), [](const Term& a, const Term& b) {
        return a.exponent < b.exponent;
    });

    return (sortedTerms);
}

void EquationSolver::SolvePolynomial(const std::vector<EquationSolver::Term>& reducedTerms) {
    int maxExponent = 0;

    if (reducedTerms.empty()) {
        std::cout << "The polynomial is zero everywhere." << std::endl;
        return ;
    }
    std::vector<Term> sortedTerms = SortTermsByExponent(reducedTerms);
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
            if (root == -0)
                root = 0;
            std::cout << "The solution is X = " << root << std::endl;
        }
    }
    else {
        std::cout << "The equation is constant, no variable X." << std::endl;
        if (sortedTerms.front().coefficient != 0)
            std::cout << sortedTerms.front().coefficient << " is not equal to 0, dummy !" << std::endl;
    }
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
    if (isNegatif)
        coefficient *= -1;
    if (NextCoefficient == '-')
        coefficient *= -1;
    NextCoefficient = '+';
    hasCoefficient = true;

    return (i);
}