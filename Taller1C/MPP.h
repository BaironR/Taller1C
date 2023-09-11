#pragma once
#include "ListaColumnaMPP.h"
#include "ListaFilaMPP.h"
class MPP{

private:
	ListaColumnaMPP* columnas;
	ListaFilaMPP* filas;

public: 
	MPP();
	void agregar(Vehiculo* vehiculo, int fila, int columna);
};

