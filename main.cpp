#include "Polynomial.h"
#include "gtest/gtest.h"

using namespace std;

// Struct to hold parameters for testing different operations
struct TestingParams {
    int testCaseNumber;
    Polynomial p1;
    Polynomial p2;
    Polynomial expected_Addition;
    Polynomial expected_Subtraction;
    Polynomial expected_Multiplication;
    double x;                    // For evaluation, root-finding
    double expected_Evaluation;   // Expected value for evaluation at point x
    Polynomial expected_Derivative;
    double expected_Root;         // Expected value for root
};

// Test class for Polynomial testing
class PolynomialTest : public testing::TestWithParam<TestingParams> {
protected:
    int testCaseNumber;
    Polynomial p1;
    Polynomial p2;
    Polynomial expected_Addition;
    Polynomial expected_Subtraction;
    Polynomial expected_Multiplication;
    double x;
    double expected_Evaluation;
    Polynomial expected_Derivative;
    double expected_Root;

    virtual void SetUp() override {
        TestingParams params = GetParam();
        testCaseNumber = params.testCaseNumber;
        p1 = params.p1;
        p2 = params.p2;
        expected_Addition = params.expected_Addition;
        expected_Subtraction = params.expected_Subtraction;
        expected_Multiplication = params.expected_Multiplication;
        x = params.x;
        expected_Evaluation = params.expected_Evaluation;
        expected_Derivative = params.expected_Derivative;
        expected_Root = params.expected_Root;
    }
};

// Instantiate test cases using the same input polynomials
INSTANTIATE_TEST_SUITE_P(
        PolynomialTests, PolynomialTest,
        testing::Values(
                TestingParams{
                        1,
                        Polynomial({1, 2, 3}),                        // p1
                        Polynomial({1, 2, 3}),                        // p2
                        Polynomial({2, 4, 6}),                        // expected addition
                        Polynomial({0, 0, 0}),                        // expected subtraction
                        Polynomial({1, 4, 10, 12, 9}),                // expected multiplication
                        2,                                            // x value for evaluation
                        17,                                           // expected evaluation of p1 at x=2
                        Polynomial({2, 4}),                           // expected derivative
                        1                                             // expected root (example value)
                },
                TestingParams{
                        2,
                        Polynomial({0, 0, 1}),                        // p1
                        Polynomial({1, 1, 1}),                        // p2
                        Polynomial({1, 1, 2}),                        // expected addition
                        Polynomial({-1, -1, 0}),                      // expected subtraction
                        Polynomial({0, 0, 1, 1, 1}),                  // expected multiplication
                        5,                                            // x value for evaluation
                        25,                                           // expected evaluation of p1 at x=5
                        Polynomial({0, 0}),                           // expected derivative
                        0                                             // expected root (example value)
                }
                // Add more test cases as needed
        )
);

// Addition Test
TEST_P(PolynomialTest, AdditionTest) {
    Polynomial sum = p1 + p2;
    EXPECT_EQ(sum, expected_Addition) << "Test case Number: " << testCaseNumber;
}

// Subtraction Test
TEST_P(PolynomialTest, SubtractionTest) {
    Polynomial diff = p1 - p2;
    EXPECT_EQ(diff, expected_Subtraction) << "Test case Number: " << testCaseNumber;
}

// Multiplication Test
TEST_P(PolynomialTest, MultiplicationTest) {
    Polynomial prod = p1 * p2;
    EXPECT_EQ(prod, expected_Multiplication) << "Test case Number: " << testCaseNumber;
}

// Evaluation Test
TEST_P(PolynomialTest, EvaluationTest) {
    double result = p1.evaluate(x);
    EXPECT_NEAR(result, expected_Evaluation, 1e-6) << "Test case Number: " << testCaseNumber;
}

// Derivative Test
TEST_P(PolynomialTest, DerivativeTest) {
    Polynomial derivative = p1.derivative();
    EXPECT_EQ(derivative, expected_Derivative) << "Test case Number: " << testCaseNumber;
}

// Root Finding Test (using Newton's method)
TEST_P(PolynomialTest, RootFindingTest) {
    double root = p1.getRoot();
    EXPECT_NEAR(root, expected_Root, 1e-6) << "Test case Number: " << testCaseNumber;
}

// Main function
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
