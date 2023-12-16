#pragma once
#include "Nodo.h"

template <typename T>
class ListaDoble {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;

public:
    ListaDoble();
    void Insertar(T valor);
    void Buscar(T valor);
    void Eliminar(T valor);
    void Mostrar();
};



