
#include <iostream>
#include <string>
#include <cctype> // Para las funciones isalpha y toupper
#include <conio.h> // Para getch()

std::string ingresarNombreApellidoMayusculas(const char* msj) {
    char datos[21];
    char c;
    int i = 0;

    std::cout << msj << std::endl;
    while ((c = getch()) != 13 && i < 20) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ') || (c == 8)) {
            if (c >= 'a' && c <= 'z') {
                c = toupper(c);
            }

            if (c == 8 && i > 0) {
                std::cout << "\b \b";
                i--;
            } else if (c != 8) {
                std::cout << c;
                datos[i++] = c;
            }
        }
    }

    datos[i] = '\0';

    while (i == 0) {
        std::cout << "\nPor favor, ingrese un valor valido: ";
        while ((c = getch()) != 13 && i < 20) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ') || (c == 8)) {
                if (c >= 'a' && c <= 'z') {
                    c = toupper(c);
                }

                if (c == 8 && i > 0) {
                    std::cout << "\b \b";
                    i--;
                } else if (c != 8) {
                    std::cout << c;
                    datos[i++] = c;
                }
            }
        }
        datos[i] = '\0';
    }

    return std::string(datos);
}
