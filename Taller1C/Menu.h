#pragma once
#include "MPP.h" //Importar el archivo cabecera de la matriz poco poblada.
#include <stack> //Importar la pila.

/*
El menú principal del programa, en el que el usuario podrá interactuar.
Como atributos privados, se posee:
Un puntero al objeto "matriz poco poblada" (que será para la matriz), una pila de punteros a enteros para los
espacios desocupados, el valor de fila y columna en 1, y una variable n inicializada en 0.

Métodos públicos: Constructor del menú, el método de iniciar el programa, estacionar vehículo (requerimiento 1
del programa), desocupar un espacio (teniendo en cuenta la patente del auto, requerimiento 2), rellenar los 
espacios desocupados, visualizar el estacionamiento (requerimiento 3), y obtener estadísticas (requerimiento 4).
*/
class Menu{

private:
	MPP* matriz; //Puntero a la matriz poco poblada.
	std::stack<int*> espacios_desocupados; //Pila de punteros a enteros (espacios desocupados, representados por vectores).
	int fila = 1; //Valor de fila actual (inicializado en 1).
	int columna = 1; //Valor de columna actual (inicializado en 1).
	int n = 0; //Valor de n (inicializado en 0).
public:
	Menu(); //Constructor del menú.
	void iniciar(); //Método para iniciar el programa.
	void estacionar_vehiculo(); //Estacionar vehículo (requerimiento 1).
	void desocupar_espacio(std::string patente); //Desocupar espacio a partir de la patente (requerimiento 2).
	void rellenar_espacios_desocupados(); //Rellenar espacios desocupados.
	void ver_estacionamiento(); //Visualizar el estacionamiento (requerimiento 3).
	void estadisticas(); //Obtener estadísticas (requerimiento 4).
};

