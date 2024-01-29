#include <iostream>
#include <string>
#include <cctype>
#include <conio.h>

std::string ingresarCedula();

std::string ingresarCedula(const char* msj) {
    char datos[11];
    char c;
    int i = 0;

    std::cout << msj << std::endl;
    while ((c = getch()) != 13 && i < 10) {
        if (isdigit(c) || c == 8) {
            if (c == 8 && i > 0) {
                std::cout << "\b \b";
                i--;
            } else if (isdigit(c)) {
                printf("%c", c);
                datos[i++] = c;
            }
        }
    }
    datos[i] = '\0';

    while (i == 0) {
        std::cout << "\nPor favor, ingrese un valor valido: ";
        while ((c = getch()) != 13 && i < 10) {
            if (isdigit(c) || c == 8) {
                if (c == 8 && i > 0) {
                    std::cout << "\b \b";
                    i--;
                } else if (isdigit(c)) {
                    printf("%c", c);
                    datos[i++] = c;
                }
            }
        }
        datos[i] = '\0';
    }

    if (i != 10) {
        std::cout << "\nDebe ingresar exactamente 10 digitos numericos." << std::endl;
        return ""; // Retornar una cadena vacía que indique error
    }

    return std::string(datos);
}
