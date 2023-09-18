#include "Vehiculo.h"

Vehiculo::Vehiculo(std::string patente, std::string tipo, bool esta_tuneado){
	this->patente = patente;
	this->tipo = tipo;
	this->esta_tuneado = esta_tuneado;
}

std::string Vehiculo::get_patente(){
	return this->patente;
}

std::string Vehiculo::get_tipo(){
	return this->tipo;
}

bool Vehiculo::get_esta_tuneado(){
	return this->esta_tuneado;

}
