#include "MPP.h"

/*
Constructor de la matriz poco poblada.
Se inicializa primeramente, insertando un objeto nulo a los vectores que representan las columnas y filas (haciendo
referencia a la columna y fila 0, en el que no debe haber nada ya que acá están los nodos). Luego en un ciclo for,
se inicializan nodos para las columnas y filas, con sus respectivos valores en 0 (fila 0 para las columnas, columna 0
para las filas). Después se agregan a cada vector, y se referencian a sí mismos (los de las filas, como su nodo izquierdo, 
y los de las columnas, como su nodo superior).
*/
MPP::MPP(){

	//Primer elemento NULL (fila/columna 0).
	columnas.push_back(NULL);
	filas.push_back(NULL);


	//Ciclo for desde casilla 1 al 30, inicializando nodos.
	for (int i = 1; i <= 30; i++) {
		NodoMPP* cabezaColumna = new NodoMPP(NULL,0,NULL); //Nodo cabeza de columna.
		NodoMPP* cabezaFila = new NodoMPP(NULL, NULL, 0); //Nodo cabeza de fila
		columnas.push_back(cabezaColumna); 
		filas.push_back(cabezaFila);
		cabezaColumna->set_superior(cabezaColumna); //Referencias a sí mismos (superior-columna, izquierda-fila).
		cabezaFila->set_izquierdo(cabezaFila);
	}
}

/*
Agregar a fila.
Se agrega el nuevo nodo a la fila.
Primeramente, se revisa el nodo cabeza de la fila se referencia a sí mismo (la fila está vacía).
En ese caso, se agrega a la fila (izquierda del nuevo nodo es la cabeza, izquierda de la cabeza es el nuevo nodo).
En caso contrario, se itera a través de la fila, mediante un nodo actual y anterior.
Mientras el actual no sea la cabecera se itera el actual y el anterior.
Finalmente, el izquierdo del nuevo nodo será el actual, y el izquierdo del anterior es el nuevo nodo.
*/
void MPP::agregar_a_fila(NodoMPP* nodo, int fila) {

	//Si la fila está vacía.
	if (filas[fila]->get_izquierdo() == filas[fila]) {
		nodo->set_izquierdo(filas[fila]);
		filas[fila]->set_izquierdo(nodo);
		return;
	}

	NodoMPP* actual2 = filas[fila]->get_izquierdo();
	NodoMPP* anterior2 = filas[fila];


	while (actual2 != filas[fila] && actual2->get_fila() < fila) {
		//Iteración.
		anterior2 = actual2;
		actual2 = actual2->get_izquierdo();
	}

	//Referencias entre actual y anterior.
	nodo->set_izquierdo(actual2);
	anterior2->set_izquierdo(nodo);
}

/*
Agregar a columna. 
Se realiza el mismo procedimiento que en agregar a fila, pero esta vez con una columna especificada.
En primer lugar se comprueba si la columna está vacía, si es así se agrega el nodo con su referencia superior a 
la cabeza. Mediante el nodo actual y el nodo superior, se itera por la columna, para poder referenciar al nuevo nodo 
y agregarlo a la matriz.
*/
void MPP::agregar_a_columna(NodoMPP* nodo, int columna) {

	//Si la columna está vacía.
	if (columnas[columna]->get_superior() == columnas[columna]) {
		nodo->set_superior(columnas[columna]);
		columnas[columna]->set_superior(nodo);
		return;
	}

	NodoMPP* actual1 = columnas[columna]->get_superior();
	NodoMPP* anterior1 = columnas[columna];

	while (actual1 != columnas[columna] && actual1->get_columna() < columna) {
		//Iteración de nodos.
		anterior1 = actual1;
		actual1 = actual1->get_superior();
	}

	//Referencias al y del nuevo nodo.
	nodo->set_superior(actual1);
	anterior1->set_superior(nodo);
}

