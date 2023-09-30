#include "NodoMPP.h"
#include "Vehiculo.h"

/*
Implementación del archivo cabecera del nodo de la matriz.
Contiene la implementación del constructor, obtenciones de nodos izquierdo y superior, fila, columna y vehículo,
y los métodos de asignación de nodos izquierdo y superior.
*/

//Constructor del nodo (vehículo, fila, columna).
NodoMPP::NodoMPP(Vehiculo* vehiculo, int fila, int columna){
	this->izquierdo = NULL; //Nodo izquierdo es nulo al inicializar.
	this->superior = NULL; //Nodo superior es nulo al inicializar.
	this->fila = fila;
	this->columna = columna;
	this->vehiculo = vehiculo;
}

/*
Destructor del nodoMPP, elimina el vehiculo que contiene
*/
NodoMPP::~NodoMPP(){
	delete vehiculo;
}

//Retornar el nodo izquierdo.
NodoMPP* NodoMPP::get_izquierdo() {
	return this->izquierdo;
}

//Retornar el nodo superior.
NodoMPP* NodoMPP::get_superior() {
	return this->superior;
}

//Designar el nodo izquierdo.
void NodoMPP::set_izquierdo(NodoMPP* izquierdo) {
	this->izquierdo = izquierdo;
}

//Designar el nodo superior.
void NodoMPP::set_superior(NodoMPP* superior) {
	this->superior = superior;
}

//Retornar el número de fila.
int NodoMPP::get_fila() {
	return this->fila;
}

//Retornar el número de columna.
int NodoMPP::get_columna() {
	return this->columna;
}

//Retornar el puntero al vehículo.
Vehiculo* NodoMPP::get_vehiculo() {
	return this->vehiculo;
}
