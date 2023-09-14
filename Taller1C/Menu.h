#pragma once
#include "MPP.h"
class Menu{

private:
	MPP* matriz;
	int fila = 1;
	int columna = 1;
	int n = 0;

public:
	Menu();
	void iniciar();
	void estacionar_vehiculo();
	void desocupar_espacio(std::string patente);
	void visualizacion();
	void estadisticas();
};

