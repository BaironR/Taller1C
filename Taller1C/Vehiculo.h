#pragma once
#include <iostream>
class Vehiculo
{
private:
	std::string patente;
	std::string tipo;
public:
	Vehiculo(std::string patente, std::string tipo);
	std::string get_patente();
	std::string get_tipo();
};

