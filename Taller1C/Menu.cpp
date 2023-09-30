#include "Menu.h"
#include <ctime> //Importar librer�a de tiempo.
#include <cstdlib> //Importar librer�a est�ndar.
#include <string> //Importar strings.
#include "Vehiculo.h"
#include <queue> //Importar filas/colas/queue.
#include <set> //Importar set (conjuntos).

/*
Implementaci�n del men� principal del programa. Aqu� se contiene toda la l�gica fundamental
para el desarrollo de la aplicaci�n. Contiene todos los m�todos implementados: constructor del men�,
estacionamiento del(los) veh�culo(s), desocupar espacio a partir de la patente, relleno de espacios
desocupados, visualizaci�n del estacionamiento, y obtenci�n de estad�sticas.
*/

/*
Constructor del men�.
Ejecuta el constructor de la matriz poco poblada.
*/
Menu::Menu(){
	this->matriz = new MPP();
}

void Menu::iniciar(){

	srand(time(nullptr)); //Semilla aleatoria: tiempo (nulo).

	//Ciclo while del men� principal.
	while (true) {

		do {
			//Bloque try que contiene el men�.
			try {

				//El usuario ingresa una opci�n (tipo string) que realiza la conversi�n a int luego.
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

				//Conversi�n opci�n string -> int.
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
					//En caso de que se elija la opci�n 1 (estacionar veh�culo), se comprueba si hay espacios
					//desocupados (pila vac�a o no). En el caso de que la pila est� vac�a se procede al m�todo
					//estacionar veh�culo. Si no est� vac�a, se ejecuta el m�todo de rellenar espacios desocupados.
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
					//Opci�n 2: desocupar espacio.
					//Primeramente se pide al usuario ingresar la patente a eliminar.
					//Despu�s se imprime la lista completa de las patentes de los autos estacionados (m�todo de la matriz).
					//Al ingresar la patente, se ejecuta el m�todo de desocupar espacio.

					std::cout << "Ingrese la patente que desea eliminar: " << std::endl;
					this->matriz->lista_patentes();
					std::string patente;
					std::cin >> patente;
					desocupar_espacio(patente);
					break;
				}

				case(3):
					std::cout << "[3] Visualizar estacionamiento " << std::endl;
					//Opci�n 3: visualizar estacionamiento. Se ejecuta el m�todo que permite ver las posiciones
					//ocupadas y desocupadas.
					ver_estacionamiento();
					break;

				case(4):
					std::cout << "[4] Ver estadisticas " << std::endl;
					//Opci�n 4: obtener estad�sticas. La matriz ejecuta su m�todo de obtener estad�sticas.
					estadisticas();
					break;

				default:
					//Opci�n default: cuando el usuario ingrese un n�mero que no est� en el rango
					//de 1 y 5. Despliega un mensaje de error.
					std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
					std::cout << std::endl;
					break;
				}

			}
			catch (const std::invalid_argument& e) {
				//Captura de excepci�n (argumento inv�lido).
				//Se captura una excepci�n producida por la conversi�n fallida de string a int
				//(El usuario ingresa un caracter no num�rico).
				std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;

			}
			catch (const std::out_of_range& e) {
				//Captura de excepci�n (fuera de rango).
				//Se captura una excepci�n debido a un desbordamiento (el usuario ingresa un n�mero entero muy grande).
				std::cerr << "Excepcion de tipo std::out_of_range: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
			}
		}while(true);
	}
	//Eliminar la matriz al terminar el programa.
	delete matriz;
}


