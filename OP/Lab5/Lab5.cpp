#include <iostream>
#include <cmath>
#include "TVector.h"

int main() {
    TVector2D v1 = input_vector2d();
    TVector2D v2 = input_vector2d();
    TVector2D v3 = input_vector2d();
    TVector3D v4 = input_vector3d();
    TVector3D v5 = input_vector3d();
    TVector3D v6 = input_vector3d();
    TVector3D v7 = input_vector3d();

    calculate(v1, v2, v3, v4, v5, v6, v7);

    return 0;
}