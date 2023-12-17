#include "NodoAmortizacion.h"

NodoAmortizacion::NodoAmortizacion(int mes, double cuota, double amortizado, double intereses, double capital, const std::string& fecha)
    : numeroMes(mes), cuota(cuota), amortizado(amortizado), intereses(intereses),
      capitalPendiente(capital), fechaPago(fecha), siguiente(nullptr), anterior(nullptr) {}
