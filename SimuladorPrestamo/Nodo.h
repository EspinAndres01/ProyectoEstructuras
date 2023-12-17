    #pragma once
    #include <iostream>
    #include <string>

    using namespace std;

    template <typename T>
    class Nodo {
    private:
        T dato;
        Nodo<T>* siguiente;
        Nodo<T>* anterior;

    public:
        Nodo(T valor);
        void setDato(T valor);
        void setSiguiente(Nodo<T>* siguienteNodo);
        void setAnterior(Nodo<T>* anteriorNodo);
        T getDato();
        Nodo<T>* getSiguiente();
        Nodo<T>* getAnterior();
    };

