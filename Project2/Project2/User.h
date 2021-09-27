#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <functional>
#include "Archivo.h"
#include "ListaSimple.h"
using namespace std; 
class User {
private:
    string username;
    string nombre;
    string apellido;
    ListaSimple<Archivo> archivos;
public:
    User(string username, string nombre, string apellido) {
        this->username = username;
        this->nombre = nombre;
        this->apellido = apellido;
    }
    string getUsername() { return this->username; }
    string getNombre() { return this->nombre; }
    string getApellido() { return this->apellido; }
    ListaSimple<Archivo> getArchivos() { return this->archivos; }
    string toString() { return "Username: "+username + ", Nombre: " + nombre + ", Apellido: " + apellido + "\n"; }

    void agregarArchivo(Archivo a) {
        /*
        ListaSimple<Archivo> archivosCopia = archivos;
        archivosCopia.insertar(a);
        this->archivos = archivosCopia;
        */
        this->archivos.insertar(a);
    }
};