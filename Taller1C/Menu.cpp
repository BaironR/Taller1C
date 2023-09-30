#include "Menu.h"
#include <ctime> //Importar librería de tiempo.
#include <cstdlib> //Importar librería estándar.
#include <string> //Importar strings.
#include "Vehiculo.h"
#include <queue> //Importar filas/colas/queue.
#include <set> //Importar set (conjuntos).

/*
Implementación del menú principal del programa. Aquí se contiene toda la lógica fundamental
para el desarrollo de la aplicación. Contiene todos los métodos implementados: constructor del menú,
estacionamiento del(los) vehículo(s), desocupar espacio a partir de la patente, relleno de espacios
desocupados, visualización del estacionamiento, y obtención de estadísticas.
*/

/*
Constructor del menú.
Ejecuta el constructor de la matriz poco poblada.
*/
Menu::Menu(){
	this->matriz = new MPP();
}

void Menu::iniciar(){

	srand(time(nullptr)); //Semilla aleatoria: tiempo (nulo).

	//Ciclo while del menú principal.
	while (true) {

		do {
			//Bloque try que contiene el menú.
			try {

				//El usuario ingresa una opción (tipo string) que realiza la conversión a int luego.
				std::string opcion;
				std::cout <<
					"****************************************\n"
					"             Menu sistema PAL           \n"
					"****************************************\n"
					"[1] Estacionar vehiculo\n"
					"[2] Desocupar espacio\n"
					"[3] Visualizar estacionamiento\n"
					"[4] Ver estadisticas\n"
					"[5] Cerrar programa" << std::endl;

				std::cin >> opcion;

				//Conversión opción string -> int.
				int opcionInt = std::stoi(opcion);


				//Si el usuario ingresa 5, se termina el programa, eliminando los elementos contenidos en memoria.
				if (opcionInt == 5) {
					std::cout << "Programa finalizado, muchas gracias." << std::endl;
					delete this->matriz;
					return;
				}

				switch (opcionInt) {

				case(1):
					std::cout << "[1] Estacionar vehiculo(s)" << std::endl;
					//En caso de que se elija la opción 1 (estacionar vehículo), se comprueba si hay espacios
					//desocupados (pila vacía o no). En el caso de que la pila esté vacía se procede al método
					//estacionar vehículo. Si no está vacía, se ejecuta el método de rellenar espacios desocupados.
					if (espacios_desocupados.empty()) {
						estacionar_vehiculo();
					}
					else {
						rellenar_espacios_desocupados();
					}
					break;

				case(2):
				{
					std::cout << "[2] Desocupar espacio " << std::endl;
					//Opción 2: desocupar espacio.
					//Primeramente se pide al usuario ingresar la patente a eliminar.
					//Después se imprime la lista completa de las patentes de los autos estacionados (método de la matriz).
					//Al ingresar la patente, se ejecuta el método de desocupar espacio.

					std::cout << "Ingrese la patente que desea eliminar: " << std::endl;
					this->matriz->lista_patentes();
					std::string patente;
					std::cin >> patente;
					desocupar_espacio(patente);
					break;
				}

				case(3):
					std::cout << "[3] Visualizar estacionamiento " << std::endl;
					//Opción 3: visualizar estacionamiento. Se ejecuta el método que permite ver las posiciones
					//ocupadas y desocupadas.
					ver_estacionamiento();
					break;

				case(4):
					std::cout << "[4] Ver estadisticas " << std::endl;
					//Opción 4: obtener estadísticas. La matriz ejecuta su método de obtener estadísticas.
					estadisticas();
					break;

				default:
					//Opción default: cuando el usuario ingrese un número que no esté en el rango
					//de 1 y 5. Despliega un mensaje de error.
					std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
					std::cout << std::endl;
					break;
				}

			}
			catch (const std::invalid_argument& e) {
				//Captura de excepción (argumento inválido).
				//Se captura una excepción producida por la conversión fallida de string a int
				//(El usuario ingresa un caracter no numérico).
				std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;

			}
			catch (const std::out_of_range& e) {
				//Captura de excepción (fuera de rango).
				//Se captura una excepción debido a un desbordamiento (el usuario ingresa un número entero muy grande).
				std::cerr << "Excepcion de tipo std::out_of_range: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
			}
		}while(true);
	}
	//Eliminar la matriz al terminar el programa.
	delete matriz;
}


