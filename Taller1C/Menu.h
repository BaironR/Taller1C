#pragma once
#include "MPP.h"
#include <stack>
class Menu{

private:
	MPP* matriz;
	std::stack<int*> espacios_desocupados;
	int fila = 1;
	int columna = 1;
	int n = 0;

public:
	Menu();
	void iniciar();
	void estacionar_vehiculo();
	void desocupar_espacio(std::string patente);
	void rellenar_espacios_desocupados();
	void ver_estacionamiento();
	void estadisticas();
};

