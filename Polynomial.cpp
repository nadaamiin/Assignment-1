#include "Polynomial.h"

// Default constructor
Polynomial::Polynomial() : coeffs(1, 0.0) { // Initialize with a zero polynomial
}

// Constructor with coefficients
Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {
    // Remove any trailing zeros
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
    if (coeffs.empty()) {
        coeffs.push_back(0.0); // Ensure at least a zero polynomial is present
    }
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {
}

// Destructor
Polynomial::~Polynomial() {
    // Nothing to clean up
}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Addition operator
Polynomial Polynomial::operator+(const Polynomial& other) const {
    size_t maxSize = max(coeffs.size(), other.coeffs.size());
    vector<double> result(maxSize, 0.0);

    for (size_t i = 0; i < maxSize; ++i) {
        double a = (i < coeffs.size()) ? coeffs[i] : 0.0;
        double b = (i < other.coeffs.size()) ? other.coeffs[i] : 0.0;
        result[i] = a + b;
    }
    return Polynomial(result);
}

// Subtraction operator
Polynomial Polynomial::operator-(const Polynomial& other) const {
    size_t maxSize = max(coeffs.size(), other.coeffs.size());
    vector<double> result(maxSize, 0.0);

    for (size_t i = 0; i < maxSize; ++i) {
        double a = (i < coeffs.size()) ? coeffs[i] : 0.0;
        double b = (i < other.coeffs.size()) ? other.coeffs[i] : 0.0;
        result[i] = a - b;
    }
    return Polynomial(result);
}

// Multiplication operator
Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0) {
                out << " + ";
            }
            if (i == 0 || poly.coeffs[i] != 1) {
                out << poly.coeffs[i];
            }
            if (i > 0) {
                out << "x";
                if (i > 1) {
                    out << "^" << i;
                }
            }
        }
    }
    return out;
}

// Return the degree of the polynomial
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

// Evaluate the polynomial at a given value of x
double Polynomial::evaluate(double x) const {
    double result = 0.0;
    double power = 1.0;
    for (double coeff : coeffs) {
        result += coeff * power;
        power *= x;
    }
    return result;
}

// Polynomial composition
Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial(vector<double>{coeffs[i]});
    }
    return result;
}

// Derivative of the polynomial
Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) {
        return Polynomial(); // Derivative of a constant is zero
    }
    vector<double> result(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        result[i - 1] = coeffs[i] * i;
    }
    return Polynomial(result);
}

// Indefinite integral of the polynomial
Polynomial Polynomial::integral() const {
    vector<double> result(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(result);
}

// Definite integral from x1 to x2
double Polynomial::integral(double x1, double x2) const {
    Polynomial antiderivative = integral();
    return antiderivative.evaluate(x2) - antiderivative.evaluate(x1);
}

// Find a root using Newton's method
double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    double x = guess;
    for (int i = 0; i < maxIter; ++i) {
        double fx = evaluate(x);
        double fpx = derivative().evaluate(x);
        if (abs(fx) < tolerance) {
            return x;
        }
        if (fpx == 0) {
            break; // Avoid division by zero
        }
        x -= fx / fpx;
    }
    return x; // Return the best estimate
}

// Set the polynomial's coefficients
void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
    // Remove any trailing zeros
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
    if (coeffs.empty()) {
        coeffs.push_back(0.0); // Ensure at least a zero polynomial is present
    }
}

// Get the coefficient for a specific degree
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) {
        return 0.0;
    }
    return coeffs[degree];
}