/*
Estacionar vehículo.
Este método realiza todo el procedimiento necesario para, la creación de vehículos (generación de patentes
y tipos aleatorios), obtener el ticket de estacionamiento (posicionar los vehículos en la queue), y el proceso
de estacionar. Primero se comprueba que la matriz no esté vacía. Si es así, entonces se pueden estacionar vehículos.
La cantidad aleatoria de vehículos a estacionar va desde el 1 hasta el 100 (de manera aleatoria, usando la función
rand() ). Se inicializa otro contador en 0, la queue para estacionarlos, y un set o conjunto de strings (este último
permite que las patentes generadas no se repitan, a pesar de que la probabilidad sea muy baja). Mientras la cantidad restante de autos a estacionar no sea 0, 
se generan y colocan en la queue los vehículos.
Se inicializa un vector de strings que posee los 4 tipos de vehículos (auto, furgoneta, camioneta y moto), junto
a un puntero, así como a un vector de booleanos true y false si el auto está tuneado o no, con un puntero. Para el tipo de vehículo
se aplica de nuevo la función random, pero para obtener el tipo del vehículo con el puntero al vector de tipos y el booleano de tuneado. 
Para la creación aleatoria de patente, se usa de nuevo la función rand(), y se
concatena 4 veces un caracter entre la A y la Z (el caracter A sumado a un número entre 0 y 25, para "desplazarse"
entre los caracteres respetando el código ASCII). Lo mismo aplica para los otros 2 números entre 0 y 9 (rand() desde 0 hasta 9).
Después, se inicializa el vehículo con su respectivo constructor (patente y tipo).

Para evitar repeticiones de vehículos, se usa el conjunto (set), ya que cada elemento ahí es único por el valor que
lo identifica. Para realizar búsquedas de valores en el set, se pueden usar los métodos begin(), find(), end(). Los
3 métodos retornan iteradores a elementos pertenecientes al conjunto, pero begin() retorna el iterador del primer
elemento, find() del elemento que se pase como parámetro, y end() del elemento que continúa al último. La comprobación
se realiza así: si el iterador que se retorna al encontrar la patente es igual a la del siguiente del último del conjunto,
(es decir, la patente no existe en el conjunto), entonces el vehículo avanza a la queue, y la patente se inserta en el set.
En caso contrario (o sea, si la patente ya existe en el conjunto, debido a que el iterador que se retorna no es igual a la del
siguiente del último), se destruye el vehículo. Por cada iteración, la cantidad aleatoria de vehículos se disminuye en 1, hasta que
termine en 0. Después de eso, el conjunto se vacía.

Mientras la cola no esté vacía y la matriz no esté llena (que hayan autos a estacionar y que haya espacios), se realiza
la inserción de los vehículos en el estacionamiento. La forma de estacionar en este caso, será de fila en fila, hasta
rellenar todas las columnas para avanzar a la próxima fila estacionable. La fórmula matemática que involucra la fila actual
y n, permite saltarse las filas en las que no se puede estacionar. Por esa razón n se inicializa a 0. Si la división entre
la fila actual (fila) y (2 + 3 * n) es igual a 0, es porque no se puede estacionar en esa fila, y en ese caso se aumenta el valor
de n y la fila, así como también el valor de la columna se reinicia a 1 para poder seguir estacionar en la misma fila hasta terminar.

Luego, se llama la función agregar por parte de la matriz, y el contador de vehículos agregados se incrementa en 1. Cuando el valor
de la columna actual es 31, significa que ya se llenó la fila, y por esa razón aumenta el número de fila en 1, y la columna se
reinicia a 1. Como el vehículo ya se agregó, se hace pop al vehículo presente en el frente de la cola. Todo este ciclo se repite
hasta que se llene la matriz o que se vacíe la cola (sin más autos para estacionar). Se imprime la cantidad ingresada de autos al estacionamiento.
En caso de que la matriz ya esté llena, se imprime un mensaje de error advirtiendo que ya no hay más espacio para almacenar los vehículos.


*/


