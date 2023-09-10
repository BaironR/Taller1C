#include "Vehiculo.h"

Vehiculo::Vehiculo(std::string patente, std::string tipo){
	this->patente = patente;
	this->tipo = tipo;
}

std::string Vehiculo::get_patente(){
	return this->patente;
}

std::string Vehiculo::get_tipo(){
	return this->tipo;
}
