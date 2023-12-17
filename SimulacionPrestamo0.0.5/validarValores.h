#include <iostream>
#include <limits>

double ingresarMontoValidado() {
    double monto;
    do {
        std::cout << "Ingrese el monto del prestamo (máximo 9 cifras): ";
        std::cin >> monto;

        if (std::cin.fail() || monto <= 0 || monto >= 1000000000) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Monto invalido. Ingrese un numero valido mayor que cero y con un máximo de 9 cifras." << std::endl;
        } else {
            break;
        }
    } while (true);

    return monto;
}

double ingresarTasaInteresValidada() {
    double tasaInteres;
    do {
        std::cout << "Ingrese la tasa de interes anual (% entre 0 y 100): ";
        std::cin >> tasaInteres;

        if (std::cin.fail() || tasaInteres < 0 || tasaInteres > 100) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Tasa de interes invalida. Ingrese un número valido entre 0 y 100." << std::endl;
        } else {
            break;
        }
    } while (true);

    return tasaInteres;
}

int ingresarNumeroCuotasValidado() {
    int numeroCuotas;
    do {
        std::cout << "Ingrese el numero de cuotas (mayor que cero): ";
        std::cin >> numeroCuotas;

        if (std::cin.fail() || numeroCuotas <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Numero de cuotas invalido. Ingrese un numero valido mayor que cero." << std::endl;
        } else {
            break;
        }
    } while (true);

    return numeroCuotas;
}
