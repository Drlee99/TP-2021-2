#pragma once
#include <direct.h>
#include "User.h"
using namespace std;
class Gestor {
	private:
		vector<User> users;
	public:
		Gestor() {
			leerDatosDeUsuarios();
			leerDatosDeArchivos();
		}
		~Gestor() {}
		void leerDatosDeUsuarios(){
			ifstream archivo("usuarios.txt");
			string username, nombre, apellido;
			while (getline(archivo, username, ',')) {
				getline(archivo, nombre, ',');
				getline(archivo, apellido);
				User u(username, nombre, apellido);
				this->users.push_back(u);
			}
		}
		void leerDatosDeArchivos(){
			ifstream archivo("archivos.txt");
			string username, filename;
			while (getline(archivo, username, ',')) {
				getline(archivo, filename);
				int pos = buscarUsuario(username);
				
				Archivo a;
				a.setFileName(filename);

				string linea;
				ifstream archivo2("archivos/" + username + "/" + filename);
				while (getline(archivo2, linea)) {
					a.agregarContenido(linea);
				}

				string comentario, username2, filename2;
				ifstream archivo3("comentarios.txt");
				while (getline(archivo3, username2, ',')) {
					getline(archivo3, filename2, ',');
					getline(archivo3, comentario);
					if (username2 == username && filename2 == filename) {
						a.agregarComentario(comentario);
					}
				}
				

				this->users[pos].agregarArchivo(a);
			}
		}
		void escribirUsuario(User u) {
			ofstream archivo("usuarios.txt", ios_base::app); // append
			archivo << u.getUsername() << "," << u.getNombre() << "," << u.getApellido() << endl;
			archivo.close();
		}
		void escribirUsuarioArchivo(User u, Archivo a) {
			ofstream archivo("archivos.txt", ios_base::app); // append
			archivo << u.getUsername() << "," << a.getFilename() << endl;
			archivo.close();
		}
		void escribirArchivo(User u, Archivo a) {
			string ruta;
			ruta = "archivos";
			_mkdir(ruta.c_str());
			ruta = ruta+"/"+ u.getUsername();
			_mkdir(ruta.c_str());

			ofstream archivo(ruta+"/"+a.getFilename(), ios_base::app); // append
			for (int i = 0; i < a.getContenido().size(); i++) {
				archivo << a.getContenido()[i] << endl;
			}
			archivo.close();

			ofstream archivo2("comentarios.txt", ios_base::app); // append
			for (int i = 0; i < a.getComentarios().size(); i++) {
				archivo2 << u.getUsername() << "," << a.getFilename() << "," << a.getComentarios()[i] << endl;
			}
			archivo2.close();
		}
		void menu() {
			cout << "Gestor de archivos" << endl;
			cout << "Opcion 1. Registrar usuario" << endl;
			cout << "Opcion 2. Registrar archivo" << endl;
			cout << "Opcion 3. Mostrar archivos" << endl;
			cout << "Opcion 4. Filtrar archivos" << endl;
			cout << "Opcion 5. Salir" << endl;
			cout << "Ingresar opcion: ";
		}
		void registrarUsuario() {
			string username, nombre, apellido;
			cin.ignore();
			cout << "Registro de usuario" << endl;
			cout << "Username (sin espacios): "; getline(cin, username);
			int pos = buscarUsuario(username);
			if (pos == -1) {
				cout << "Nombre: "; getline(cin, apellido);
				cout << "Apellido: "; getline(cin, apellido);
				User u(username, nombre, apellido);
				this->users.push_back(u);
				this->escribirUsuario(u); // Escritura en archivo *.txt
			}
			else {
				cout << "No se puede registrar un usuario con username existente" << endl;
			}
		}
		void registrarArchivo() {
			string username, filename, linea, comentario;
			cout << "Registro de archivo" << endl;
			cout << "Username del autor: "; cin >> username;
			int pos = buscarUsuario(username);
			if (pos != -1) {
				cin.ignore();
				cout << "Nombre del archivo: "; getline(cin, filename);
				cout << "Contenido del archivo: "; getline(cin, linea);
				cout << "Comentario del archivo: "; getline(cin, comentario);
				Archivo a(filename);
				a.agregarContenido(linea);
				a.agregarComentario(comentario);
				this->users[pos].agregarArchivo(a);
				escribirUsuarioArchivo(this->users[pos], a); // Escritura en fichero
				escribirArchivo(this->users[pos], a);
			}
			else {
				cout << "El usuario no existe" << endl;
			}	
		}
		int buscarUsuario(string username) {
			for (int i = 0; i < this->users.size(); i++) {
				if (users[i].getUsername() == username) {
					return i;
				}
			}
			return - 1;
		}
		void mostrarArchivos() {
			for (int i = 0; i < this->users.size(); i++) {
				cout << this->users[i].toString();
				cout << "Archivos registrados: " << endl;
				for (int j = 0; j < this->users[i].getArchivos().cantidad(); j++) {
					cout << this->users[i].getArchivos().obtener(j).getFilename() << endl;
					for (int k = 0; k < this->users[i].getArchivos().obtener(j).getContenido().size(); k++) {
						cout << this->users[i].getArchivos().obtener(j).getContenido()[k] << endl;
					}
					for (int k = 0; k < this->users[i].getArchivos().obtener(j).getComentarios().size(); k++) {
						cout << this->users[i].getArchivos().obtener(j).getComentarios()[k] << endl;
					}
				}
				if (this->users[i].getArchivos().cantidad() == 0) {
					cout << "El usuario no registro archivos" << endl;
				}
				cout << endl;
			}
		}
		void filtrarArchivos() {
			string opcion;
			do {
				system("CLS");
				cout << "Filtrato de archivos" << endl;
				cout << "Opcion 1. Filtrar archivo con nombre igual a: " << endl;
				cout << "Opcion 2. Filtrar archivos con nombres que inician con: " << endl;
				cout << "Opcion 3. Filtrar archivos con nombres que finalizan con: " << endl;
				cout << "Opcion 4. Filtrar archivos con nombres que estan contenidos en: " << endl;
				cout << "Opcion 5. Filtrar archivos con nombres que no estan contenidos en: " << endl;
				cout << "Opcion 6. Salir" << endl;
				cout << "Ingresar opcion:¨";
				cin >> opcion;
				if (opcion == "1") {
					system("CLS");
					filtrarIgualA();
					system("PAUSE");
				}
				else if (opcion == "2") {
					system("CLS");
					filtrarIniciaCon();
					system("PAUSE");
				}
				else if (opcion == "3") {
					system("CLS");
					filtrarFinalizaCon();
					system("PAUSE");
				}
				else if (opcion == "4") {
					system("CLS");
					filtrarEstaContenidoEn();
					system("PAUSE");
				}
				else if (opcion == "5") {
					system("CLS");
					filtrarNoEstaContenidoEn();
					system("PAUSE");
				}
				else if (opcion == "6") {
					break;
				}
				else {
					cout << "Opcion incorrecta" << endl;
					system("PAUSE");
				}
			} while (opcion != "6");
		}
		void filtrarIgualA() {
			string cadena;
			cout << "Filtrato de archivos" << endl;
			cout << "Filtrar archivo con nombre igual a: "; cin >> cadena;
			int encontrados = 0;
			for (int i = 0; i < this->users.size(); i++) {
				string username = this->users[i].getUsername();
				for (int j = 0; j < this->users[i].getArchivos().cantidad(); j++) {
					string nombreArchivo = this->users[i].getArchivos().obtener(j).getFilename();
					if (nombreArchivo == cadena) {
						cout << "Username: " + username + "Archivo: " + nombreArchivo << endl;
						encontrados++;
					}
				}
			}
			if (encontrados == 0) {
				cout << "No se encontraron archivos utilizando el criterio del filtro" << endl;
			}
		}
		
