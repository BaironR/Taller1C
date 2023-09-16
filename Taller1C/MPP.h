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
	int* eliminar_patente(std::string patente);
	void eliminar_de_fila(std::string patente, int* arreglo, int fila);
	void eliminar_de_columna(std::string patente, int* arreglo, int columna);
	void lista_patentes();
	bool esta_llena();
};

