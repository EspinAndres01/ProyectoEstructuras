#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <limits>
#include <iomanip> 

int ingresar_enteros(const char* msj);
int borrar(char* datos, int& i);
float ingresar_reales(const char* msj);
std::string ingresar_alfabetico(const char* msj);
std::string ingresarCedula();

std::string ingresarCedula(const char* msj) {
    char datos[11]; // Se reserva espacio para 11 caracteres: 10 dígitos + el carácter nulo '\0'
    char c;
    int i = 0;

    std::cout << msj << std::endl;
    while ((c = getch()) != 13 && i < 10) { // 13 es el valor ASCII de la tecla 'Enter' (retorno de carro)
        if (isdigit(c)) { // Verificar si el carácter es un dígito
            printf("%c", c); // Mostrar el dígito ingresado
            datos[i++] = c; // Agregar el dígito al array de datos
        }
    }
    datos[i] = '\0'; // Agregar el carácter nulo al final del array para formar la cadena

    if (i != 10) { // Verificar si se ingresaron exactamente 10 dígitos
        std::cout << "\nDebe ingresar exactamente 10 digitos numericos." << std::endl;
        return ""; // Retornar una cadena vacía que indique error
    }

    return std::string(datos); // Convertir el array de caracteres a un objeto std::string
}

// Función para generar un nuevo ID
std::string generarID() {
    static int contador = 0; // Variable estática para llevar la cuenta de los registros

    std::string ID = "L" + std::to_string(contador); // Concatenar 'L' con el contador

    // Completar con ceros a la izquierda para que tenga 5 caracteres en total
    ID = ID + std::string(4 - ID.length(), '0') + std::to_string(contador);
    
    contador++; // Incrementar el contador para el próximo registro
    return ID;
}

// Función para generar y mostrar múltiples IDs
void generarYMostrarIDs(int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        std::string nuevoID = generarID();
        std::cout << "Nuevo ID generado: " << nuevoID << std::endl;
    }
}

int ingresar_enteros(const char* msj) {
    char* datos = new char[10];
    char c;
    int i = 0;

    std::cout<<msj<<std::endl;
    while ((c = getch()) != 13 && i < 9) {
        if ((c >= '0' && c <= '9')|| c == 8) {
            if(c == 8){
                i = borrar(datos,i);
            }else{
                printf("%c", c);
                datos[i++] = c;
            }

        }
    }
    datos[i] = '\0';
    return atoi(datos);
}

float ingresar_reales(const char* msj) {
    char* datos = new char[12];
    char c;
    int i = 0;
    bool hay_punto = false;
    int posicion_punto;

    std::cout<<msj<<std::endl;

    while ((c = getch()) != 13 && i < 11) {
        if ((c >= '0' && c <= '9') || (c == '.' && !hay_punto)|| c == 8 || c == '-') {
            if(!((c == '.')&& i == 0)){
                if(!((c == '-') && i != 0)){
                    if (c == 8) {
                        i = borrar(datos, i);
                        if((i+1) == posicion_punto){
                            hay_punto = false;
                        }
                    }
                    else {
                        std::cout<<c;
                        datos[i++] = c;

                        if (c == '.') {
                            posicion_punto = i;
                            hay_punto = true;
                        }
                    }
                }
            }
        }
    }
    datos[i] = '\0';
    return atof(datos);
}

std::string ingresar_alfabetico(const char* msj) {
    char datos[21];
    char c;
    int i = 0;

    std::cout<<msj<<std::endl;
    while ((c = getch()) != 13 && i < 20) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')|| c == 32||c == 8) {
            if (c == 8) {
                i = borrar(datos, i);
            } else {
                std::cout<<c;
                datos[i++] = c;
            }
        }
    }
    datos[i] = '\0';
    return std::string(datos);
}


int borrar(char* datos, int& i) {
    if (i > 0) {
        std::cout << "\b \b";
        i--;
        datos[i] = '\0';
        return i;
    }
    return 0;
}
#endif // VALIDACIONES_H_INCLUDED
