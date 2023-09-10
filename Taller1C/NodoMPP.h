#pragma once
#include "Vehiculo.h"
class NodoMPP{

private:
	NodoMPP* izquierdo;
	NodoMPP* superior;
	int fila;
	int columna;
	Vehiculo* vehiculo;
public:
	NodoMPP(Vehiculo* vehiculo, int fila, int columna);
	NodoMPP* get_izquierdo();
	NodoMPP* get_superior();
	void set_izquierdo(NodoMPP* izquierdo);
	void set_superior(NodoMPP* superior);
	int get_fila();
	int get_columna();
	Vehiculo* get_vehiculo();
};

