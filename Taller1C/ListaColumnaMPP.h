#pragma once
#include "NodoMPP.h"
class ListaColumnaMPP{

private:
	NodoMPP* cabeza;
public:
	ListaColumnaMPP();
	void agregar(Vehiculo* vehiculo, int fila, int columna);

};