/*
Estacionar veh�culo.
Este m�todo realiza todo el procedimiento necesario para, la creaci�n de veh�culos (generaci�n de patentes
y tipos aleatorios), obtener el ticket de estacionamiento (posicionar los veh�culos en la queue), y el proceso
de estacionar. Primero se comprueba que la matriz no est� vac�a. Si es as�, entonces se pueden estacionar veh�culos.
La cantidad aleatoria de veh�culos a estacionar va desde el 1 hasta el 100 (de manera aleatoria, usando la funci�n
rand() ). Se inicializa otro contador en 0, la queue para estacionarlos, y un set o conjunto de strings (este �ltimo
permite que las patentes generadas no se repitan, a pesar de que la probabilidad sea muy baja). Mientras la cantidad restante de autos a estacionar no sea 0, 
se generan y colocan en la queue los veh�culos.
Se inicializa un vector de strings que posee los 4 tipos de veh�culos (auto, furgoneta, camioneta y moto), junto
a un puntero, as� como a un vector de booleanos true y false si el auto est� tuneado o no, con un puntero. Para el tipo de veh�culo
se aplica de nuevo la funci�n random, pero para obtener el tipo del veh�culo con el puntero al vector de tipos y el booleano de tuneado. 
Para la creaci�n aleatoria de patente, se usa de nuevo la funci�n rand(), y se
concatena 4 veces un caracter entre la A y la Z (el caracter A sumado a un n�mero entre 0 y 25, para "desplazarse"
entre los caracteres respetando el c�digo ASCII). Lo mismo aplica para los otros 2 n�meros entre 0 y 9 (rand() desde 0 hasta 9).
Despu�s, se inicializa el veh�culo con su respectivo constructor (patente y tipo).

Para evitar repeticiones de veh�culos, se usa el conjunto (set), ya que cada elemento ah� es �nico por el valor que
lo identifica. Para realizar b�squedas de valores en el set, se pueden usar los m�todos begin(), find(), end(). Los
3 m�todos retornan iteradores a elementos pertenecientes al conjunto, pero begin() retorna el iterador del primer
elemento, find() del elemento que se pase como par�metro, y end() del elemento que contin�a al �ltimo. La comprobaci�n
se realiza as�: si el iterador que se retorna al encontrar la patente es igual a la del siguiente del �ltimo del conjunto,
(es decir, la patente no existe en el conjunto), entonces el veh�culo avanza a la queue, y la patente se inserta en el set.
En caso contrario (o sea, si la patente ya existe en el conjunto, debido a que el iterador que se retorna no es igual a la del
siguiente del �ltimo), se destruye el veh�culo. Por cada iteraci�n, la cantidad aleatoria de veh�culos se disminuye en 1, hasta que
termine en 0. Despu�s de eso, el conjunto se vac�a.

Mientras la cola no est� vac�a y la matriz no est� llena (que hayan autos a estacionar y que haya espacios), se realiza
la inserci�n de los veh�culos en el estacionamiento. La forma de estacionar en este caso, ser� de fila en fila, hasta
rellenar todas las columnas para avanzar a la pr�xima fila estacionable. La f�rmula matem�tica que involucra la fila actual
y n, permite saltarse las filas en las que no se puede estacionar. Por esa raz�n n se inicializa a 0. Si la divisi�n entre
la fila actual (fila) y (2 + 3 * n) es igual a 0, es porque no se puede estacionar en esa fila, y en ese caso se aumenta el valor
de n y la fila, as� como tambi�n el valor de la columna se reinicia a 1 para poder seguir estacionar en la misma fila hasta terminar.

Luego, se llama la funci�n agregar por parte de la matriz, y el contador de veh�culos agregados se incrementa en 1. Cuando el valor
de la columna actual es 31, significa que ya se llen� la fila, y por esa raz�n aumenta el n�mero de fila en 1, y la columna se
reinicia a 1. Como el veh�culo ya se agreg�, se hace pop al veh�culo presente en el frente de la cola. Todo este ciclo se repite
hasta que se llene la matriz o que se vac�e la cola (sin m�s autos para estacionar). Se imprime la cantidad ingresada de autos al estacionamiento.
En caso de que la matriz ya est� llena, se imprime un mensaje de error advirtiendo que ya no hay m�s espacio para almacenar los veh�culos.


*/