void Menu::estacionar_vehiculo(){
	
	if (!this->matriz->esta_llena()) { //Si la matríz no está llena, se procede a crear los vehículos.
		int cant_aleatoria = 1 + (rand() % 100); //Cantidad aleatoria (1-100).
		int contador_vehiculos_agregados = 0; //Contador de vehículos.
		std::queue<Vehiculo*> cola; //Queue de vehículos a estacionar.
		std::set<std::string> conjunto; //Set de patentes.

		//Mientras la cantidad aleatoria no sea 0, se crean vehículos.


		while (cant_aleatoria != 0) {

			std::string tipos[] = { "Auto", "Camioneta","Furgoneta","Moto" };
			std::string* punt_tipo = &tipos[0];

			//Tipo aleatorio.
			std::string tipo = *(punt_tipo += (rand() % 4));


			bool tuneados[] = { true, false };
			bool* punt_esta_tuneado = &tuneados[0];

			//Tuneado aleatorio.
			bool esta_tuneado = *(punt_esta_tuneado += (rand() % 2));
			std::string patente;


			//Generar patente aleatoria.
			for (int i = 0; i < 4; ++i) {
				patente += 'A' + (rand() % 26);
			}

			for (int i = 0; i < 2; ++i) {
				patente += '0' + (rand() % 10);
			}


			Vehiculo* vehiculo = new Vehiculo(patente, tipo, esta_tuneado);


			//Conseguir ticket de estacionamiento.
			//Si la patente no existe en el conjunto, la patente se añade al conjunto, 
			//y el vehículo se agrega a la queue.

			if (conjunto.find(vehiculo->get_patente()) == conjunto.end()) {
				cola.push(vehiculo);
				conjunto.insert(patente);

			}
			else {
				//Eliminar vehículo si la patente ya existe.
				delete vehiculo;
			}

			//Cantidad aleatoria menos 1.
			cant_aleatoria--;


		}



		//Se vacía el conjunto.
		conjunto.clear();

		//Mientras la cola no esté vacía y la matriz no esté llena, se procede a estacionar los vehículos
		//de la queue.

		while (!cola.empty() && !this->matriz->esta_llena()) {

			Vehiculo* vehiculo = cola.front();

			//Esta fórmula matemática permite identificar las filas en las que no se puede estacionar.
			//Si la fila actual es divisible por 2 + 3n, entonces no se puede estacionar.
			//Al comienzo, n vale 0. Cuando se procede a la fila 2, por ejemplo, no se puede estacionar.
			//Cuando se alcanza una fila que no se puede estacionar, el valor de n y la fila aumentan en 1,
			//y el valor de la columna se reinicia en 1 ya que se completó la fila anterior.

			if ((this->fila % (2 + 3 * n) == 0)) {
				n++;
				this->fila++;
				this->columna = 1;
			}

			//El vehículo se agrega a la matriz, con su vehículo y valores de fila y columna.


			this->matriz->agregar(vehiculo, fila, columna++);
			contador_vehiculos_agregados++; //Vehículos agregados más 1.

			//Si la columna actual es 31, significa que se completó la fila con 30 autos.
			//Se reinicia el valor a 1, y se avanza a la siguiente fila.
			if (columna == 31) {
				this->columna = 1;
				this->fila++;
			}

			//Se elimina el vehículo ya estacionado de la queue.
			cola.pop();
		}

		//Imprimir información de cantidad de autos.
		std::cout << "Se han agregado: " << contador_vehiculos_agregados << " vehiculos " << std::endl;

	} else {
		std::cout << "El estacionamiento ya no tiene espacios para almacenar mas vehiculos" << std::endl;
	}
}

/*
Desocupar espacio del estacionamiento, a partir de la patente.
A partir de la patente ingresada por el usuario, se llama al método de la matriz para eliminar el vehículo
(retornando un vector con el espacio desocupado de la columna y fila). Si el espacio desocupado no es nulo, entonces
se agrega a la pila de espacios desocupados, y se despliega un mensaje notificando esta liberación. Si es nulo, es porque
la patente no se encontró.
*/
void Menu::desocupar_espacio(std::string patente) {
	//Se retorna un vector con el valor de la fila y la columna, a partir de la patente.
	int* espacio_desocupado = this->matriz->eliminar_patente(patente);

	//Si no es nulo, es porque hay un espacio desocupado y existe la patente en la matriz poco poblada.
	if (espacio_desocupado != nullptr) {
		espacios_desocupados.push(espacio_desocupado);
		std::cout << "Se desocupo un espacio en la posicion " << "Fila: " << espacio_desocupado[0] << " Columna: " << espacio_desocupado[1] << std::endl;
	}
	else {
		std::cout << "Error: no se pudo eliminar el vehiculo porque no existe. Intente de nuevo. " << std::endl;
	}
}


