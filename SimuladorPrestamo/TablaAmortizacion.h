#pragma once
#include "NodoAmortizacion.h"
#include "Fecha.h"
class TablaAmortizacion {
private:
    NodoAmortizacion* primero;
    NodoAmortizacion* ultimo;
    static unsigned int contadorArchivos;
public:
    TablaAmortizacion();
    void generarTabla(double prestamo, double tasaInteresAnual, int numeroCuotas, const std::string& fechaInicial);
    void mostrarTabla();
    ~TablaAmortizacion();
    void guardarTablaCSV(const std::string& nombreDirectorio);
    std::string obtenerNombreArchivoFechaHora();
    void guardarDatosEnArchivo(double prestamo, double tasaInteresAnual, int numeroCuotas);
    void cargarDatosDesdeArchivo(const std::string& nombreArchivo);
};


