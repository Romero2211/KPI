#pragma once
#ifndef TVECTOR_H
#define TVECTOR_H

#include <iostream>
#include <cmath>

class TVector {
protected:
    double x, y, z;
public:
    TVector(double x0, double y0, double z0) : x(x0), y(y0), z(z0) {}

    virtual double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    virtual bool is_parallel(const TVector& other) const {
        return std::abs(x * other.y - y * other.x) < 1e-6 &&
            std::abs(x * other.z - z * other.x) < 1e-6 &&
            std::abs(y * other.z - z * other.y) < 1e-6;
    }

    virtual bool is_perpendicular(const TVector& other) const {
        return std::abs(x * other.x + y * other.y + z * other.z) < 1e-6;
    }
};

class TVector2D : public TVector {
public:
    TVector2D(double x0, double y0) : TVector(x0, y0, 0) {}

    double length() const override {
        return std::sqrt(x * x + y * y);
    }
};

class TVector3D : public TVector {
public:
    TVector3D(double x0, double y0, double z0) : TVector(x0, y0, z0) {}

    double length() const override {
        return std::sqrt(x * x + y * y + z * z);
    }
};

void calculate(const TVector& v1, const TVector& v2, const TVector& v3, const TVector& v4, const TVector& v5, const TVector& v6, const TVector& v7);

TVector3D input_vector3d();

TVector2D input_vector2d();

#endif // TVECTOR_H
