#include "Vehiculo.h"
/*
Implementación del archivo cabecera de vehículo.
Contiene la implementación del constructor, el método de retornar la patente y el tipo, y retornar
si está tuneado o no.
*/

//Constructor del vehículo (patente, tipo, está tuneado o no).
Vehiculo::Vehiculo(std::string patente, std::string tipo, bool esta_tuneado){
	this->patente = patente;
	this->tipo = tipo;
	this->esta_tuneado = esta_tuneado;
}

//Retornar la patente del vehículo.
std::string Vehiculo::get_patente(){
	return this->patente;
}

//Retornar el tipo del vehículo.
std::string Vehiculo::get_tipo(){
	return this->tipo;
}

//Retornar si el auto está tuneado o no.
bool Vehiculo::get_esta_tuneado(){
	return this->esta_tuneado;

}
