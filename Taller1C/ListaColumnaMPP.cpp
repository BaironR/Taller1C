#include "ListaColumnaMPP.h"

ListaColumnaMPP::ListaColumnaMPP() {
	this->cabeza = new NodoMPP(NULL, NULL, 0);
	this->cabeza->set_superior(this->cabeza);
}

void ListaColumnaMPP::agregar(Vehiculo* vehiculo, int fila, int columna) {

	if (fila > 0 && columna > 0 && fila <= 30 && columna <= 30) {

		NodoMPP* nodo = new NodoMPP(vehiculo, fila, columna);

		if (this->cabeza->get_superior() == this->cabeza) {
			nodo->set_superior(this->cabeza);
			this->cabeza->set_superior(nodo);
			return;
		}

		NodoMPP* actual = this->cabeza->get_superior();
		NodoMPP* anterior = this->cabeza;

		while (actual != this->cabeza && actual->get_fila() < fila) {
			anterior = actual;
			actual = actual->get_superior();
		}

		nodo->set_superior(actual);
		anterior->set_superior(nodo);
	}
}
