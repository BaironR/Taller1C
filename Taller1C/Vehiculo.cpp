#include "Vehiculo.h"

Vehiculo::Vehiculo(){

	srand(time(nullptr));

	std::string tipos[] = {"Auto", "Camioneta","Furgoneta","Moto"};
	std::string* punt_tipo = &tipos[0];

	char letras[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	char* punt_char = &letras[0];

    std::string numeros = std::to_string(rand()%10) + std::to_string(rand() % 10);

	for (int i = 0; i < 4; ++i) {
		this->patente += *(punt_char + (rand() % 26));
	}

	this->patente += numeros;

	this->tipo = *(punt_tipo += (rand() % 4));
}

std::string Vehiculo::get_patente(){
	return this->patente;
}

std::string Vehiculo::get_tipo(){
	return this->tipo;
}
