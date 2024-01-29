#include "Cedula.h"
#include <iostream>
#include <cctype>

bool Cedula::validarCedulaEcuatoriana(const std::string &cedula) {
    if (cedula.length() != 10) {
        return false;
    }

    //Verificar si es todo digitos
    for (char c : cedula) {
        if (!isdigit(c)) {
            return false;
        }
    }

    //Algoritmo para validar el ultimo digito de la cedula

    int total = 0;
    for (int i = 0; i < 9; ++i) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }
        total += digito;
    }

    int verificador = total % 10 != 0 ? 10 - (total % 10) : 0;
    int ultimoDigito = cedula[9] - '0';

    return verificador == ultimoDigito;
}