void Menu::estacionar_vehiculo(){
	
	if (!this->matriz->esta_llena()) { //Si la matr�z no est� llena, se procede a crear los veh�culos.
		int cant_aleatoria = 1 + (rand() % 100); //Cantidad aleatoria (1-100).
		int contador_vehiculos_agregados = 0; //Contador de veh�culos.
		std::queue<Vehiculo*> cola; //Queue de veh�culos a estacionar.
		std::set<std::string> conjunto; //Set de patentes.

		//Mientras la cantidad aleatoria no sea 0, se crean veh�culos.


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
			//Si la patente no existe en el conjunto, la patente se a�ade al conjunto, 
			//y el veh�culo se agrega a la queue.

			if (conjunto.find(vehiculo->get_patente()) == conjunto.end()) {
				cola.push(vehiculo);
				conjunto.insert(patente);

			}
			else {
				//Eliminar veh�culo si la patente ya existe.
				delete vehiculo;
			}

			//Cantidad aleatoria menos 1.
			cant_aleatoria--;


		}



		//Se vac�a el conjunto.
		conjunto.clear();

		//Mientras la cola no est� vac�a y la matriz no est� llena, se procede a estacionar los veh�culos
		//de la queue.

		while (!cola.empty() && !this->matriz->esta_llena()) {

			Vehiculo* vehiculo = cola.front();

			//Esta f�rmula matem�tica permite identificar las filas en las que no se puede estacionar.
			//Si la fila actual es divisible por 2 + 3n, entonces no se puede estacionar.
			//Al comienzo, n vale 0. Cuando se procede a la fila 2, por ejemplo, no se puede estacionar.
			//Cuando se alcanza una fila que no se puede estacionar, el valor de n y la fila aumentan en 1,
			//y el valor de la columna se reinicia en 1 ya que se complet� la fila anterior.

			if ((this->fila % (2 + 3 * n) == 0)) {
				n++;
				this->fila++;
				this->columna = 1;
			}

			//El veh�culo se agrega a la matriz, con su veh�culo y valores de fila y columna.


			this->matriz->agregar(vehiculo, fila, columna++);
			contador_vehiculos_agregados++; //Veh�culos agregados m�s 1.

			//Si la columna actual es 31, significa que se complet� la fila con 30 autos.
			//Se reinicia el valor a 1, y se avanza a la siguiente fila.
			if (columna == 31) {
				this->columna = 1;
				this->fila++;
			}

			//Se elimina el veh�culo ya estacionado de la queue.
			cola.pop();
		}

		//Imprimir informaci�n de cantidad de autos.
		std::cout << "Se han agregado: " << contador_vehiculos_agregados << " vehiculos " << std::endl;

	} else {
		std::cout << "El estacionamiento ya no tiene espacios para almacenar mas vehiculos" << std::endl;
	}
}