		void filtrarIniciaCon() {
			string cadena;
			cout << "Filtrato de archivos" << endl;
			cout << "Filtrar archivos con nombres que inician con: " << endl; cin >> cadena;
			int encontrados = 0;
			for (int i = 0; i < this->users.size(); i++) {
				string username = this->users[i].getUsername();
				for (int j = 0; j < this->users[i].getArchivos().cantidad(); j++) {
					string nombreArchivo = this->users[i].getArchivos().obtener(j).getFilename();
					// string cad = "holaxyz";
					// cout << cad.substr(0,3) -> "hol"
					// cout << cad.substr(2,2) -> "la"
					if (nombreArchivo.substr(0, cadena.size()) == cadena) {
						cout << "Username: " + username + "Archivo: " + nombreArchivo << endl;
						encontrados++;
					}
				}
			}
			if (encontrados == 0) {
				cout << "No se encontraron archivos utilizando el criterio del filtro" << endl;
			}
		}
		void filtrarFinalizaCon() {
			string cadena;
			cout << "Filtrato de archivos" << endl;
			cout << "Filtrar archivos con nombres que finalizan con: " << endl; cin >> cadena;
			int encontrados = 0;
			for (int i = 0; i < this->users.size(); i++) {
				string username = this->users[i].getUsername();
				for (int j = 0; j < this->users[i].getArchivos().cantidad(); j++) {
					string nombreArchivo = this->users[i].getArchivos().obtener(j).getFilename();
					// string cad = "holaxyz";
					// cout << cad.substr(0,3) -> "hol"
					// cout << cad.substr(2,2) -> "la"
					if (nombreArchivo.substr(nombreArchivo.size()-cadena.size(), cadena.size()) == cadena) {
						cout << "Username: " + username + "Archivo: " + nombreArchivo << endl;
						encontrados++;
					}
				}
			}
			if (encontrados == 0) {
				cout << "No se encontraron archivos utilizando el criterio del filtro" << endl;
			}
		}
		void filtrarEstaContenidoEn() {
			string cadena;
			cout << "Filtrato de archivos" << endl;
			cout << "Filtrar archivos con nombres que estan contenidos en: " << endl; cin >> cadena;
			int encontrados = 0;
			for (int i = 0; i < this->users.size(); i++) {
				string username = this->users[i].getUsername();
				for (int j = 0; j < this->users[i].getArchivos().cantidad(); j++) {
					string nombreArchivo = this->users[i].getArchivos().obtener(j).getFilename();
					if (cadena.find(nombreArchivo) != -1) {
						cout << "Username: " + username + "Archivo: " + nombreArchivo << endl;
						encontrados++;
					}
				}
			}
			if (encontrados == 0) {
				cout << "No se encontraron archivos utilizando el criterio del filtro" << endl;
			}
		}
		void filtrarNoEstaContenidoEn() {
			string cadena;
			cout << "Filtrato de archivos" << endl;
			cout << "Filtrar archivos con nombres que no estan contenidos en: " << endl; cin >> cadena;
			int encontrados = 0;
			for (int i = 0; i < this->users.size(); i++) {
				string username = this->users[i].getUsername();
				for (int j = 0; j < this->users[i].getArchivos().cantidad(); j++) {
					string nombreArchivo = this->users[i].getArchivos().obtener(j).getFilename();
					if (cadena.find(nombreArchivo) == -1) {
						cout << "Username: " + username + "Archivo: " + nombreArchivo << endl;
						encontrados++;
					}
				}
			}
			if (encontrados == 0) {
				cout << "No se encontraron archivos utilizando el criterio del filtro" << endl;
			}
		}
		void iniciar() {
			string opcion;
			do {
				system("CLS");
				menu();
				cin >> opcion;
				if (opcion == "1") {
					system("CLS");
					registrarUsuario();
					system("PAUSE");
				}
				else if (opcion == "2") {
					system("CLS");
					registrarArchivo();
					system("PAUSE");
				}
				else if (opcion == "3") {
					system("CLS");
					mostrarArchivos();
					system("PAUSE");
				}
				else if (opcion == "4") {
					system("CLS");
					filtrarArchivos();
					system("PAUSE");
				}
				else if (opcion == "5") {
					cout << "Hasta pronto" << endl;
					system("PAUSE");
				}
				else {
					cout << "Opcion incorrecta" << endl;
					system("PAUSE");

				}

			} while (opcion != "5");
		}
};