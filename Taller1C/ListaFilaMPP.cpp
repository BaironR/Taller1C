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

		NodoMPP* aux = this->cabeza->get_izquierdo();

		while (aux != this->cabeza){

			if (columna == aux->get_columna() && fila == aux->get_fila()){
				return;
			}

			else if (columna > aux->get_columna() && ) {

			}
			aux = aux->get_izquierdo();
		}

	}
}