/*
Agregar vehículo a la matriz.
En primer lugar se comprueba si el número de fila y columna es válido (mayor a 0 e igual o menor a 30).
En ese caso, se crea el nuevo nodo que almacena el vehículo, y se llama a los métodos de agregar en fila
y agregar en columna.
*/
void MPP::agregar(Vehiculo* vehiculo, int fila, int columna){


	//Se agrega si los valores fila y columna son mayores a 0 o, iguales o menores a 30.
	if (fila > 0 && fila <= 30 && columna > 0 && columna <= 30) {

		//Nuevo nodo.
		NodoMPP* nodo = new NodoMPP(vehiculo, fila, columna);
		agregar_a_fila(nodo, fila); //Agregar a fila.
		agregar_a_columna(nodo, columna); //Agregar a columna.
	}
}

/*
Ver estacionamiento.
En este método se imprime el estacionamiento, indicando los espacios ocupados y desocupados, reflejados
en la estructura actual de la matriz. Se va recorriendo por filas, iterando entre las columnas. Se llama al
método de obtener vehículo (con la fila y columna actuales). En caso que el método no retorne null (o sea, que
un vehículo existe en esa posición), se imprime una 'A'. En caso contrario, un punto para los espacios desocupados.
Por cada fila se salta una línea.
*/
void MPP::ver_estacionamiento(){

	int filas_estacionables[] = {1,3,4,6,7,9,10,12,13,15,16,18,19,21,22,24,25,27,28,30};
	int* puntero_estacionables = &filas_estacionables[0];

	for (int fila = 1; fila <= 30; fila++) {

		bool estacionable = false;

		for (int i = 0; i < 20; i++){
			if (fila == filas_estacionables[i]) {
				estacionable = true;
			}

			if (filas_estacionables[i] > fila) {
				break;
			}
		}

		for (int columna = 1; columna <= 30; columna++) {
			if (estacionable) {
				Vehiculo* vehiculo = obtener_vehiculo(fila, columna);
				if (vehiculo != nullptr) {
					//Si existe un vehículo con cierta fila y columna, se imprime una "A ".
					std::cout << "A ";
				}
				else {
					std::cout << ". "; // Agrega espacios para alinear las columnas
				}
			}
			else {
				std::cout << "+ ";
			}
		}
		std::cout << std::endl; // Cambia de línea después de cada fila
	}
}

/*
Obtener vehículo.
Permite obtener un vehículo a partir del valor de fila y columna especificado.
En este caso, para conseguir el vehículo se recorre por cada fila.

Se inicializa un nodo auxiliar en el último nodo de la fila, de la columna más lejana (el izquierdo
de la cabecera). Mientras el auxiliar no sea la cabecera, se recorre la fila a través de cada columna,
buscando un nodo que coincida con el valor de la columna. En caso contrario, se retorna nullptr.
*/
Vehiculo* MPP::obtener_vehiculo(int fila, int columna){

	NodoMPP* aux = filas[fila]->get_izquierdo();

	while (aux != filas[fila]) {
		//Mientras el nodo auxiliar no sea la cabecera, se itera por la fila.
		//Si en la fila existe un vehículo que coincida con la fila y columna, se retorna.
		if (aux->get_columna() == columna) {
			return aux->get_vehiculo();
		}
		aux = aux->get_izquierdo();
	}
	//Nullptr si no existe.
	return nullptr;
}

/*
Eliminar patente de vehículo en específico.
Se inicializa un puntero en un arreglo de 2 espacios, que consisten en las coordenadas del vehículo eliminado.
Luego, por cada fila se recorre para encontrar.
Si los valores del arreglo poseen valores mayores a 0, se retorna el puntero que apunta al arreglo.
En caso contrario, nullptr.
*/
int* MPP::eliminar_patente(std::string patente){

	//Puntero a arreglo con las coordenadas del auto eliminado.
	int* arreglo = new int[2];

	//Iterar por filas para recorrer la matriz, y encontrar al vehículo a eliminar.
	for (int i = 1; i <= 30; i++) {
		//Se ejecuta el método de eliminar de fila, enviando la patente, el puntero y el valor de fila actual.
		eliminar_de_fila(patente, arreglo, i);
		if (arreglo[0] != 0) {
			break;
		}
	}

	//En caso que la fila no sea 0 (se desocupó un espacio), se procede a eliminar el nodo de la columna.
	if (arreglo[0] != 0) {
		eliminar_de_columna(patente, arreglo, arreglo[1]);
	}


	//Se retorna el puntero si las coordenadas son mayores a 0. Es decir, que el auto existe 
	//y se desocupó un espacio.

	if (arreglo[0] > 0 && arreglo[1] > 0) {
		return arreglo;
	}

	//Nullptr si no se pudo eliminar el auto.
	return nullptr;
}

