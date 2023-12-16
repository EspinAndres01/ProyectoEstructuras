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

unsigned int TablaAmortizacion::contadorArchivos = 0;

std::string TablaAmortizacion::obtenerNombreArchivoFechaHora() {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* tiempo = std::localtime(&tiempoActual);

    std::stringstream nombreArchivo;
    nombreArchivo << "Amortizacion-" << (tiempo->tm_year + 1900) << "-"
                 << std::setw(2) << std::setfill('0') << (tiempo->tm_mon + 1) << "-"
                 << std::setw(2) << std::setfill('0') << tiempo->tm_mday << "-"
                 << std::setw(2) << std::setfill('0') << tiempo->tm_hour << ":"
                 << std::setw(2) << std::setfill('0') << tiempo->tm_min << ":"
                 << std::setw(2) << std::setfill('0') << tiempo->tm_sec
                 << "-" << std::setw(3) << std::setfill('0') << ++contadorArchivos; // Incrementar el contador para hacer el nombre único

    return nombreArchivo.str();
}

void TablaAmortizacion::guardarTablaCSV(const std::string& nombreDirectorio) {
    std::string nombreArchivo = obtenerNombreArchivoFechaHora() + ".csv";
    std::string rutaCompleta = nombreDirectorio + "/" + nombreArchivo;

    // Verificar si el directorio ya existe
    std::ifstream dir(nombreDirectorio);
    if (!dir.good()) {
        // Intentar crear el directorio si no existe
        if (std::system(("mkdir" + nombreDirectorio).c_str()) != 0) {
            std::cerr << "Error al crear el directorio" << std::endl;
            return;
        }
    }

    // Declarar el objeto std::ofstream fuera de la estructura condicional
    std::ofstream archivo;
    archivo.open(rutaCompleta); // Abrir el archivo

    if (archivo.is_open()) {
        archivo << "Mes,Cuota,Amortizado,Intereses,Capital Pendiente,Fecha de Pago\n";

        NodoAmortizacion* actual = primero;

        while (actual != nullptr) {
            archivo << actual->numeroMes << ","
                    << actual->cuota << ","
                    << actual->amortizado << ","
                    << actual->intereses << ","
                    << actual->capitalPendiente << ","
                    << actual->fechaPago << "\n";

            actual = actual->siguiente;
        }

        archivo.close();
        std::cout << "La tabla se ha guardado exitosamente en " << rutaCompleta << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo " << rutaCompleta << " para escritura." << std::endl;
    }
}