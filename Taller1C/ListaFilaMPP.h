#pragma once
#include "NodoMPP.h"
class ListaFilaMPP{

private:
	NodoMPP* cabeza;
public:
	ListaFilaMPP();
	void agregar(Vehiculo* vehiculo, int fila, int columna);
};

