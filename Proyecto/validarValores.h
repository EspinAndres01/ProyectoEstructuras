#include <iostream>
#include <limits>
#include "validaciones.h"

double ingresarMontoValidado() {
    double monto;
    do {
        monto=ingresar_enteros("\nIngrese el monto del prestamo (máximo 9 cifras): ");

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
        tasaInteres=ingresar_enteros("\nIngrese la tasa de interes anual (% entre 0 y 100):");

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
        numeroCuotas=ingresar_enteros("\nIngrese el numero de cuotas (mayor que cero y menor que 500): ");

        if (std::cin.fail() || numeroCuotas <= 0||numeroCuotas >=500) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Numero de cuotas invalido. Ingrese un numero valido mayor que cero o menor que 500." << std::endl;
        } else {
            break;
        }
    } while (true);

    return numeroCuotas;
}
