#include "Menu.h"
#include "Vehiculo.h"
#include <queue>

void Menu::iniciar(){

	while (true) {

		std::cout<<
			       "****************************************\n"  
			       "             Menú sistema PAL           \n" 
			       "****************************************\n" 
			       "[1] Estacionar vehículo\n" 
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
	std::queue<Vehiculo> cola;

	while (cant_aleatoria != 0) {
		Vehiculo* vehiculo = new Vehiculo();
		cant_aleatoria--;
	}
}
