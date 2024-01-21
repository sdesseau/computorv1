#include "EquationSolver.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <equation>" << std::endl;
        return (1);
    }

    std::string equation = argv[1];
    EquationSolver equationSolver(equation);

    std::vector<EquationSolver::Term> parsedTerms = equationSolver.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms = equationSolver.ReduceTerms(parsedTerms);
    std::cout << "Equation Reduced: " << equationSolver.WriteReducedEquation(reducedTerms) << std::endl;

    equationSolver.SolvePolynomial(reducedTerms);   
    return (0);
}
