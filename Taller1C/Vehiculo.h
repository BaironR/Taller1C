#pragma once
#include <iostream>
/*
La clase Vehículo.
Como atributos privados, se tienen la patente y el tipo de vehículo, ambos de tipo string, y 
un booleano si el auto está tuneado o no.
El tipo de vehículo puede ser auto, camioneta, furgoneta o moto.
Métodos públicos: constructor, retornar patente, retornar tipo, booleano si está tuneado o no.
*/
class Vehiculo
{
private:
	std::string patente; //Patente
	std::string tipo; //Tipo de vehículo (auto, camioneta, furgoneta o moto).
	bool esta_tuneado; //Está tuneado o no.
public:
	Vehiculo(std::string patente, std::string tipo, bool esta_tuneado); //Constructor de vehículo
	std::string get_patente(); //Obtener patente
	std::string get_tipo(); //Obtener tipo de vehículo.
	bool get_esta_tuneado(); //Obtener si está tuneado o no.
};

