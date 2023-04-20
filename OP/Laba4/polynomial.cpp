#include "polynomial.h"
#include <iostream>

Polynomial::Polynomial() {
    for (int i = 0; i < 4; i++) {
        coefficients[i] = 0;
    }
}

Polynomial::Polynomial(double a, double b, double c, double d) {
    coefficients[0] = a;
    coefficients[1] = b;
    coefficients[2] = c;
    coefficients[3] = d;
}

Polynomial::Polynomial(double coeffs[]) {
    for (int i = 0; i < 4; i++) {
        coefficients[i] = coeffs[i];
    }
}

void Polynomial::setCoefficient(int index, double value) {
    coefficients[index] = value;
}

double Polynomial::getCoefficient(int index) const {
    return coefficients[index];
}

double Polynomial::getA() const {
    return coefficients[0];
}

double Polynomial::getB() const {
    return coefficients[1];
}

double Polynomial::getC() const {
    return coefficients[2];
}

double Polynomial::getD() const {
    return coefficients[3];
}

double Polynomial::evaluate(double x) const {
    double result = coefficients[3];
    for (int i = 2; i >= 0; i--) {
        result = result * x + coefficients[i];
    }
    return result;
}

void Polynomial::print() const {
    std::cout << coefficients[0] << " + " << coefficients[1] << "x + "
        << coefficients[2] << "x^2 + " << coefficients[3] << "x^3" << std::endl;
}

void Polynomial::operator+=(double value) {
    for (int i = 0; i < 4; i++) {
        coefficients[i] += value;
    }
}

void Polynomial::operator-=(double value) {
    for (int i = 0; i < 4; i++) {
        coefficients[i] -= value;
    }
}

bool Polynomial::operator==(const Polynomial& other) const {
    for (int i = 0; i < 4; i++) {
        if (coefficients[i] != other.coefficients[i]) {
            return false;
        }
    }
    return true;
}
