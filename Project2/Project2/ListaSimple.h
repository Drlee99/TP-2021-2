#include <iostream>
#include <cstdlib>
using namespace std;
template <typename Tipo>
struct Nodo {
    Tipo elemento;
    Nodo<Tipo>* siguiente;
    Nodo(Tipo e) { elemento = e; siguiente = nullptr; }
};
template <typename Tipo>
struct ListaSimple {
    Nodo<Tipo>* inicio;
    ListaSimple() {
        inicio = nullptr;
        //asumo que no tiene elementos
    }
    void insertar(Nodo<Tipo>* n) {
        //para 0 elementos
        if (inicio == nullptr)
            inicio = n;
        //para 1--m elementos
        else
        {
            Nodo<Tipo>* aux = inicio;
            while (aux->siguiente != nullptr)
                aux = aux->siguiente;
            aux->siguiente = n;
        }
    }
    void insertar(Tipo e) {
        Nodo<Tipo>* nuevo = new Nodo<Tipo>(e);
        //para 0 elementos
        if (inicio == nullptr)
            inicio = nuevo;
        //para 1--m elementos
        else
        {
            Nodo<Tipo>* aux = inicio;
            while (aux->siguiente != nullptr)
                aux = aux->siguiente;
            aux->siguiente = nuevo;
        }
    }
    void mostrar() {
        Nodo<Tipo>* aux = inicio;
        while (aux->siguiente != nullptr) {
            cout << aux->elemento << " ";
            aux = aux->siguiente;
        }
        cout << aux->elemento << " ";
    }
    Tipo obtener(int pos) {
        Nodo<Tipo>* aux = inicio;
        for (int i = 0; i < pos; i++) {
            aux = aux->siguiente;
        }
        return aux->elemento;
    }
    int cantidad() {
        short c = 0;
        Nodo<Tipo>* aux = inicio;
        while (aux != nullptr) {
            c++;
            aux = aux->siguiente;
        }
        return c;
    }
};