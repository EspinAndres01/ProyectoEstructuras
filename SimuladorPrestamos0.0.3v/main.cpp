#include <iostream>
#include "TablaAmortizacion.h"

int main() {
    double prestamo = 10000.0; // Monto del préstamo
    double tasaInteresAnual = 6.0; // Tasa de interés anual (%)
    int numeroCuotas = 25; // Número de cuotas
    std::string fechaInicial = "01/01/2023"; // Fecha inicial

    TablaAmortizacion tabla;
    tabla.generarTabla(prestamo, tasaInteresAnual, numeroCuotas, fechaInicial);
    tabla.mostrarTabla();
    //std::string directorio = "mi_carpeta"; // Directorio donde se guardará el archivo
    //tabla.guardarTablaCSV(directorio);
    return 0;
}
