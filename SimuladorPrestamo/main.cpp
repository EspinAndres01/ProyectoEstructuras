#include <iostream>
#include <fstream>
#include "TablaAmortizacion.h"

void mostrarMenu() {
    std::cout << "Seleccione una opción:" << std::endl;
    std::cout << "1. Generar préstamo e ingresar valores." << std::endl;
    std::cout << "2. Recuperar información del archivo y generar tabla." << std::endl;
    std::cout << "3. Salir." << std::endl;
    std::cout << "Ingrese el número de la opción: ";
}

int main() {
    TablaAmortizacion tabla;
    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                double prestamo;
                double tasaInteresAnual;
                int numeroCuotas;

                std::cout << "Ingrese el monto del préstamo: ";
                std::cin >> prestamo;
                std::cout << "Ingrese la tasa de interés anual (%): ";
                std::cin >> tasaInteresAnual;
                std::cout << "Ingrese el número de cuotas: ";
                std::cin >> numeroCuotas;

                tabla.guardarDatosEnArchivo(prestamo, tasaInteresAnual, numeroCuotas);
                tabla.generarTabla(prestamo, tasaInteresAnual, numeroCuotas,"-");
                tabla.mostrarTabla();
                std::cout << "Valores guardados exitosamente." << std::endl;
                break;
            }
            case 2:
                tabla.cargarDatosDesdeArchivo("datos_prestamo.txt");
                tabla.mostrarTabla();
                break;
            case 3:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo." << std::endl;
                break;
        }
    } while (opcion != 3);

    return 0;
}
