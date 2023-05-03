#include "TVector.h"

void calculate(const TVector& v1, const TVector& v2, const TVector& v3, const TVector& v4, const TVector& v5, const TVector& v6, const TVector& v7) {
    double parallel_sum = 0.0;
    double perpendicular_sum = 0.0;

    for (const auto& v : { &v2, &v3 }) {
        if (v->is_parallel(v1)) {
            parallel_sum += v->length();
        }
    }

    for (const auto& v : { &v5, &v6, &v7 }) {
        if (v->is_perpendicular(v4)) {
            perpendicular_sum += v->length();
        }
    }

    std::cout << "Sum of lengths of vectors parallel to v1: " << parallel_sum << std::endl;
    std::cout << "Sum of lengths of vectors perpendicular to v4: " << perpendicular_sum << std::endl;
}

TVector3D input_vector3d() {
    double x, y, z;
    std::cout << "Enter the x, y, z coordinates of a 3D vector: ";
    std::cin >> x >> y >> z;
    return TVector3D(x, y, z);
}

TVector2D input_vector2d() {
    double x, y;
    std::cout << "Enter the x, y coordinates of a 2D vector: ";
    std::cin >> x >> y;
    return TVector2D(x, y);
}
