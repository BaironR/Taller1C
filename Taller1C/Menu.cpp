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

		do {
			try {

				std::string opcion;
				std::cout <<
					"****************************************\n"
					"             Menu sistema PAL           \n"
					"****************************************\n"
					"[1] Estacionar vehiculo\n"
					"[2] Desocupar espacio\n"
					"[3] Visualizar estacionamiento\n"
					"[4] Ver registros\n"
					"[5] Cerrar programa" << std::endl;

				std::cin >> opcion;
				int opcionInt = std::stoi(opcion);

				if (opcionInt == 5) {
					std::cout << "Programa finalizado, muchas gracias." << std::endl;
					return;
				}

				switch (opcionInt) {

				case(1) :

					if (espacios_desocupados.empty()) {
						estacionar_vehiculo();

					} else {
						rellenar_espacios_desocupados();
					}
			
					break;

				case(2):
                {
				std::cout << "Ingrese la patente que desea eliminar: " << std::endl;
				this->matriz->lista_patentes();
				std::string patente;
				std::cin >> patente;
				desocupar_espacio(patente);
				break; 
				}
		
				case(3):
					ver_estacionamiento();
					break;

				case(4):

				default:
					std::cout << "Dicha opcion no existe, intente nuevamente";
					break;
				}

			} catch (const std::invalid_argument& e) {
				std::cerr << "Excepcion de tipo: " << e.what() << " Ingrese una opcion valida" << std::endl;

			} catch (const std::out_of_range& e) {
				std::cerr << "Excepcion de tipo std::out_of_range: " << e.what() << " Ingrese una opcion valida" << std::endl;
			}

		}while(true);
	}
}

void Menu::estacionar_vehiculo(){
	
	if (!this->matriz->esta_llena()){
		int cant_aleatoria = 1 + (rand() % 100);
		int contador_vehiculos_agregados = 0;
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

			if ((this->fila % (2 + 3 * n) == 0)) {
				n++;
				this->fila++;
				this->columna = 1;
			}

			this->matriz->agregar(vehiculo, fila, columna++);
			contador_vehiculos_agregados++;

			if (columna == 31) {
				this->columna = 1;
				this->fila++;
			}

			cola.pop();
		}

		std::cout << "Se han agregado: " << contador_vehiculos_agregados << " vehiculos " << std::endl;

	} else {
		std::cout << "El estacionamiento ya no tiene espacios para almacenar mas vehiculos" << std::endl;
	}
}

void Menu::desocupar_espacio(std::string patente){
	int* espacio_desocupado = this->matriz->eliminar_patente(patente);

	if (espacio_desocupado != nullptr) {
		espacios_desocupados.push(espacio_desocupado);
		std::cout << "Se desocupo un espacio en la posicion " << "Fila: " << espacio_desocupado[0] << " Columna: " << espacio_desocupado[1] << std::endl;
	}
}

void Menu::rellenar_espacios_desocupados(){

	int cant_aleatoria = 1 + (rand() % 100);
	int contador_vehiculos_agregados = 0;
	std::queue<Vehiculo*> cola;
	std::set<std::string> conjunto;

	if (this->matriz->esta_llena()) {
		cant_aleatoria = espacios_desocupados.size()-1;
	}

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
		} else {
			delete vehiculo;
		}
		cant_aleatoria--;
	}

	conjunto.clear();
	int auxFila = this->fila;
	int auxColumna = this->columna;

	while (!cola.empty()) {

		Vehiculo* vehiculo = cola.front();

		if (!espacios_desocupados.empty()) {

			int* espacio_a_ocupar = espacios_desocupados.top();
			this->fila = espacio_a_ocupar[0];
			this->columna = espacio_a_ocupar[1];
			this->matriz->agregar(vehiculo, this->fila, this->columna);
			contador_vehiculos_agregados++;
			cola.pop();
			espacios_desocupados.pop();

		} else {
			break;
		}
	}

	this->fila = auxFila;
	this->columna = auxColumna;

	while (!cola.empty() && !this->matriz->esta_llena()) {

		Vehiculo* vehiculo = cola.front();

		if ((this->fila % (2 + 3 * n) == 0)) {
			n++;
			this->fila++;
			this->columna = 1;
		}

		this->matriz->agregar(vehiculo, this->fila, this->columna++);
		contador_vehiculos_agregados++;

		if (columna == 31) {
			this->columna = 1;
			this->fila++;
		}

		cola.pop();
	}

	std::cout << "Se han agregado: " << contador_vehiculos_agregados << " vehiculos " << std::endl;
}

void Menu::ver_estacionamiento(){
	this->matriz->ver_estacionamiento();
}

void Menu::estadisticas()
{
}
