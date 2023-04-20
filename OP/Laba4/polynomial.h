#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
private:
    double coefficients[4];

public:
    Polynomial();
    Polynomial(double a, double b, double c, double d);
    Polynomial(double coeffs[]);

    void setCoefficient(int index, double value);
    double getCoefficient(int index) const;

    double getA() const;
    double getB() const;
    double getC() const;
    double getD() const;

    double evaluate(double x) const;
    void print() const;

    void operator+=(double value);
    void operator-=(double value);
    bool operator==(const Polynomial& other) const;
};

#endif // POLYNOMIAL_H
