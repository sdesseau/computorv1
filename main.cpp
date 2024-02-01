#include "EquationSolver.hpp"

int main(int argc, char* argv[]) {
    try {
        if (argc != 2)
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <equation>");
        
        std::string equation = argv[1];
        EquationSolver equationSolver(equation);

        std::vector<EquationSolver::Term> parsedTerms = equationSolver.ParseInput();
        std::vector<EquationSolver::Term> reducedTerms = equationSolver.ReduceTerms(parsedTerms);
        std::cout << "Equation Reduced: " << equationSolver.WriteReducedEquation(reducedTerms) << std::endl;
        equationSolver.SolvePolynomial(reducedTerms);
        
        return (0);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
}