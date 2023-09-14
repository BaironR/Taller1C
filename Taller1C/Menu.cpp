#include "Menu.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include "Vehiculo.h"
#include <queue>
#include <set>

Menu::Menu(){
	this->matriz = new MPP();
}

void Menu::iniciar(){

	srand(time(nullptr));

	while (true) {
		std::cout <<
			"****************************************\n"
			"             Menu sistema PAL           \n"
			"****************************************\n"
			"[1] Estacionar vehiculo\n"
			"[2] Desocupar espacio\n"
			"[3] Visualizar estacionamiento\n"
			"[4] Ver registros\n"
			"[5] Cerrar programa" << std::endl;

		std::string opcion;
		std::cin >> opcion;

		if (opcion == "5"){
		    std::cout << "Programa finalizado. Muchas gracias" << std::endl;
			break;
		}

		if (opcion == "1") {
			estacionar_vehiculo();
		}

		if (opcion == "3") {
			visualizacion();
		}
	}
}

void Menu::estacionar_vehiculo(){
	
	if (!this->matriz->esta_llena()) {
		int cant_aleatoria = 1 + (rand() % 100);
		std::cout << cant_aleatoria;
		std::queue<Vehiculo*> cola;
		std::set<std::string> conjunto;

		while (cant_aleatoria != 0) {

			std::string tipos[] = { "Auto", "Camioneta","Furgoneta","Moto" };
			std::string* punt_tipo = &tipos[0];
			std::string tipo = *(punt_tipo += (rand() % 4));
			std::string patente;

			for (int i = 0; i < 4; ++i) {
				patente += 'A' + (rand() % 26);
			}

			for (int i = 0; i < 2; ++i) {
				patente += '0' + (rand() % 10);
			}


			Vehiculo* vehiculo = new Vehiculo(patente, tipo);

			if (conjunto.find(vehiculo->get_patente()) == conjunto.end()) {
				cola.push(vehiculo);
				conjunto.insert(patente);

			}
			else {
				delete vehiculo;
			}

			cant_aleatoria--;
		}

		conjunto.clear();

		while (!cola.empty() && !this->matriz->esta_llena()) {

			Vehiculo* vehiculo = cola.front();

			if ((fila % (2 + 3 * n) == 0)) {

				n++;
				fila++;
				columna = 1;
			}

			this->matriz->agregar(vehiculo, fila, columna);
			columna++;

			if (columna == 31) {
				columna = 1;
				fila++;
			}

			cola.pop();
		}

	} else {

		std::cout << "El estacionamiento ya no tiene espacios para almacenar mas vehiculos" << std::endl;
	}
}

void Menu::desocupar_espacio(std::string patente){
}

void Menu::visualizacion(){
	this->matriz->ver_estacionamiento();
}

void Menu::estadisticas()
{
}
