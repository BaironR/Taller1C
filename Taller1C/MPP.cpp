#include "MPP.h"

MPP::MPP(){
	this->columnas = new ListaColumnaMPP();
	this->filas = new ListaFilaMPP();
}

void MPP::agregar(Vehiculo* vehiculo, int fila, int columna){
	this->columnas->agregar(vehiculo,fila,columna);
	this->filas->agregar(vehiculo,fila,columna);
}
