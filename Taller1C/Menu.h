#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
class Menu{

public:
	Menu();
	void iniciar();
	void estacionar_vehiculo();
	void desocupar_espacio(std::string patente);
	void visualizacion();
	void estadisticas();
};

