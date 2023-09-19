#pragma once
#include <iostream>
/*
La clase Veh�culo.
Como atributos privados, se tienen la patente y el tipo de veh�culo, ambos de tipo string, y 
un booleano si el auto est� tuneado o no.
El tipo de veh�culo puede ser auto, camioneta, furgoneta o moto.
M�todos p�blicos: constructor, retornar patente, retornar tipo, booleano si est� tuneado o no.
*/
class Vehiculo
{
private:
	std::string patente; //Patente
	std::string tipo; //Tipo de veh�culo (auto, camioneta, furgoneta o moto).
	bool esta_tuneado; //Est� tuneado o no.
public:
	Vehiculo(std::string patente, std::string tipo, bool esta_tuneado); //Constructor de veh�culo
	std::string get_patente(); //Obtener patente
	std::string get_tipo(); //Obtener tipo de veh�culo.
	bool get_esta_tuneado(); //Obtener si est� tuneado o no.
};

