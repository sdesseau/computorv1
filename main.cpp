#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <complex>

class EquationParser {
public:

    struct Term {
            double coefficient;
            int exponent;
        };

    EquationParser(const std::string& equation) : equation(equation) {}

    std::vector<Term> ParseInput() {

        for (int i = 0; equation[i]; i++) {
            char ch = equation[i];
            // std::cout << "In ParseInput: ch: " << ch << std::endl;
            if (isEqualsSign(ch)) {
                processEqualsSign(parsedTerms);
                isRightSide = true;
            } else if (isOperator(ch)) {
                processOperator(parsedTerms);
            } else if (isVariable(ch)) {
                processVariable(equation, i);
            } else if (isExponentIndicator(ch)) {
                i = processExponentIndicator(equation, i);
            } else if (std::isdigit(ch) || isDecimalPoint(ch)) {
               i = processDigit(equation, i);
            }
        }

        // Ajouter le dernier terme à la liste
        if (hasCoefficient) {
            if (isNegativeCoefficient) {
                coefficient = -coefficient;
            }
            addTermToList(parsedTerms);
        }

        return parsedTerms;
    }

    int GetDegree() const {
        int degree = 0;

        for (const Term& term : parsedTerms) {
            if (term.exponent > degree) {
                degree = term.exponent;
            }
        }

        return degree;
    }

    static std::vector<Term> ReduceTerms(const std::vector<Term>& parsedTerms) {
        std::vector<Term> reducedTerms;

        for (const Term& term : parsedTerms) {
            // Vérifier si un terme du même degré existe déjà dans reducedTerms
            bool found = false;
            for (Term& reducedTerm : reducedTerms) {
                if (reducedTerm.exponent == term.exponent) {
                    reducedTerm.coefficient += term.coefficient;
                    found = true;
                    break;
                }
            }

            // Si le terme du même degré n'a pas été trouvé, l'ajouter à reducedTerms
            if (!found) {
                reducedTerms.push_back(term);
            }
        }

        return reducedTerms;
    }

