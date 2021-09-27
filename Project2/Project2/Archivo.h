#pragma once
#include <vector>
using namespace std;
class Archivo {
	private:
		string filename;
		vector<string> contenido; // ListaSimple
		vector<string> comentarios; // Pila
	public:
		Archivo(){}
		Archivo(string filename){
			this->filename = filename;
		}
		~Archivo(){}

		string getFilename() { return this->filename; }
		vector<string> getContenido() { return this->contenido; }
		vector<string> getComentarios() { return this->comentarios; }

		void setFileName(string filename) { this->filename = filename; }

		void agregarContenido(string linea) {
			contenido.push_back(linea);
		}
		void agregarComentario(string comentario) {
			comentarios.push_back(comentario);
		}
};