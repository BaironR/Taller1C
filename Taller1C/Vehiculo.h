#pragma once
#include <iostream>
class Vehiculo
{
private:
	std::string patente;
	std::string tipo;
	bool esta_tuneado;
public:
	Vehiculo(std::string patente, std::string tipo, bool esta_tuneado);
	std::string get_patente();
	std::string get_tipo();
	bool get_esta_tuneado();
};

