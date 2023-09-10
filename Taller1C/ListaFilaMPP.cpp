#include "ListaFilaMPP.h"

ListaFilaMPP::ListaFilaMPP(){ 
	this->cabeza = new NodoMPP(NULL, NULL, 0);
}

void ListaFilaMPP::agregar(Vehiculo* vehiculo, int fila, int columna){

	if (fila >= 0 && columna >= 0) {

		NodoMPP* nodo = new NodoMPP(vehiculo, fila, columna);

		if (this->cabeza->get_izquierdo() == NULL) {
			this->cabeza->set_izquierdo(nodo);
			nodo->set_izquierdo(this->cabeza);
			return;
		}

		NodoMPP* aux = this->cabeza;

		while (aux->get_izquierdo() != NULL) {

		}

	}
}
