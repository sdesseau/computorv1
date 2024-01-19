#include "EquationSolver.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <equation>" << std::endl;
        return 1;
    }

    std::string equation = argv[1];
    EquationSolver equationSolver(equation);

    // Affichage des termes analysés
    std::vector<EquationSolver::Term> parsedTerms = equationSolver.ParseInput();
    std::cout << "Termes analyses :" << std::endl;
    for (const EquationSolver::Term& term : parsedTerms) {
        std::cout << "Coefficient : " << term.coefficient
                  << ", Exposant : " << term.exponent << std::endl;
    }

    // Affichage des termes reduits
    std::vector<EquationSolver::Term> reducedTerms = equationSolver.ReduceTerms(parsedTerms);
    std::cout << "Termes reduits :" << std::endl;
    for (const EquationSolver::Term& term : reducedTerms) {
        std::cout << "Coefficient : " << term.coefficient
                  << ", Exposant : " << term.exponent << std::endl;
    }
    std::cout << "Equation Reduced: " << equationSolver.WriteReducedEquation(reducedTerms) << std::endl;


    equationSolver.SolvePolynomial(reducedTerms);   
    return (0);
}