/*
Desocupar espacio del estacionamiento, a partir de la patente.
A partir de la patente ingresada por el usuario, se llama al m�todo de la matriz para eliminar el veh�culo
(retornando un vector con el espacio desocupado de la columna y fila). Si el espacio desocupado no es nulo, entonces
se agrega a la pila de espacios desocupados, y se despliega un mensaje notificando esta liberaci�n. Si es nulo, es porque
la patente no se encontr�.
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
En este m�todo, valga la redundancia, se rellenan los espacios desocupados a partir de una cantidad aleatoria.
Si la matriz est� llena (sin espacios disponibles), la cantidad aleatoria se reduce al tama�o de espacios
desocupados menos 1 (-1 o 0). La generaci�n de veh�culos se produce de la misma forma que en estacionar_vehiculo(),
y la correspondiente inserci�n a la queue. Se inicializan variables auxiliares de fila y columna, con los valores
de fila y columna actuales, para no perderlos. La inserci�n a los espacios desocupados se realiza hasta que la queue
est� vac�a o que la pila de espacios desocupados. Un vector de enteros con el espacio, se retorna desde el tope de la
pila, y el valor de fila y columna actuales se actualizan a partir del vector retornado. Luego, se llama la funci�n
de la matriz de agregar el nodo, con el veh�culo, fila actual y columna actual como par�metros. El contador de veh�culos
agregados se incrementa en 1, y se hacen pop (eliminar) el veh�culo de la queue, con el vector en el tope de la pila de
espacios desocupados. Cuando la pila de espacios desocupados se desocupe, se hace break. Puede suceder que la cola no se
vac�e antes de que la pila lo haga.

Cabe destacar que la pila de espacios desocupados es para aquellos espacios que est�n antes de la posici�n actual en
el cual se estaba al momento de rellenar. Luego de que se acabe la pila de espacios desocupados, significa que ya se puede
regresar al espacio actual.

Luego, se restaura los valores de fila y columna actuales con los auxiliares. Mientras la cola no est� vac�a o la matriz
no est� llena, se contin�a rellenando desde la posici�n en el que estaba. Se realiza el mismo procedimiento que en el m�todo
de estacionar_vehiculo(). Y finalmente, se imprime la cantidad agregada de veh�culos.
*/

void Menu::rellenar_espacios_desocupados(){

	int cant_aleatoria = 1 + (rand() % 100);
	int contador_vehiculos_agregados = 0;
	std::queue<Vehiculo*> cola;
	std::set<std::string> conjunto;

	if (this->matriz->esta_llena()) {
		cant_aleatoria = espacios_desocupados.size()-1;
	}

	//La creaci�n de autos se produce de la misma forma que en el m�todo de estacionar_vehiculo().

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

	//Mientras hayan veh�culos a estacionar, se agregan a los espacios desocupados que est�n
	//antes de la posici�n actual.
	while (!cola.empty()) {

		Vehiculo* vehiculo = cola.front();

		if (!espacios_desocupados.empty()) {

			//El tope de la pila de espacios desocupados es almacenado por un puntero de enteros.
			int* espacio_a_ocupar = espacios_desocupados.top();

			//Los valores de fila y columna se actualizan con los valores del vector extra�do de la pila.
			this->fila = espacio_a_ocupar[0];
			this->columna = espacio_a_ocupar[1];

			//Se agrega el veh�culo a la matriz.
			this->matriz->agregar(vehiculo, this->fila, this->columna);
			contador_vehiculos_agregados++;

			//Eliminaci�n del �ltimo auto y las coordenadas del �ltimo espacio desocupado.
			cola.pop();
			espacios_desocupados.pop();
		} else {
			break;
		}
	}

	//Los valores de fila y columna en el que se estaban antes de rellenar los espacios vac�os, 
	//se recuperan gracias a los auxiliares.
	this->fila = auxFila;
	this->columna = auxColumna;

	//La inserci�n de los veh�culos en la matriz se realiza igualmente que en el m�todo estacionar_vehiculo().

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
	//Despliegue de informaci�n de la cantidad de veh�culos estacionados.
	std::cout << "Se han agregado: " << contador_vehiculos_agregados << " vehiculos " << std::endl;
}

/*
Ver estacionamiento.
Solamente se ejecuta el m�todo de la matriz para imprimir el estacionamiento.
*/
void Menu::ver_estacionamiento(){
	std::cout << "'A' representan los espacios ocupados por vehiculos. " << std::endl;
	std::cout << "'.' representan los espacios desocupados. " << std::endl;
	std::cout << "'+' representan los espacios no estacionables. " << std::endl;
	std::cout << std::endl;
	this->matriz->ver_estacionamiento();
}

/*
Ver estad�sticas. 
Se ejecuta el m�todo de la matriz para imprimir estad�sticas respecto a los veh�culos estacionados.
*/
void Menu::estadisticas(){
	this->matriz->ver_estadisticas();
}
