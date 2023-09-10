#include "ListaFilaMPP.h"

ListaFilaMPP::ListaFilaMPP(){ 
	this->cabeza = new NodoMPP(NULL, NULL, 0);
	this->cabeza->set_izquierdo(this->cabeza);
}

void ListaFilaMPP::agregar(Vehiculo* vehiculo, int fila, int columna){

	if (fila >= 0 && columna >= 0) {

		NodoMPP* nodo = new NodoMPP(vehiculo, fila, columna);

		if (this->cabeza->get_izquierdo() == this->cabeza){
			nodo->set_izquierdo(this->cabeza);
			this->cabeza->set_izquierdo(nodo);
			return;
		}

		NodoMPP* actual = this->cabeza->get_izquierdo();
		NodoMPP* anterior = this->cabeza;

		while (actual != this->cabeza && actual->get_columna() > columna){
			anterior = this->cabeza->get_izquierdo();
			actual = this->cabeza->get_izquierdo();
		}

		nodo->set_izquierdo(actual);
		anterior->set_izquierdo(nodo);
	}
}
