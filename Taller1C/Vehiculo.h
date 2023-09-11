#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
class Vehiculo
{
private:
	std::string patente;
	std::string tipo;
public:
	Vehiculo();
	std::string get_patente();
	std::string get_tipo();
};

