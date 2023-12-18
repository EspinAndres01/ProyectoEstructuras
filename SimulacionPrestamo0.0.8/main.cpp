#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "TablaAmortizacion.h"
#include "Fecha.h"
#include "validarValores.h"
#include <fstream>
#include "WebOpener.h"


TablaAmortizacion tabla;
Fecha fecha;

void mostrarMenu(int opcion) {
    system("cls");
    std::cout << "\n--------------GENERADOR DE PRESTAMO-----------------\n";
    std::cout << "\nSeleccione una opcion:\n\n";
    std::cout << (opcion == 1 ? "> " : "  ") << "1. Generar prestamo e ingresar valores.\n";
    std::cout << (opcion == 2 ? "> " : "  ") << "2. Recuperar informacion del archivo y generar tabla.\n";
    std::cout << (opcion == 3 ? "> " : "  ") << "4. Generar Backup\n";
    std::cout << (opcion == 4 ? "> " : "  ") << "5. Lista de respaldos\n";
    std::cout << (opcion == 5 ? "> " : "  ") << "6. Equipo de desarrollo\n";
    std::cout << (opcion == 6 ? "> " : "  ") << "7. Ayuda\n";
    std::cout << (opcion == 7 ? "> " : "  ") << "8. Salir\n";
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
    tabla.crearRespaldo("datos_prestamo.txt");
    pausa();
}
void realizarOpcion4() {
    system("cls");
    tabla.listarRespaldos("datos_prestamo.txt");
    std::string archivoRespaldo;
    std::cout << "Ingrese el nombre del archivo que desea restaurar: ";
    std::cin >> archivoRespaldo;
    tabla.restaurarRespaldo("datos_prestamo.txt", archivoRespaldo);
    pausa();
}

void realizarOpcion6() {
    system("cls");
    std::cout << "Saliendo del programa." << std::endl;

    pausa();
    exit(0);
}
void realizarOpcion5() {
    system("cls");
    std::cout << "Seleccione una opción:\n\n";
    std::cout << "  1. Ayuda\n";
    std::cout << "  2. Saliendo del programa\n\n";

    char opcionAyuda;
    std::cout << "Ingrese la opción: ";
    std::cin >> opcionAyuda;

    if (opcionAyuda == '1') {
        // Llamada a la nueva función para abrir una página web
        WebOpener::abrirPaginaWeb("doxy/html/index.html");
        std::cout << "\nSe abrió la página de ayuda en el navegador.\n";
    } else if (opcionAyuda == '2') {
        std::cout << "Saliendo del programa.\n";
        pausa();
        exit(0);
    } else {
        std::cout << "Opción no válida.\n";
    }

    pausa();
}
void mostrarImagenGrupoDesarrollo() {
    system("cls");
    const std::string rutaArchivoImagen = "gupo.txt"; // Ruta del archivo de imagen ASCII

    std::ifstream archivoImagen(rutaArchivoImagen);
    if (!archivoImagen.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        pausa();
        return;
    }

    std::string linea;
    while (getline(archivoImagen, linea)) {
        std::cout << linea << std::endl;
    }

    if (archivoImagen.eof()) {
        std::cout << "\t\t     GRUPO DE DESARROLLO" << std::endl;
    } else if (archivoImagen.fail()) {
        std::cout << "Error al leer el archivo." << std::endl;
    } else if (archivoImagen.bad()) {
        std::cout << "Error crítico al abrir el archivo." << std::endl;
    }

    archivoImagen.close();
    pausa();
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
                if (opcion < 7) opcion++;
                break;
            case 13: // Enter
                if (opcion == 1) {
                    realizarOpcion1();
                } else if (opcion == 2) {
                    realizarOpcion2();
                } else if (opcion == 3) {
                    realizarOpcion3();
                } else if(opcion==4){
                    realizarOpcion4();
                } else if(opcion==5){
                    mostrarImagenGrupoDesarrollo();
                } else if(opcion==6){
                    realizarOpcion5();
                } else if(opcion==7){
                    realizarOpcion6();
                }
                break;
            default:
                break;
        }
    } while (true);

    return 0;
}
