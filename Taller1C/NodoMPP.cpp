#include "NodoMPP.h"
#include "Vehiculo.h"

NodoMPP::NodoMPP(Vehiculo* vehiculo, int fila, int columna){
	this->izquierdo = NULL;
	this->superior = NULL;
	this->fila = fila;
	this->columna = columna;
	this->vehiculo = vehiculo;
}

NodoMPP* NodoMPP::get_izquierdo(){
	return this->izquierdo;
}

NodoMPP* NodoMPP::get_superior(){
	return this->superior;
}

void NodoMPP::set_izquierdo(NodoMPP* izquierdo){
	this->izquierdo = izquierdo;
}

void NodoMPP::set_superior(NodoMPP* superior){
	this->superior = superior;
}

int NodoMPP::get_fila(){
	return this->fila;
}

int NodoMPP::get_columna(){
	return this->columna;
}

Vehiculo* NodoMPP::get_vehiculo(){
	return this->vehiculo;
}
