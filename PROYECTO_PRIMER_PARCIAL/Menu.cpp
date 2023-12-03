/***********************************************************************
 * Module:  Menu.cpp
 * Author:  kibok
 * Modified: s�bado, 2 de diciembre de 2023 19:44:59
 * Purpose: Implementation of the class Menu
 ***********************************************************************/

#include "Menu.h"
#include <conio.h>
////////////////////////////////////////////////////////////////////////
// Name:       Menu::mostrar(std::string& opciones, int opcionSeleccionada)
// Purpose:    Implementation of Menu::mostrar()
// Parameters:
// - opciones
// - opcionSeleccionada
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::mostrar(const std::vector<std::string>& opciones, int opcionSeleccionada) {
    system("cls");
    std::cout << "---- Menú ----\n";
    for (size_t i = 0; i < opciones.size(); ++i) {
        if (opcionSeleccionada == i) {
            std::cout << "> ";
        } else {
            std::cout << "  ";
        }
        std::cout << i + 1 << ". " << opciones[i] << "\n";
    }
    std::cout << "0. Salir\n";
}
////////////////////////////////////////////////////////////////////////
// Name:       Menu::obtenerOpcion(std::string& opciones)
// Purpose:    Implementation of Menu::obtenerOpcion()
// Parameters:
// - opciones
// Return:     int
////////////////////////////////////////////////////////////////////////

int Menu::obtenerOpcion(const std::vector<std::string>& opciones) {
    int opcion = 0;
    int tecla;
    int numOpciones = static_cast<int>(opciones.size());
    int opcionSeleccionada = 0;

    do {
        mostrar(opciones, opcionSeleccionada);

        tecla = _getch(); 
        if (tecla == 224) { 
            tecla = _getch(); 
            if (tecla == 72 && opcionSeleccionada > 0) { // Flecha arriba
                opcionSeleccionada--;
            } else if (tecla == 80 && opcionSeleccionada < numOpciones) { // Flecha abajo
                opcionSeleccionada++;
            }
        }
    } while (tecla != 13); // Enter

    return opcionSeleccionada;
}
////////////////////////////////////////////////////////////////////////
// Name:       Menu::manejarOpcion(int opcion, std::string& opciones)
// Purpose:    Implementation of Menu::manejarOpcion()
// Parameters:
// - opcion
// - opciones
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::manejarOpcion(int opcion, const std::vector<std::string>& opciones) {
    if (opcion >= 1 && opcion <= opciones.size()) {
        std::cout << "Ha seleccionado: " << opciones[opcion - 1] << "\n";
        // Realizar acciones según la opción seleccionada
    } else if (opcion == 0) {
        std::cout << "Saliendo del menú...\n";
    } else {
        std::cout << "Opción inválida. Por favor, elija una opción válida.\n";
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::iniciar(std::string& opciones)
// Purpose:    Implementation of Menu::iniciar()
// Parameters:
// - opciones
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::iniciar(const std::vector<std::string>& opciones) {
    int eleccion = obtenerOpcion(opciones);
    manejarOpcion(eleccion, opciones);
}
////////////////////////////////////////////////////////////////////////
// Name:       Menu::Menu(std::string& titulo)
// Purpose:    Implementation of Menu::Menu()
// Parameters:
// - titulo
// Return:     
////////////////////////////////////////////////////////////////////////

Menu::Menu(const std::string& titulo) : titulo(titulo) 
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::~Menu()
// Purpose:    Implementation of Menu::~Menu()
// Return:     
////////////////////////////////////////////////////////////////////////

Menu::~Menu()
{
   // TODO : implement
}