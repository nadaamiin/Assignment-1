#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial, where coeffs[i] represents the coefficient of x^i

public:
    // Constructors
    Polynomial(); // Default constructor
    Polynomial(const vector<double>& coefficients); // Initialize with coefficients
    Polynomial(const Polynomial& other); // Copy constructor

    // Destructor
    ~Polynomial();

    // Assignment operator
    Polynomial& operator=(const Polynomial& other);

    // Arithmetic operators
    Polynomial operator+(const Polynomial& other) const; // Addition of two polynomials
    Polynomial operator-(const Polynomial& other) const; // Subtraction of two polynomials
    Polynomial operator*(const Polynomial& other) const; // Multiplication of two polynomials

    // Equality operator
    bool operator==(const Polynomial& other) const; // Check if two polynomials are equal

    // Output operator
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // Stream insertion for output

    // Utility functions
    int degree() const; // Return the degree of the polynomial
    double evaluate(double x) const; // Evaluate the polynomial at a given value of x
    Polynomial compose(const Polynomial& q) const; // Composition of two polynomials
    Polynomial derivative() const; // Derivative of the polynomial
    Polynomial integral() const; // Indefinite integral of the polynomial
    double integral(double x1, double x2) const; // Definite integral from x1 to x2
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100); // Find a root using Newton's method

    // Set and get coefficients
    void setCoefficients(const vector<double>& coefficients); // Set the polynomial's coefficients
    double getCoefficient(int degree) const; // Get the coefficient for a specific degree

};

#endif // POLYNOMIAL_H
