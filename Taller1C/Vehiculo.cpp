#include "Vehiculo.h"
/*
Implementaci�n del archivo cabecera de veh�culo.
Contiene la implementaci�n del constructor, el m�todo de retornar la patente y el tipo, y retornar
si est� tuneado o no.
*/

//Constructor del veh�culo (patente, tipo, est� tuneado o no).
Vehiculo::Vehiculo(std::string patente, std::string tipo, bool esta_tuneado){
	this->patente = patente;
	this->tipo = tipo;
	this->esta_tuneado = esta_tuneado;
}

//Retornar la patente del veh�culo.
std::string Vehiculo::get_patente(){
	return this->patente;
}

//Retornar el tipo del veh�culo.
std::string Vehiculo::get_tipo(){
	return this->tipo;
}

//Retornar si el auto est� tuneado o no.
bool Vehiculo::get_esta_tuneado(){
	return this->esta_tuneado;

}
