#include "NodoAmortizacion.h"

NodoAmortizacion::NodoAmortizacion(int mes, double cuota, double amortizado, double intereses, double capital, const std::string& fecha, std::string ID)
    : numeroMes(mes), cuota(cuota), amortizado(amortizado), intereses(intereses),
      capitalPendiente(capital), fechaPago(fecha), IDUsuario(ID),siguiente(nullptr), anterior(nullptr) {}
