#include "MPP.h"

MPP::MPP(){

	columnas.push_back(NULL);
	filas.push_back(NULL);

	for (int i = 1; i <= 30; i++) {
		NodoMPP* cabezaColumna = new NodoMPP(NULL,0,NULL);
		NodoMPP* cabezaFila = new NodoMPP(NULL, NULL, 0);
		columnas.push_back(cabezaColumna);
		filas.push_back(cabezaFila);
		cabezaColumna->set_superior(cabezaColumna);
		cabezaFila->set_izquierdo(cabezaFila);
	}
}


void MPP::agregar_a_fila(NodoMPP* nodo, int fila) {

	if (filas[fila]->get_izquierdo() == filas[fila]) {
		nodo->set_izquierdo(filas[fila]);
		filas[fila]->set_izquierdo(nodo);
		return;
	}

	NodoMPP* actual2 = filas[fila]->get_izquierdo();
	NodoMPP* anterior2 = filas[fila];

	while (actual2 != filas[fila] && actual2->get_fila() < fila) {
		anterior2 = actual2;
		actual2 = actual2->get_izquierdo();
	}

	nodo->set_izquierdo(actual2);
	anterior2->set_izquierdo(nodo);
}

void MPP::agregar_a_columna(NodoMPP* nodo, int columna) {

	if (columnas[columna]->get_superior() == columnas[columna]) {
		nodo->set_superior(columnas[columna]);
		columnas[columna]->set_superior(nodo);
		return;
	}

	NodoMPP* actual1 = columnas[columna]->get_superior();
	NodoMPP* anterior1 = columnas[columna];

	while (actual1 != columnas[columna] && actual1->get_columna() < columna) {
		anterior1 = actual1;
		actual1 = actual1->get_superior();
	}

	nodo->set_superior(actual1);
	anterior1->set_superior(nodo);
}

void MPP::agregar(Vehiculo* vehiculo, int fila, int columna){

	if (fila > 0 && fila <= 30 && columna > 0 && columna <= 30) {

		NodoMPP* nodo = new NodoMPP(vehiculo, fila, columna);
		agregar_a_fila(nodo,fila);
		agregar_a_columna(nodo, columna);
	}
}

void MPP::ver_estacionamiento(){

	for (int fila = 1; fila <= 30; fila++) {
		for (int columna = 1; columna <= 30; columna++) {
			Vehiculo* vehiculo = obtener_vehiculo(fila, columna);
			if (vehiculo != nullptr) {
				std::cout << "A ";
			} else {
				std::cout << ". "; // Agrega espacios para alinear las columnas
			}
		}
		std::cout << std::endl; // Cambia de línea después de cada fila
	}
}

Vehiculo* MPP::obtener_vehiculo(int fila, int columna){

	NodoMPP* aux = filas[fila]->get_izquierdo();

	while (aux != filas[fila]) {

		if (aux->get_columna() == columna) {
			return aux->get_vehiculo();
		}

		aux = aux->get_izquierdo();
	}

	return nullptr;
}

bool MPP::esta_llena() {
	for (int columna = 1; columna <= 30; columna++) {
		Vehiculo* vehiculo = obtener_vehiculo(30, columna);

		if (vehiculo == nullptr) {
			return false;
		}
	}
}