/*
Rellenar espacios desocupados.
En este método, valga la redundancia, se rellenan los espacios desocupados a partir de una cantidad aleatoria.
Si la matriz está llena (sin espacios disponibles), la cantidad aleatoria se reduce al tamaño de espacios
desocupados menos 1 (-1 o 0). La generación de vehículos se produce de la misma forma que en estacionar_vehiculo(),
y la correspondiente inserción a la queue. Se inicializan variables auxiliares de fila y columna, con los valores
de fila y columna actuales, para no perderlos. La inserción a los espacios desocupados se realiza hasta que la queue
esté vacía o que la pila de espacios desocupados. Un vector de enteros con el espacio, se retorna desde el tope de la
pila, y el valor de fila y columna actuales se actualizan a partir del vector retornado. Luego, se llama la función
de la matriz de agregar el nodo, con el vehículo, fila actual y columna actual como parámetros. El contador de vehículos
agregados se incrementa en 1, y se hacen pop (eliminar) el vehículo de la queue, con el vector en el tope de la pila de
espacios desocupados. Cuando la pila de espacios desocupados se desocupe, se hace break. Puede suceder que la cola no se
vacíe antes de que la pila lo haga.

Cabe destacar que la pila de espacios desocupados es para aquellos espacios que están antes de la posición actual en
el cual se estaba al momento de rellenar. Luego de que se acabe la pila de espacios desocupados, significa que ya se puede
regresar al espacio actual.

Luego, se restaura los valores de fila y columna actuales con los auxiliares. Mientras la cola no esté vacía o la matriz
no esté llena, se continúa rellenando desde la posición en el que estaba. Se realiza el mismo procedimiento que en el método
de estacionar_vehiculo(). Y finalmente, se imprime la cantidad agregada de vehículos.
*/

void Menu::rellenar_espacios_desocupados(){

	int cant_aleatoria = 1 + (rand() % 100);
	int contador_vehiculos_agregados = 0;
	std::queue<Vehiculo*> cola;
	std::set<std::string> conjunto;

	if (this->matriz->esta_llena()) {
		cant_aleatoria = espacios_desocupados.size()-1;
	}

	//La creación de autos se produce de la misma forma que en el método de estacionar_vehiculo().

	while (cant_aleatoria != 0) {

		std::string tipos[] = { "Auto", "Camioneta","Furgoneta","Moto" };
		std::string* punt_tipo = &tipos[0];
		std::string tipo = *(punt_tipo += (rand() % 4));
		bool tuneados[] = { true, false };
		bool* punt_esta_tuneado = &tuneados[0];
		bool esta_tuneado = *(punt_esta_tuneado += (rand() % 2));
		std::string patente;

		for (int i = 0; i < 4; ++i) {
			patente += 'A' + (rand() % 26);
		}

		for (int i = 0; i < 2; ++i) {
			patente += '0' + (rand() % 10);
		}

		Vehiculo* vehiculo = new Vehiculo(patente, tipo, esta_tuneado);

		if (conjunto.find(vehiculo->get_patente()) == conjunto.end()) {
			cola.push(vehiculo);
			conjunto.insert(patente);
		} else {
			delete vehiculo;
		}
		cant_aleatoria--;
	}

	conjunto.clear();

	//Se guardan los valores de fila y columna actual, en auxiliares.

	int auxFila = this->fila;
	int auxColumna = this->columna;

	//Mientras hayan vehículos a estacionar, se agregan a los espacios desocupados que están
	//antes de la posición actual.
	while (!cola.empty()) {

		Vehiculo* vehiculo = cola.front();

		if (!espacios_desocupados.empty()) {

			//El tope de la pila de espacios desocupados es almacenado por un puntero de enteros.
			int* espacio_a_ocupar = espacios_desocupados.top();

			//Los valores de fila y columna se actualizan con los valores del vector extraído de la pila.
			this->fila = espacio_a_ocupar[0];
			this->columna = espacio_a_ocupar[1];

			//Se agrega el vehículo a la matriz.
			this->matriz->agregar(vehiculo, this->fila, this->columna);
			contador_vehiculos_agregados++;

			//Eliminación del último auto y las coordenadas del último espacio desocupado.
			cola.pop();
			espacios_desocupados.pop();
		} else {
			break;
		}
	}

	//Los valores de fila y columna en el que se estaban antes de rellenar los espacios vacíos, 
	//se recuperan gracias a los auxiliares.
	this->fila = auxFila;
	this->columna = auxColumna;

	//La inserción de los vehículos en la matriz se realiza igualmente que en el método estacionar_vehiculo().

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
	//Despliegue de información de la cantidad de vehículos estacionados.
	std::cout << "Se han agregado: " << contador_vehiculos_agregados << " vehiculos " << std::endl;
}

/*
Ver estacionamiento.
Solamente se ejecuta el método de la matriz para imprimir el estacionamiento.
*/
void Menu::ver_estacionamiento(){
	std::cout << "'A' representan los espacios ocupados por vehiculos. " << std::endl;
	std::cout << "'.' representan los espacios desocupados. " << std::endl;
	std::cout << "'+' representan los espacios no estacionables. " << std::endl;
	std::cout << std::endl;
	this->matriz->ver_estacionamiento();
}

/*
Ver estadísticas. 
Se ejecuta el método de la matriz para imprimir estadísticas respecto a los vehículos estacionados.
*/
void Menu::estadisticas(){
	this->matriz->ver_estadisticas();
}
