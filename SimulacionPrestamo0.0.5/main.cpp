#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "TablaAmortizacion.h"
#include "Fecha.h"
#include "validaciones.h"
#include "validarValores.h"

TablaAmortizacion tabla;
Fecha fecha;

void mostrarMenu(int opcion) {
    system("cls");
    std::cout << "\n--------------GENERADOR DE PRESTAMO-----------------\n";
    std::cout << "\nSeleccione una opcion:\n\n";
    std::cout << (opcion == 1 ? "> " : "  ") << "1. Generar prestamo e ingresar valores.\n";
    std::cout << (opcion == 2 ? "> " : "  ") << "2. Recuperar informacion del archivo y generar tabla.\n";
    std::cout << (opcion == 3 ? "> " : "  ") << "3. Salir\n";
}

void pausa() {
    std::cout << "\nPresione Enter para continuar...\n";
    while (_getch() != 13); 
}


void realizarOpcion1() {
    system("cls");
    std::cout << "---------------SIMULADOR DE PRESTAMOS-------------------\n";
    double prestamo = ingresarMontoValidado();
    double tasaInteresAnual = ingresarTasaInteresValidada();
    int numeroCuotas = ingresarNumeroCuotasValidado();


    int diaAleatorio = fecha.obtenerDiaAleatorio();

    tabla.guardarDatosEnArchivo(prestamo, tasaInteresAnual, numeroCuotas, diaAleatorio);
    tabla.generarTabla(prestamo, tasaInteresAnual, numeroCuotas, "-", diaAleatorio);
    tabla.mostrarTabla();
    std::cout << "\nLos valores se han guardado exitosamente en 'datos_prestamo.txt'." << std::endl;

    pausa();
}

void realizarOpcion2() {
    system("cls");
    tabla.visualizarDatosEnArchivo("datos_prestamo.txt");
    int indice=ingresar_enteros("\nIngrese el elemento que quiere recuperar");
    tabla.cargarDatosDesdeArchivo("datos_prestamo.txt",indice);
    tabla.mostrarTabla();

    pausa();
}

void realizarOpcion3() {
    system("cls");
    std::cout << "Saliendo del programa." << std::endl;

    pausa();
    exit(0);
}

int main() {
    int opcion = 1;
    char key;

    do {
        mostrarMenu(opcion);
        key = _getch();

        switch (key) {
            case 72: // Flecha arriba
                if (opcion > 1) opcion--;
                break;
            case 80: // Flecha abajo
                if (opcion < 3) opcion++;
                break;
            case 13: // Enter
                if (opcion == 1) {
                    realizarOpcion1();
                } else if (opcion == 2) {
                    realizarOpcion2();
                } else if (opcion == 3) {
                    realizarOpcion3();
                }
                break;
            default:
                break;
        }
    } while (true);

    return 0;
}
