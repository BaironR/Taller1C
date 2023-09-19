#pragma once
#include "Vehiculo.h"
/*
La interfaz para los nodos de la matriz.
Como atributos privados, contiene: punteros de nodos a los nodos izquierdo y superior, número de fila y columna
en el que será almacenado, y un puntero al vehículo almacenado.
Métodos públicos: constructor del nodo (vehículo, fila, columna), obtener nodo izquierdo, obtener nodo superior,
designar nodo izquierdo y superior, obtener fila y columna, y obtener el puntero al vehículo.
*/
class NodoMPP {

private:
	NodoMPP* izquierdo; //Nodo izquierdo.
	NodoMPP* superior; //Nodo superior.
	int fila; //Valor de fila.
	int columna; //Valor de columna.
	Vehiculo* vehiculo; //Vehículo almacenado.
public:
	NodoMPP(Vehiculo* vehiculo, int fila, int columna); //Constructor del nodo.
	NodoMPP* get_izquierdo(); //Obtener nodo izquierdo.
	NodoMPP* get_superior(); //Obtener nodo superior.
	void set_izquierdo(NodoMPP* izquierdo); //Designar nodo izquierdo.
	void set_superior(NodoMPP* superior); //Designar nodo superior.
	int get_fila(); //Obtener fila. 
	int get_columna(); //Obtener columna.
	Vehiculo* get_vehiculo(); //Obtener vehículo.
};