    static std::string WriteReducedEquation(const std::vector<Term>& reducedTerms) {
        // Trie les termes par ordre décroissant de degré
        std::vector<Term> sortedTerms = reducedTerms;
        std::sort(sortedTerms.begin(), sortedTerms.end(), [](const Term& a, const Term& b) {
            return a.exponent < b.exponent;
        });

        // Construit la chaîne de caractères représentant l'équation réduite
        std::ostringstream equationStream;

        bool isFirstTerm = true;

        for (const Term& term : sortedTerms) {
            if (term.coefficient != 0) {
                if (!isFirstTerm) {
                    if (term.coefficient > 0) {
                        equationStream << " + ";
                    } else {
                        equationStream << " - ";
                    }
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

        equationStream << " = 0";

        return equationStream.str();
    }

    static void SolveQuadratic(double a, double b, double c) {
        // double discriminant = b * b - 4 * a * c;

        // if (discriminant > 0) {
        //     double root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        //     double root2 = (-b - std::sqrt(discriminant)) / (2 * a);

        //     std::cout << "Discriminant is positive, two real roots:" << std::endl;
        //     std::cout << "Root 1: " << root1 << std::endl;
        //     std::cout << "Root 2: " << root2 << std::endl;
        // } else if (discriminant == 0) {
        //     double root = -b / (2 * a);

        //     std::cout << "Discriminant is zero, one real root:" << std::endl;
        //     std::cout << "Root: " << root << std::endl;
        // } else {
        //     std::cout << "Discriminant is negative, two complex roots:" << std::endl;
        //     std::complex<double> root1(-b / (2 * a), std::sqrt(-discriminant) / (2 * a));
        //     std::complex<double> root2(-b / (2 * a), -std::sqrt(-discriminant) / (2 * a));

        //     std::cout << "Root 1: " << root1 << std::endl;
        //     std::cout << "Root 2: " << root2 << std::endl;
        // }
    }

    static void SolvePolynomial(const std::vector<EquationParser::Term>& reducedTerms) {
        // if (reducedTerms.empty()) {
        //     std::cout << "The polynomial is zero everywhere." << std::endl;
        //     return;
        // }

        // int maxExponent = reducedTerms.front().exponent;

        // if (maxExponent > 2) {
        //     std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        // } else if (maxExponent == 2) {
        //     double a = GetCoefficient(reducedTerms, 2);
        //     double b = GetCoefficient(reducedTerms, 1);
        //     double c = GetCoefficient(reducedTerms, 0);

        //     std::cout << "Solving quadratic equation: " << a << "x^2 + " << b << "x + " << c << " = 0" << std::endl;
        //     SolveQuadratic(a, b, c);
        // } else if (maxExponent == 1) {
        //     double a = GetCoefficient(reducedTerms, 1);
        //     double b = GetCoefficient(reducedTerms, 0);

        //     std::cout << "Solving linear equation: " << a << "x + " << b << " = 0" << std::endl;

        //     if (a == 0) {
        //         if (b == 0) {
        //             std::cout << "The equation has infinitely many solutions." << std::endl;
        //         } else {
        //             std::cout << "The equation has no solution." << std::endl;
        //         }
        //     } else {
        //         double root = -b / a;
        //         std::cout << "The solution is x = " << root << std::endl;
        //     }
        // } else {
        //     std::cout << "The equation is constant, no variable x." << std::endl;
        // }
    }

private:
    std::vector<Term> parsedTerms;
    std::string equation;
    double coefficient = 0;
    int exponent = 0;
    bool isNegativeCoefficient = false;
    bool isNegativeExponent = false;
    bool hasCoefficient = false;
    bool hasDecimal = false;
    double decimalMultiplier = 0.1;
    bool isRightSide = false;

    bool isOperator(char ch) const {
        return ch == '-' || ch == '+';
    }

    bool isVariable(char ch) const {
        return ch == 'X';
    }

    bool isExponentIndicator(char ch) const {
        return ch == '^';
    }

    bool isDecimalPoint(char ch) const {
        return ch == '.';
    }

    bool isEqualsSign(char ch) const {
        return ch == '=';
    }

    static double GetCoefficient(const std::vector<EquationParser::Term>& terms, int exponent) {
        auto it = std::find_if(terms.begin(), terms.end(), [exponent](const EquationParser::Term& term) {
            return term.exponent == exponent;
        });

        if (it != terms.end()) {
            return it->coefficient;
        } else {
            return 0.0;
        }
    }

    void addTermToList(std::vector<Term>& parsedTerms) {
        if (isRightSide) {
            coefficient = -coefficient;
        }
        // std::cout << "Added Term: Coefficient = " << coefficient << ", Exponent = " << exponent << std::endl;
        parsedTerms.push_back({coefficient, exponent});
    }

    void resetVariables() {
        coefficient = 0;
        exponent = 0;
        isNegativeCoefficient = false;
        hasCoefficient = false;
        hasDecimal = false;
        decimalMultiplier = 0.1;
    }

    void processEqualsSign(std::vector<Term>& parsedTerms) {
        // std::cout << "Processing Equals Sign" << std::endl;
        addTermToList(parsedTerms);
        resetVariables();
    }

    void processOperator(std::vector<Term>& parsedTerms) {
        // std::cout << "Processing Operator" << std::endl;
        addTermToList(parsedTerms);
        resetVariables();
        isNegativeCoefficient = (equation[equation.find_last_of("+-") - 1] == '-');
    }

    void processVariable(const std::string& equation, int i) {
        // std::cout << "Processing Variable" << std::endl;
        if (equation[i + 1] != '^')
            exponent = 1;
        hasCoefficient = true;
    }

    int processExponentIndicator(const std::string& equation, int i) {
        // std::cout << "Processing Exponent Indicator" << std::endl;
        i++;
        if (equation[i] == '-') {
            isNegativeExponent = true;
            i++;
        }
        // std::cout << "Valeur of equation[i]: " << equation[i] << std::endl;
        while (std::isdigit(equation[i])) {
            // std::cout << "Value Of Exponent: " << exponent << std::endl;
            exponent = exponent * 10 + (equation[i] - '0');
            i++;
            // std::cout << "Value Of Exponent: " << exponent << std::endl;
        }
        if (isNegativeExponent == true)
            exponent *= -1;
        // std::cout << "Exponent: " << exponent << std::endl;
        return (i);
    }

    bool canProcess(char c)
    {
        if (c == ' ' || c == '*' || c == 'X' || c == '=')
            return (false);
        return (true);    
   }

    int processDigit(const std::string& equation, int i) {
        // std::cout << "Processing Digit: " << equation[i] << std::endl;
        // std::cout << "Coeff " << coefficient << std::endl;
        // std::cout << "decimalMultiplier: " << decimalMultiplier << std::endl;
        // std::cout << "Exponent: " << exponent << std::endl;

        while (canProcess(equation[i]) && equation[i])
        {
            if (equation[i] == '.')
            {
                // std::cout << "Decimal Found" << std::endl;
                i++;
                while (canProcess(equation[i]) && equation[i])
                {
                    coefficient += (equation[i] - '0') * decimalMultiplier;
                    decimalMultiplier *= 0.1;
                    i++;
                    // std::cout << "Coeff 2:" << coefficient << std::endl;
                }
                break;
            }
            coefficient = coefficient * 10 + (equation[i] - '0');
            i++;
            // std::cout << "NewCoeff: " << coefficient << std::endl;
        }
        return (i);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <equation>" << std::endl;
        return 1;
    }

    // Récupérer l'équation à partir des arguments de la ligne de commande
    std::string equation = argv[1];

    // Créer une instance de la classe EquationParser
    EquationParser equationParser(equation);

    // Appel de la fonction ParseInput
    std::vector<EquationParser::Term> parsedTerms = equationParser.ParseInput();

    // Affichage des termes analysés
    std::cout << "Termes analyses :" << std::endl;
    for (const EquationParser::Term& term : parsedTerms) {
        std::cout << "Coefficient : " << term.coefficient
                  << ", Exposant : " << term.exponent << std::endl;
    }
    std::vector<EquationParser::Term> reducedTerms = equationParser.ReduceTerms(parsedTerms);
    // Affichage des termes reduits
    std::cout << "Termes reduits :" << std::endl;
    for (const EquationParser::Term& term : reducedTerms) {
        std::cout << "Coefficient : " << term.coefficient
                  << ", Exposant : " << term.exponent << std::endl;
    }
    std::cout << "Equation Reduced: " << equationParser.WriteReducedEquation(reducedTerms) << std::endl;


    equationParser.SolvePolynomial(reducedTerms);   
    return 0;
}