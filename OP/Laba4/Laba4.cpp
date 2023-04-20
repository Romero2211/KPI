#include <iostream>
#include"polynomial.h"

int main() {
    Polynomial P1, P2, P3;
    double value, point;

    int choice;
    do {
        std::cout << "\n ";
        std::cout << "1. Create P1 polynomial" << std::endl;
        std::cout << "2. Create P2 polynomial" << std::endl;
        std::cout << "3. Create P3 polynomial" << std::endl;
        std::cout << "4. Increase coefficients of P1 polynomial by a value" << std::endl;
        std::cout << "5. Decrease coefficients of P2 polynomial by a value" << std::endl;
        std::cout << "6. Check if coefficients of P1 and P2 polynomials are equal" << std::endl;
        std::cout << "7. Evaluate P3 polynomial at a given point" << std::endl;
        std::cout << "8. Print P1 polynomial" << std::endl;
        std::cout << "9. Print P2 polynomial" << std::endl;
        std::cout << "10. Print P3 polynomial" << std::endl;
        std::cout << "11. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            double a, b, c, d;
            std::cout << "\n ";
            std::cout << "Enter coefficients of P1 polynomial (a, b, c, d): ";
            std::cin >> a >> b >> c >> d;
            P1 = Polynomial(a, b, c, d);
            break;
        case 2:
            double coeffs[4];
            std::cout << "\n ";
            std::cout << "Enter coefficients of P2 polynomial (a, b, c, d): ";
            std::cin >> coeffs[0] >> coeffs[1] >> coeffs[2] >> coeffs[3];
            P2 = Polynomial(coeffs);
            break;
        case 3:
            std::cout << "\n ";
            std::cout << "Enter coefficients of P3 polynomial (a, b, c, d): ";
            std::cin >> a >> b >> c >> d;
            P3 = Polynomial(a, b, c, d);
            break;
        case 4:
            std::cout << "\n ";
            std::cout << "Enter a value to increase coefficients of P1 polynomial: ";
            std::cin >> value;
            P1 += value;
            break;
        case 5:
            std::cout << "\n ";
            std::cout << "Enter a value to decrease coefficients of P2 polynomial: ";
            std::cin >> value;
            P2 -= value;
            break;
        case 6:
            if (P1 == P2) {
                std::cout << "Coefficients of P1 and P2 polynomials are equal." << std::endl;
            }
            else {
                std::cout << "Coefficients of P1 and P2 polynomials are not equal." << std::endl;
            }
            break;
        case 7:
            std::cout << "Enter a value of x to evaluate P3 polynomial: ";
            std::cin >> point;
            std::cout << "P3(" << point << ") = " << P3.evaluate(point) << std::endl;
            break;
        case 8:
            std::cout << "\n ";
            std::cout << "P1 polynomial: ";
            P1.print();
            std::cout << "\n ";
            break;
        case 9:
            std::cout << "\n ";
            std::cout << "P2 polynomial: ";
            P2.print();
            std::cout << "\n ";
            break;
        case 10:
            std::cout << "\n ";
            std::cout << "P3 polynomial: ";
            P3.print();
            std::cout << "\n ";
            break;
        case 11:
            std::cout << "\n ";
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "\n ";
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

    } while (choice != 11);

    return 0;
}
