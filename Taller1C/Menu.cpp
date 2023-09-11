#include "Menu.h"
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

		std::cout<<
			       "****************************************\n"  
			       "             Men� sistema PAL           \n" 
			       "****************************************\n" 
			       "[1] Estacionar veh�culo\n" 
			       "[2] Desocupar espacio\n" 
			       "[3] Visualizar estacionamiento\n" 
			       "[4] Ver registros\n" 
			       "[5] Cerrar programa\n";

		std::string opcion;
		std::cin >> opcion;

		if (opcion == "5") {
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
	srand(time(nullptr));

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

	while (!cola.empty()) {
		Vehiculo* vehiculo = cola.front();
		std::cout << "Patente: " << vehiculo->get_patente() << std::endl;
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
