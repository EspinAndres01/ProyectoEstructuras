#include "Nodo.h"

template <typename T>
Nodo<T>::Nodo(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}

template <typename T>
void Nodo<T>::setDato(T valor) {
    dato = valor;
}

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* siguienteNodo) {
    siguiente = siguienteNodo;
}

template <typename T>
void Nodo<T>::setAnterior(Nodo<T>* anteriorNodo) {
    anterior = anteriorNodo;
}

template <typename T>
T Nodo<T>::getDato() {
    return dato;
}

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() {
    return siguiente;
}

template <typename T>
Nodo<T>* Nodo<T>::getAnterior() {
    return anterior;
}
