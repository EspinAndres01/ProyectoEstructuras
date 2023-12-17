#include "TablaAmortizacion.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <cstdio>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

TablaAmortizacion::TablaAmortizacion() : primero(nullptr), ultimo(nullptr) {}

void TablaAmortizacion::generarTabla(double prestamo, double tasaInteresAnual, int numeroCuotas, const std::string& fechaInicial) {
    double tasaInteresMensual = tasaInteresAnual / 12.0 / 100.0;
    double cuota = prestamo * (tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -numeroCuotas));

    double capitalPendiente = prestamo;
    std::string fechaPago = fechaInicial;

    // Crear el primer nodo con valores predefinidos
    primero = new NodoAmortizacion(0, 0, 0.0, 0.0, prestamo, fechaInicial);
    ultimo = primero;

    for (int i = 1; i <= numeroCuotas; ++i) {
        
        double interes = capitalPendiente * tasaInteresMensual;
        double amortizado = cuota - interes;
        capitalPendiente -= amortizado;
        if (capitalPendiente < 0) {
            capitalPendiente = 0; 
        }

        std::string fechaPago = Fecha::generarFechaPago(fechaInicial, i);

        NodoAmortizacion* nuevoPago = new NodoAmortizacion(i, cuota, amortizado, interes, capitalPendiente, fechaPago);

        ultimo->siguiente = nuevoPago;
        nuevoPago->anterior = ultimo;
        ultimo = nuevoPago;
        
        
    }
}

void TablaAmortizacion::mostrarTabla() {
    NodoAmortizacion* actual = primero;

    std::cout << "Mes | Cuota | Amortizado | Intereses | Capital Pendiente | Fecha de Pago" << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;

    while (actual != nullptr) {
        std::cout << std::setw(3) << actual->numeroMes << " | " << std::setw(6) << actual->cuota << " | "
                  << std::setw(10) << actual->amortizado << " | " << std::setw(9) << actual->intereses << " | "
                  << std::setw(17) << actual->capitalPendiente << " | " << actual->fechaPago << std::endl;

        actual = actual->siguiente;
    }

    std::cout << "-----------------------------------------------------------------------" << std::endl;
}

TablaAmortizacion::~TablaAmortizacion() {
    NodoAmortizacion* actual = primero;
    while (actual != nullptr) {
        NodoAmortizacion* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    primero = nullptr;
    ultimo = nullptr;
}

void TablaAmortizacion::guardarDatosEnArchivo(double prestamo, double tasaInteresAnual, int numeroCuotas) {
    std::ofstream archivo("datos_prestamo.txt", std::ios::app); // Abre el archivo en modo de añadir (append)

    if (!archivo) {
        // Si el archivo no existe, se crea uno nuevo
        archivo.open("datos_prestamo.txt");
    }

    if (archivo.is_open()) {
        archivo << prestamo << " " << tasaInteresAnual << " " << numeroCuotas <<std::endl;
        archivo.close();
        std::cout << "Los valores se han guardado exitosamente en 'datos_prestamo.txt'." << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo 'datos_prestamo.txt' para escritura." << std::endl;
    }
}

void TablaAmortizacion::cargarDatosDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        double prestamo;
        double tasaInteresAnual;
        int numeroCuotas;

        archivo >> prestamo >> tasaInteresAnual >> numeroCuotas;

        std::string fechaInicial = "-"; // Puedes establecer una fecha inicial predeterminada si es necesario

        // Generar la tabla de amortización con los valores leídos del archivo
        generarTabla(prestamo, tasaInteresAnual, numeroCuotas, fechaInicial);

        archivo.close();

    } else {
        std::cerr << "El archivo " << nombreArchivo << " no existe o no se pudo abrir." << std::endl;
    }
}
