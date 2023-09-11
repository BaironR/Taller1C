#include "Menu.h"
#include "MPP.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include "Vehiculo.h"
#include <queue>
#include <set>

Menu::Menu(){
}

void Menu::iniciar(){

	while (true) {
		std::cout <<
			"****************************************\n"
			"             Menú sistema PAL           \n"
			"****************************************\n"
			"[1] Estacionar vehículo\n"
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
	}
}

void Menu::estacionar_vehiculo(){

	int cant_aleatoria = 1 + rand() % 600;
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
			conjunto.insert(vehiculo->get_patente());
		}

		cant_aleatoria--;
	}

	conjunto.clear();
	MPP* matriz = new MPP();
	int fila = 1;
	int columna = 1;
	int n = 0;

	while (!cola.empty()) {
		Vehiculo* vehiculo = cola.front();

		if (!(fila % 2 + 3*n)){

			matriz->agregar(vehiculo, fila, columna);
			columna++;

			if (columna == 31) {
				columna = 1;
				fila++;
			}

			if (fila > 30) {
				return;
			}
		}

		else {
			fila++;
			columna = 1;
			matriz->agregar(vehiculo, fila, columna);
			n++;
		}

		cola.pop();
		delete vehiculo; // Liberar la memoria asignada a los objetos Vehiculo
	}
}

void Menu::desocupar_espacio(std::string patente)
{
}

void Menu::visualizacion()
{
}

void Menu::estadisticas()
{
}
