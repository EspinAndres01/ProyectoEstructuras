#pragma once
#include <string>

class NodoAmortizacion {
public:
    int numeroMes;
    double cuota;
    double amortizado;
    double intereses;
    double capitalPendiente;
    std::string fechaPago;
    NodoAmortizacion* siguiente;
    NodoAmortizacion* anterior;
    std::string IDUsuario; 

    NodoAmortizacion(int mes, double cuota, double amortizado, double intereses, double capital, const std::string& fecha,std::string IDUsuario);
};