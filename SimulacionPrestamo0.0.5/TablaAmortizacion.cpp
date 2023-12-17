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
#include <iomanip> 

TablaAmortizacion::TablaAmortizacion() : primero(nullptr), ultimo(nullptr) {}

void TablaAmortizacion::generarTabla(double prestamo, double tasaInteresAnual, int numeroCuotas, const std::string& fechaInicial, int diaAleatorio) {
    double tasaInteresMensual = tasaInteresAnual / 12.0 / 100.0;
    double cuota = prestamo * tasaInteresMensual / (1 - pow(1 + tasaInteresMensual, -numeroCuotas));

    double capitalPendiente = prestamo;
    std::string fechaPago = fechaInicial;

    // Crear el primer nodo con valores predefinidos
    primero = new NodoAmortizacion(0, 0, 0.0, 0.0, prestamo, fechaInicial);
    ultimo = primero;

    for (int i = 1; i <= numeroCuotas; ++i) {
        double interes = capitalPendiente * tasaInteresMensual;
        double amortizado = cuota - interes;
        capitalPendiente -= amortizado;

        // Validar que el capital pendiente no sea negativo
        capitalPendiente = (capitalPendiente < 0) ? 0 : capitalPendiente;

        // Generar la fecha de pago
        std::string fechaPago = Fecha::generarFechaPago(fechaInicial, i);

        // Crear un nuevo nodo de amortización
        NodoAmortizacion* nuevoPago = new NodoAmortizacion(i, cuota, amortizado, interes, capitalPendiente, fechaPago);

        // Establecer relaciones entre nodos
        ultimo->siguiente = nuevoPago;
        nuevoPago->anterior = ultimo;
        ultimo = nuevoPago;
    }
}

void TablaAmortizacion::mostrarTabla() {
    NodoAmortizacion* actual = primero;

    std::cout << "\n\nMes | Cuota | Amortizado | Intereses | Capital Pendiente | Fecha de Pago" << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;

    while (actual != nullptr) {
        // Configurar el formato de salida para evitar la notación científica
        std::cout << std::fixed << std::setprecision(2); // Dos decimales después del punto decimal

        std::cout << std::setw(3) << actual->numeroMes << " | " << std::setw(8) << actual->cuota << " | "
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

void TablaAmortizacion::guardarDatosEnArchivo(double prestamo, double tasaInteresAnual, int numeroCuotas, int diaAleatorio) {
    std::ofstream archivo("datos_prestamo.txt", std::ios::app); // Abre el archivo en modo de añadir (append)

    if (!archivo) {
        // Si el archivo no existe, se crea uno nuevo
        archivo.open("datos_prestamo.txt");
    }

    if (archivo.is_open()) {
        archivo << prestamo << " " << tasaInteresAnual << " " << numeroCuotas << " " << diaAleatorio << std::endl;
        archivo.close();
        
    } else {
        std::cerr << "No se pudo abrir el archivo 'datos_prestamo.txt' para escritura." << std::endl;
    }
}


void TablaAmortizacion::visualizarDatosEnArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        std::cout << "Conjuntos de valores disponibles en el archivo:" << std::endl;

        int contador = 1;
        double prestamo, tasaInteresAnual;
        int numeroCuotas, diaAleatorio;

        while (archivo >> prestamo >> tasaInteresAnual >> numeroCuotas >> diaAleatorio) {
            std::cout << contador << ". Prestamo: " << prestamo << ", Tasa de Interes Anual: " << tasaInteresAnual
                      << ", Numero de Cuotas: " << numeroCuotas << ", Dia de pago: " << diaAleatorio << std::endl;
            contador++;
        }

        archivo.close();
    } else {
        std::cerr << "El archivo " << nombreArchivo << " no existe o no se pudo abrir." << std::endl;
    }
}

void TablaAmortizacion::cargarDatosDesdeArchivo(const std::string& nombreArchivo, int opcion) {
    std::ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        double prestamo, tasaInteresAnual;
        int numeroCuotas, diaAleatorio;

        int contador = 1;
        while (archivo >> prestamo >> tasaInteresAnual >> numeroCuotas >> diaAleatorio) {
            if (contador == opcion) {
                std::string fechaInicial = "-";
                generarTabla(prestamo, tasaInteresAnual, numeroCuotas, fechaInicial, diaAleatorio);
                archivo.close();
                return;
            }
            contador++;
        }

        std::cout << "Opción no válida." << std::endl;
        archivo.close();

    } else {
        std::cerr << "El archivo " << nombreArchivo << " no existe o no se pudo abrir." << std::endl;
    }
}
