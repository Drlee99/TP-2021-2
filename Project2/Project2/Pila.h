#include <iostream>
using namespace std;
template <typename T>
class Pila {
    Nodo<T>* inicio;
    Nodo<T>* fin;
    long cantidad;
public:
    Cola() {
        fin = inicio = nullptr;
        cantidad = 0;
    }
    void push(T e) {    //O(1)    
        Nodo<T>* n = new Nodo<T>(e);
        if (inicio == nullptr)
            inicio = fin = n;
        else {
            fin->siguiente = n;
            n->anterior = fin;
            fin = n;
        }
        ++cantidad;
    }
    void pop() {
        if (inicio == nullptr) return;
        Nodo<T>* aux = inicio;
        if (cantidad == 1)
            inicio = fin = nullptr;
        else {
            inicio = inicio->siguiente;
            inicio->anterior = nullptr;
        }
        delete aux;
        --cantidad;
    }
    void front(function<void(T)> fFront) {
        if (cantidad > 0)
            fFront(inicio->elemento);
    }
    bool empty() {
        return cantidad == 0;
    }
    int size() { return cantidad; }
};