/*
Eliminar de fila.
A partir de la fila especificada, se realiza el procedimiento de eliminación de fila.
Se tiene un nodo "actual" y "anterior", que permiten iterar para encontrar el vehículo a eliminar.
Mientras el actual no sea el nodo cabecera, se recorre la fila. Si el actual corresponde al vehículo
(ya que coincide su patente), entonces se designa al siguiente del anterior como el siguiente del actual, 
y se recopilan las coordenadas del nodo a eliminar. En este método no se elimina del todo, ya que la eliminación
como tal se produce en el método de eliminación de columna.
*/
void MPP::eliminar_de_fila(std::string patente, int* arreglo, int fila) {

	//Nodo actual y anterior.
	NodoMPP* actual = filas[fila]->get_izquierdo();
	NodoMPP* anterior = filas[fila];


	while (actual != filas[fila]) {

		//Si el actual corresponde al que contiene el vehículo, se recogen sus datos 
		//Y se elimina la referencia del anterior.
		if (actual->get_vehiculo()->get_patente() == patente) {
			arreglo[0] = actual->get_fila();
			arreglo[1] = actual->get_columna();
			anterior->set_izquierdo(actual->get_izquierdo());
			return;
		}

		//Iteración.
		anterior = actual;
		actual = actual->get_izquierdo();
	}
	//Si no se encontró en la fila, su coordenada de fila será 0.
	arreglo[0] = 0;
}

/*
Eliminar de columna.
El proceso de recorrer por columna se produce de la misma manera que en el método de eliminar de fila.
Se tiene un nodo anterior y actual que recorren la columna, hasta que el actual sea la cabecera o contenga
el vehículo a eliminar. Acá se quita su referencia de su anterior (o sea, el nodo de abajo), y se elimina
definitivamente con el delete.
*/
void MPP::eliminar_de_columna(std::string patente, int* arreglo, int columna){

	NodoMPP* actualCol = columnas[columna]->get_superior();
	NodoMPP* anteriorCol = columnas[columna];

	while (actualCol != columnas[columna]) {

		if (actualCol->get_vehiculo()->get_patente() == patente) {
			anteriorCol->set_superior(actualCol->get_superior());
			//Eliminación del nodo.
			delete actualCol;
			return;
		}

		//Iteración.
		anteriorCol = actualCol;
		actualCol = actualCol->get_superior();
	}
	//Si no está en la columna, su coordenada de columna es igual a 0.
	arreglo[1] = 0;
}


/*
Lista de patentes del estacionaiento.
Se recorre por cada columna (iterando mediante filas), obtienendo todas las patentes de los 
autos estacionados.
*/
void MPP::lista_patentes(){

	std::cout << "Lista de patentes del estacionamiento" << std::endl;

	for (int fila = 1; fila <= 30; fila++) {
	
		//Nodo auxiliar.
		NodoMPP* aux = filas[fila]->get_izquierdo();

		//Mientras no sea la cabecera, se obtienen los datos de los vehículos (patente, fila y columna).
		while (aux != filas[fila]) {
			std::cout << aux->get_vehiculo()->get_patente() << " Fila:" << fila << " Columna: "<< aux->get_columna() << std::endl;
			aux = aux->get_izquierdo();
		}	
	}
}

