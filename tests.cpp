// tests.cpp
#include "EquationSolver.hpp"

void printResult(bool success, const std::string& message) {
    if (success) {
        std::cout << "\033[1;32m" << "PASSED: " << message << "\033[0m" << std::endl << std::endl << std::endl;
    } else {
        std::cerr << "\033[1;31m" << "FAILED: " << message << "\033[0m" << std::endl << std::endl << std::endl;
    }
}

void runTests() {


    std::cout << "\033[1;32m" << "TESTING COMPUTORV1" << "\033[0m" << std::endl << std::endl;

    // Test 0: Parsing Test
    std::cout << "\033[1;33m" << "Test Number 0" << "\033[0m" << std::endl;
    EquationSolver Solver("---2x^2+5.127-12xX + 2X 0000000000001212XX      +++ -          -10 = -1212xx  ****2 - 12.03x^2                ");
    std::vector<EquationSolver::Term> parsedTerms = Solver.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms = Solver.ReduceTerms(parsedTerms);
    std::cout << "Equation Reduced: " << Solver.WriteReducedEquation(reducedTerms) << std::endl;
    Solver.SolvePolynomial(reducedTerms);   
    printResult(reducedTerms.size() == 3, "Test 0 - Correct number of terms after reduction: 3");
    
    // Test 1: Quadratic equation
    std::cout << "\033[1;33m" << "Test Number 1" << "\033[0m" << std::endl;
    EquationSolver Solver1("2X^2 + 3X + 1 = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms1 = Solver1.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms1 = Solver1.ReduceTerms(parsedTerms1);
    std::cout << "Equation Reduced: " << Solver1.WriteReducedEquation(reducedTerms1) << std::endl;
    Solver1.SolvePolynomial(reducedTerms1);   
    printResult(reducedTerms1.size() == 3, "Test 1 - Correct number of terms after reduction: 3");

    // Test 2: Another One
    std::cout << "\033[1;33m" << "Test Number 2" << "\033[0m" << std::endl;
    EquationSolver Solver2("3X^2 - 2X + 4 = 2X + 2");
    std::vector<EquationSolver::Term> parsedTerms2 = Solver2.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms2 = Solver2.ReduceTerms(parsedTerms2);
    std::cout << "Equation Reduced: " << Solver2.WriteReducedEquation(reducedTerms2) << std::endl;
    Solver2.SolvePolynomial(reducedTerms2);   
    printResult(reducedTerms2.size() == 3, "Test 2 - Correct number of terms after reduction: 3");

    // Test 3: Constant equation
    std::cout << "\033[1;33m" << "Test Number 3" << "\033[0m" << std::endl;
    EquationSolver Solver3("5 = 5");
    std::vector<EquationSolver::Term> parsedTerms3 = Solver3.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms3 = Solver3.ReduceTerms(parsedTerms3);
    std::cout << "Equation Reduced: " << Solver3.WriteReducedEquation(reducedTerms3) << std::endl;
    Solver3.SolvePolynomial(reducedTerms3);   
    printResult(reducedTerms3.size() == 0, "Test 3 - Correct number of terms after reduction: 0");

    // Test 4: Parsing with decimal coefficients
    std::cout << "\033[1;33m" << "Test Number 4" << "\033[0m" << std::endl;
    EquationSolver Solver4("0.5X^2 + 1.5X - 2.3 = X^2 - 3.2X + 4.7");
    std::vector<EquationSolver::Term> parsedTerms4 = Solver4.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms4 = Solver4.ReduceTerms(parsedTerms4);
    std::cout << "Equation Reduced: " << Solver4.WriteReducedEquation(reducedTerms4) << std::endl;
    Solver4.SolvePolynomial(reducedTerms4);   
    printResult(reducedTerms4.size() == 3, "Test 4 - Correct number of terms after reduction: 3");

    // Test 5: Linear equation
    std::cout << "\033[1;33m" << "Test Number 5" << "\033[0m" << std::endl;
    EquationSolver Solver5("2X + 5 = 3X - 1");
    std::vector<EquationSolver::Term> parsedTerms5 = Solver5.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms5 = Solver5.ReduceTerms(parsedTerms5);
    

    std::cout << "Equation Reduced: " << Solver5.WriteReducedEquation(reducedTerms5) << std::endl;
    Solver5.SolvePolynomial(reducedTerms5);   
    printResult(reducedTerms5.size() == 2, "Test 5 - Correct number of terms after reduction for a linear equation: 2");

    // Test 6: Quadratic equation with negative discriminant
    std::cout << "\033[1;33m" << "Test Number 6" << "\033[0m" << std::endl;
    EquationSolver Solver6("X^2 + 4X + 5 = 0");
    std::vector<EquationSolver::Term> parsedTerms6 = Solver6.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms6 = Solver6.ReduceTerms(parsedTerms6);
    std::cout << "Equation Reduced: " << Solver6.WriteReducedEquation(reducedTerms6) << std::endl;
    Solver6.SolvePolynomial(reducedTerms6);   
    printResult(reducedTerms6.size() == 3, "Test 6 - Correct number of terms after reduction: 3");

    // Test 7: Linear equation with zero coefficient
    std::cout << "\033[1;33m" << "Test Number 7" << "\033[0m" << std::endl;
    EquationSolver Solver7("2X - 2X = 0");
    std::vector<EquationSolver::Term> parsedTerms7 = Solver7.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms7 = Solver7.ReduceTerms(parsedTerms7);
    std::cout << "Equation Reduced: " << Solver7.WriteReducedEquation(reducedTerms7) << std::endl;
    Solver7.SolvePolynomial(reducedTerms7);   
    printResult(reducedTerms7.size() == 0, "Test 7 - Correct number of terms after reduction: 0");

    // Test 8: Equation with valid spaces
    std::cout << "\033[1;33m" << "Test Number 8" << "\033[0m" << std::endl;
    EquationSolver Solver8(" 2 X^2 + 3X + 1 = X^2 + 5X + 2 ");
    std::vector<EquationSolver::Term> parsedTerms8 = Solver8.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms8 = Solver8.ReduceTerms(parsedTerms8);
    std::cout << "Equation Reduced: " << Solver8.WriteReducedEquation(reducedTerms8) << std::endl;
    Solver8.SolvePolynomial(reducedTerms8);   
    printResult(reducedTerms8.size() == 3, "Test 8 - Correct number of terms after reduction: 3");

    // Test 9: Equation with invalid spaces
    std::cout << "\033[1;33m" << "Test Number 9" << "\033[0m" << std::endl;
    EquationSolver Solver9("2X^2 + 3 X + 1 = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms9 = Solver9.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms9 = Solver9.ReduceTerms(parsedTerms9);
    std::cout << "Equation Reduced: " << Solver9.WriteReducedEquation(reducedTerms9) << std::endl;
    Solver9.SolvePolynomial(reducedTerms9);   
    printResult(reducedTerms9.size() == 3, "Test 9 - Correct number of terms after reduction: 3");

    // Test 10: Quadratic equation with all coefficients canceled out
    std::cout << "\033[1;33m" << "Test Number 10" << "\033[0m" << std::endl;
    EquationSolver Solver10("X^2 + 2X + 1 = X^2 + 2X + 1");
    std::vector<EquationSolver::Term> parsedTerms10 = Solver10.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms10 = Solver10.ReduceTerms(parsedTerms10);
    bool allCoefficientsZero = std::all_of(reducedTerms10.begin(), reducedTerms10.end(),
                                           [](const EquationSolver::Term& term) {
                                               return term.coefficient == 0;
                                           });

    std::cout << "Equation Reduced: " << Solver10.WriteReducedEquation(reducedTerms10) << std::endl;
    Solver10.SolvePolynomial(reducedTerms10);   
    printResult(allCoefficientsZero, "Test 10 - All coefficients canceled out");

    // Test 11: Equation with leading zeros in coefficients
    std::cout << "\033[1;33m" << "Test Number 11" << "\033[0m" << std::endl;
    EquationSolver Solver11("002X^2 + 003X + 001 = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms11 = Solver11.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms11 = Solver11.ReduceTerms(parsedTerms11);
    std::cout << "Equation Reduced: " << Solver11.WriteReducedEquation(reducedTerms11) << std::endl;
    Solver11.SolvePolynomial(reducedTerms11);   
    printResult(reducedTerms11.size() == 3, "Test 11 - Correct number of terms after reduction: 3");

    // Test 12: Equation with coefficient and variable only
    std::cout << "\033[1;33m" << "Test Number 12" << "\033[0m" << std::endl;
    EquationSolver Solver12("2X = 0");
    std::vector<EquationSolver::Term> parsedTerms12 = Solver12.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms12 = Solver12.ReduceTerms(parsedTerms12);
    std::cout << "Equation Reduced: " << Solver12.WriteReducedEquation(reducedTerms12) << std::endl;
    Solver12.SolvePolynomial(reducedTerms12);   
    printResult(reducedTerms12.size() == 1, "Test 12 - Correct number of terms after reduction: 1");

    // Test 13: Quadratic equation with imaginary roots
    std::cout << "\033[1;33m" << "Test Number 13" << "\033[0m" << std::endl;
    EquationSolver Solver13("X^2 + 2X + 5 = 0");
    std::vector<EquationSolver::Term> parsedTerms13 = Solver13.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms13 = Solver13.ReduceTerms(parsedTerms13);
    std::cout << "Equation Reduced: " << Solver13.WriteReducedEquation(reducedTerms13) << std::endl;
    Solver13.SolvePolynomial(reducedTerms13);   
    printResult(reducedTerms13.size() == 3, "Test 13 - Correct number of terms after reduction: 3");

    // Test 14: Equation with consecutive exponents
    std::cout << "\033[1;33m" << "Test Number 14" << "\033[0m" << std::endl;
    EquationSolver Solver14("X^2 + X^3 + X^4 = 0");
    std::vector<EquationSolver::Term> parsedTerms14 = Solver14.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms14 = Solver14.ReduceTerms(parsedTerms14);
    std::cout << "Equation Reduced: " << Solver14.WriteReducedEquation(reducedTerms14) << std::endl;
    Solver14.SolvePolynomial(reducedTerms14);   
    printResult(reducedTerms14.size() == 3, "Test 14 - Correct number of terms after reduction: 3");

    // Test 15: Equation with invalid spaces in exponent
    std::cout << "\033[1;33m" << "Test Number 15" << "\033[0m" << std::endl;
    EquationSolver Solver15("2X^2 + 3X^       2 + 1 = X    ^   2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms15 = Solver15.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms15 = Solver15.ReduceTerms(parsedTerms15);
    std::cout << "Equation Reduced: " << Solver15.WriteReducedEquation(reducedTerms15) << std::endl;
    Solver15.SolvePolynomial(reducedTerms15);   
    printResult(reducedTerms15.size() == 3, "Test 15 - Correct number of terms after reduction: 3");

    // Test 16: Equation with repeated variables
    std::cout << "\033[1;33m" << "Test Number 16" << "\033[0m" << std::endl;
    EquationSolver Solver16("2X^2 + 3X + XX = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms16 = Solver16.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms16 = Solver16.ReduceTerms(parsedTerms16);
    std::cout << "Equation Reduced: " << Solver16.WriteReducedEquation(reducedTerms16) << std::endl;
    Solver16.SolvePolynomial(reducedTerms16);   
    printResult(reducedTerms16.size() == 3, "Test 16 - Correct number of terms after reduction: 3");


    // Test with special outputs //


    // // Test 17: Equation with invalid exponent format -> Error: Unknown Exponent Character: a
        // std::cout << "\033[1;33m" << "Test Number 17" << "\033[0m" << std::endl;
    // EquationSolver Solver17("2X^2 + 3X^a + 1 = X^2 + 5X + 2");
    // std::vector<EquationSolver::Term> parsedTerms17 = Solver17.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms17 = Solver17.ReduceTerms(parsedTerms17);
    // std::cout << "Equation Reduced: " << Solver17.WriteReducedEquation(reducedTerms17) << std::endl;
    // Solver17.SolvePolynomial(reducedTerms17);   

    // // Test 18: Equation with missing coefficient before variable -> Error: Unknown Exponent Character: X
    //     std::cout << "\033[1;33m" << "Test Number 18" << "\033[0m" << std::endl;
    // EquationSolver Solver18("2^X^2 + 3X + 1 = X^2 + 5X + 2");
    // std::vector<EquationSolver::Term> parsedTerms18 = Solver18.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms18 = Solver18.ReduceTerms(parsedTerms18);
    // std::cout << "Equation Reduced: " << Solver18.WriteReducedEquation(reducedTerms18) << std::endl;
    // Solver18.SolvePolynomial(reducedTerms18); 

    // // Test 19: Equation with invalid characters -> Error: Invalid characters found
    // std::cout << "\033[1;33m" << "Test Number 19" << "\033[0m" << std::endl;
    // EquationSolver Solver19("2X^2 + @3X + 1 = X^2 + 5X + 2");
    // std::vector<EquationSolver::Term> parsedTerms19 = Solver19.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms19 = Solver19.ReduceTerms(parsedTerms19);
    // std::cout << "Equation Reduced: " << Solver19.WriteReducedEquation(reducedTerms19) << std::endl;
    // Solver19.SolvePolynomial(reducedTerms19); 

    // // Test 20: Handling negative exponents -> Error: By definition, a polynomial has non-negative integer exponents of variables
    //     std::cout << "\033[1;33m" << "Test Number 20" << "\033[0m" << std::endl;
    // EquationSolver Solver20("2X^- 4 - 3X^-2 = 5");
    // std::vector<EquationSolver::Term> parsedTerms20 = Solver20.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms20 = Solver20.ReduceTerms(parsedTerms20);
    // std::cout << "Equation Reduced: " << Solver20.WriteReducedEquation(reducedTerms20) << std::endl;
    // Solver20.SolvePolynomial(reducedTerms20);   

    // // Test 21: Equation with multiple decimal points -> Error: Multiple Decimal Point
    //     std::cout << "\033[1;33m" << "Test Number 21" << "\033[0m" << std::endl;
    // EquationSolver Solver21("1.2.3X^2 - 2.5 = 0");
    // std::vector<EquationSolver::Term> parsedTerms21 = Solver21.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms21 = Solver21.ReduceTerms(parsedTerms21);
    // std::cout << "Equation Reduced: " << Solver21.WriteReducedEquation(reducedTerms21) << std::endl;
    // Solver21.SolvePolynomial(reducedTerms21);
}

int main() {
    runTests();
    return 0;
}
