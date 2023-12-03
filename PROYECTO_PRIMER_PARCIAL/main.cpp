#include <iostream>
#include "menu.h"

int main() {
    std::vector<std::string> listaOpciones = {"Opcion 1", "Opcion 2", "Opcin 3", "Opcion 4"};

    Menu menu("Menu Principal");
    menu.iniciar(listaOpciones);

    return 0;
}
