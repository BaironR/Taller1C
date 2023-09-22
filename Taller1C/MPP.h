#pragma once
#include "NodoMPP.h"
/*
La clase de la matriz poco poblada (MPP).
Como atributos privados, se posee la fila de columnas, y la columna de filas de nodos de la matriz, en forma de punteros..
Como m�todos p�blicos, se poseen: el constructor de la matriz, el m�todo de agregar un nodo a la matriz,
agregar a fila y columna, el m�todo para imprimir el estacionamiento, obtener un veh�culo a partir de la fila y columna,
eliminar un veh�culo a partir de la patente, eliminar un nodo de una fila y columna (pasando como par�metro un puntero a
un vector que especifica las coordenadas del nodo eliminado), la lista de patentes de los veh�culos en la matriz, un m�todo
booleano para comprobar si la matriz est� vac�a, y un m�todo para visualizar estad�sticas respecto a los autos estacionados.
*/
class MPP{
private:
	NodoMPP** columnas;
	NodoMPP** filas;
public:
	MPP(); //Constructor de la matriz poco poblada.
	void agregar(Vehiculo* vehiculo, int fila, int columna); //Agregar veh�culo a la matriz.
	void agregar_a_fila(NodoMPP* nodo, int fila); //Agregar veh�culo a una fila especificada.
	void agregar_a_columna(NodoMPP* nodo, int columna); //Agregar veh�culo a una columna especificada.
	void ver_estacionamiento(); //Desplegar el estacionamiento.
	Vehiculo* obtener_vehiculo(int fila, int columna); //Obtener un veh�culo a partir de la fila y columna.
	int* eliminar_patente(std::string patente); //Eliminar veh�culo a partir de su patente.
	void eliminar_de_fila(std::string patente, int* arreglo, int fila); //Eliminar nodo de una fila.
	void eliminar_de_columna(std::string patente, int* arreglo, int columna); //Eliminar nodo de columna.
	void lista_patentes(); //Imprimir la lista de patentes de veh�culos estacionados.
	bool esta_llena(); //Comprobar si la matriz est� llena.
	void ver_estadisticas(); //M�todo para ver estad�sticas.
};

