#pragma once
#include <vector>
#include "NodoMPP.h"
class MPP{

private:
	std::vector<NodoMPP*> columnas;
	std::vector<NodoMPP*> filas;

public: 
	MPP();
	void agregar(Vehiculo* vehiculo, int fila, int columna);
	void agregar_a_fila(NodoMPP* nodo, int fila);
	void agregar_a_columna(NodoMPP* nodo, int columna);
	void ver_estacionamiento();
	Vehiculo* obtener_vehiculo(int fila, int columna);
	bool esta_llena();
};

