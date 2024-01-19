// main_test.cpp
#include "EquationSolver.hpp"

// Helper function for colorizing output
void printResult(bool success, const std::string& message) {
    if (success) {
        std::cout << "\033[1;32m" << "PASSED: " << message << "\033[0m" << std::endl;
    } else {
        std::cerr << "\033[1;31m" << "FAILED: " << message << "\033[0m" << std::endl;
    }
}

void runTests() {
    // Test 1: Quadratic equation
    EquationSolver Solver1("2X^2 + 3X + 1 = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms1 = Solver1.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms1 = Solver1.ReduceTerms(parsedTerms1);

    printResult(reducedTerms1.size() == 3, "Test 1 - Correct number of terms after reduction");

    // Test 2: Another One
    EquationSolver Solver2("3X^2 - 2X + 4 = 2X + 2");
    std::vector<EquationSolver::Term> parsedTerms2 = Solver2.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms2 = Solver2.ReduceTerms(parsedTerms2);

    printResult(reducedTerms2.size() == 3, "Test 2 - Correct number of terms after reduction");

    // Test 3: Constant equation
    EquationSolver Solver3("5 = 5");
    std::vector<EquationSolver::Term> parsedTerms3 = Solver3.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms3 = Solver3.ReduceTerms(parsedTerms3);

    printResult(reducedTerms3.size() == 1, "Test 3 - Correct number of terms after reduction");

    // Test 4: Parsing with decimal coefficients
    EquationSolver Solver4("0.5X^2 + 1.5X - 2.3 = X^2 - 3.2X + 4.7");
    std::vector<EquationSolver::Term> parsedTerms4 = Solver4.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms4 = Solver4.ReduceTerms(parsedTerms4);

    printResult(reducedTerms4.size() == 3, "Test 4 - Correct number of terms after reduction");

    // Test 5: Linear equation
    EquationSolver Solver5("2X + 5 = 3X - 1");
    std::vector<EquationSolver::Term> parsedTerms5 = Solver5.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms5 = Solver5.ReduceTerms(parsedTerms5);
    
    printResult(reducedTerms5.size() == 2, "Test 5 - Correct number of terms after reduction for a linear equation");

    // Test 6: Quadratic equation with negative discriminant
    EquationSolver Solver6("X^2 + 4X + 5 = 0");
    std::vector<EquationSolver::Term> parsedTerms6 = Solver6.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms6 = Solver6.ReduceTerms(parsedTerms6);

    printResult(reducedTerms6.size() == 3, "Test 6 - Correct number of terms after reduction");

    // Test 7: Linear equation with zero coefficient
    EquationSolver Solver7("2X - 2X = 0");
    std::vector<EquationSolver::Term> parsedTerms7 = Solver7.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms7 = Solver7.ReduceTerms(parsedTerms7);

    printResult(reducedTerms7.size() == 1, "Test 7 - Correct number of terms after reduction");

    // Test 8: Equation with valid spaces
    EquationSolver Solver8(" 2 X^2 + 3X + 1 = X^2 + 5X + 2 ");
    std::vector<EquationSolver::Term> parsedTerms8 = Solver8.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms8 = Solver8.ReduceTerms(parsedTerms8);

    printResult(reducedTerms8.size() == 3, "Test 8 - Correct number of terms after reduction");

    // Test 9: Equation with invalid spaces
    EquationSolver Solver9("2X^2 + 3 X + 1 = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms9 = Solver9.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms9 = Solver9.ReduceTerms(parsedTerms9);

    printResult(reducedTerms9.size() == 3, "Test 9 - Correct number of terms after reduction");

    // Test 10: Quadratic equation with all coefficients canceled out
    EquationSolver Solver10("X^2 + 2X + 1 = X^2 + 2X + 1");
    std::vector<EquationSolver::Term> parsedTerms10 = Solver10.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms10 = Solver10.ReduceTerms(parsedTerms10);

    bool allCoefficientsZero = std::all_of(reducedTerms10.begin(), reducedTerms10.end(),
                                           [](const EquationSolver::Term& term) {
                                               return term.coefficient == 0;
                                           });

    printResult(allCoefficientsZero, "Test 10 - All coefficients canceled out");


    // Test 11: Equation with leading zeros in coefficients
    EquationSolver Solver11("002X^2 + 003X + 001 = X^2 + 5X + 2");
    std::vector<EquationSolver::Term> parsedTerms11 = Solver11.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms11 = Solver11.ReduceTerms(parsedTerms11);

    printResult(reducedTerms11.size() == 3, "Test 11 - Correct number of terms after reduction");

    // Test 12: Equation with coefficient and variable only
    EquationSolver Solver12("2X = 0");
    std::vector<EquationSolver::Term> parsedTerms12 = Solver12.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms12 = Solver12.ReduceTerms(parsedTerms12);

    printResult(reducedTerms12.size() == 1, "Test 12 - Correct number of terms after reduction");

    // Test 13: Quadratic equation with imaginary roots
    EquationSolver Solver13("X^2 + 2X + 5 = 0");
    std::vector<EquationSolver::Term> parsedTerms13 = Solver13.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms13 = Solver13.ReduceTerms(parsedTerms13);

    printResult(reducedTerms13.size() == 3, "Test 13 - Correct number of terms after reduction");

    // Test 14: Equation with consecutive exponents
    EquationSolver Solver14("X^2 + X^3 + X^4 = 0");
    std::vector<EquationSolver::Term> parsedTerms14 = Solver14.ParseInput();
    std::vector<EquationSolver::Term> reducedTerms14 = Solver14.ReduceTerms(parsedTerms14);

    printResult(reducedTerms14.size() == 3, "Test 14 - Correct number of terms after reduction");


    // Test with special outputs

    // // Test 15: Handling negative exponents -> Error: By definition, a polynomial has non-negative integer exponents of variables
    // EquationSolver Solver15("2X^- 4 - 3X^-2 = 5");
    // std::vector<EquationSolver::Term> parsedTerms15 = Solver15.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms15 = Solver15.ReduceTerms(parsedTerms15);

    // printResult(reducedTerms15.size() == 2, "Test 15 - Correct number of terms after reduction");

    // // Test 16: Equation with multiple decimal points -> Error: Multiple Decimal Point
    // EquationSolver Solver16("1.2.3X^2 - 2.5 = 0");
    // std::vector<EquationSolver::Term> parsedTerms16 = Solver16.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms16 = Solver16.ReduceTerms(parsedTerms16);

    // printResult(reducedTerms16.size() == 2, "Test 16 - Correct number of terms after reduction");

    // // Test 17: Equation with invalid exponent format -> Error: Unknown Exponent Character: a
    // EquationSolver Solver17("2X^2 + 3X^a + 1 = X^2 + 5X + 2");
    // std::vector<EquationSolver::Term> parsedTerms17 = Solver17.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms17 = Solver17.ReduceTerms(parsedTerms17);

    // printResult(reducedTerms17.size() == 4, "Test 17 - Correct number of terms after reduction");

    // // Test 18: Equation with missing variable after exponent -> Error: Unknown Exponent Character: 
    // EquationSolver Solver18("2X^2 + 3^ + 1 = X^2 + 5X + 2");
    // std::vector<EquationSolver::Term> parsedTerms18 = Solver18.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms18 = Solver18.ReduceTerms(parsedTerms18);

    // printResult(reducedTerms18.size() == 4, "Test 18 - Correct number of terms after reduction");

    // // Test 19: Equation with missing coefficient before variable -> Error: Unknown Exponent Character: X
    // EquationSolver Solver19("2^X^2 + 3X + 1 = X^2 + 5X + 2");
    // std::vector<EquationSolver::Term> parsedTerms19 = Solver19.ParseInput();
    // std::vector<EquationSolver::Term> reducedTerms19 = Solver19.ReduceTerms(parsedTerms19);

    // printResult(reducedTerms19.size() == 4, "Test 19 - Correct number of terms after reduction");
}

int main() {
    runTests();
    return 0;
}