/*
¿Está llena?
Retorna una variable booleana para identificar si la matriz está llena en los espacios que se 
pueden estacionar. Si al recorrer mediante cada columna no se encuentra algún vehículo con un espacio especificado,
significa que hay un espacio desocupado, y por ende, la matriz no está llena.
*/
bool MPP::esta_llena() {
	for (int columna = 1; columna <= 30; columna++) {
		//Se recorre la fila 30, por cada una de las columnas.
		Vehiculo* vehiculo = obtener_vehiculo(30, columna);

		//Si hay un vehículo que no existe, se retorna false porque la matriz no está llena.
		if (vehiculo == nullptr) {
			return false;
		}
	}

	//Caso contrario, true.
	return true;
}

/*
Ver estadísticas.
Mediante contadores, se obtiene cada uno de los vehículos por fila y columna, para generar las estadísticas. 
Si el vehículo existe, se incrementa en 1 el contador de vehículos totales. 
A partir del tipo de vehículo, se incrementan también los otros contadores, además de si está tuneado (característica propia).
Luego, se imprime el total de porcentaje total ocupado (de 600), los porcentajes de cada uno de los tipos de vehículos, 
y finalmente, el porcentaje respecto al total de la característica propia (tuneado).
Si no hay vehículos estacionados, se imprime un mensaje de error.
*/
void MPP::ver_estadisticas(){


	//Contadores iniciados en 0.
	double contador_de_vehiculos = 0;
	double contador_de_autos = 0;
	double contador_de_motos = 0;
	double contador_de_furgonetas = 0;
	double contador_de_camionetas = 0;
	double contador_tuneados = 0;

	for (int fila = 1; fila <= 30; fila++) {
		for (int columna = 1; columna <= 30; columna++) {
			//Obtención de vehículo.
			Vehiculo* vehiculo = obtener_vehiculo(fila, columna);

			//El vehículo existe.
			if (vehiculo != nullptr) {
				contador_de_vehiculos++;
				
				//Contadores dependiendo del tipo.
				
				if (vehiculo->get_tipo() == "Auto") {
					contador_de_autos++;

				} else if (vehiculo->get_tipo() == "Moto") {
					contador_de_motos++;

				} else if (vehiculo->get_tipo() == "Camioneta") {
					contador_de_camionetas++;
				}
				else if (vehiculo->get_tipo() == "Furgoneta") {
					contador_de_furgonetas++;
				}

				//Está tuneado o no.
				if (vehiculo->get_esta_tuneado()) {
					contador_tuneados++;
				}
			}
		}
	}

	//El porcentaje de vehículos se toma con respecto a 600 (porque son 600 espacios estacionables).
	std::cout << "El porcentaje de espacios ocupados es del " << (contador_de_vehiculos/600) * 100 << "% con " << contador_de_vehiculos << " espacios ocupados de 600 en total" <<std::endl;

	//Despliegue de estadísticas totales de los vehículos.
	if (contador_de_vehiculos > 0) {

		std::cout << "Porcentaje de vehiculos por tipo: \n"
			"Autos: " << (contador_de_autos / contador_de_vehiculos) * 100 << "% con: " << contador_de_autos << " autos" << "\n"
			"Motos: " << (contador_de_motos / contador_de_vehiculos) * 100 << "% con: " << contador_de_motos << " motos" << "\n"
			"Furgonetas: " << (contador_de_furgonetas / contador_de_vehiculos) * 100 << "% con: " << contador_de_furgonetas << " furgonetas" << "\n"
			"Camionetas: " << (contador_de_camionetas / contador_de_vehiculos) * 100 << "% con: " << contador_de_camionetas << " camionetas" << "\n"
			"Haciendo un total de: " << contador_de_vehiculos << " vehiculos" << std::endl;
		std::cout << "Hay un " << (contador_tuneados / contador_de_vehiculos) * 100 << "% de vehiculos tuneados" << std::endl;
	} else {
		std::cout << "No hay vehiculos ingresados en el sistema" << std::endl;
	}
}

