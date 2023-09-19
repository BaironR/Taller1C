#include <iostream>
#include "Menu.h"
/*
El main del taller.
Inicializa un puntero al men� principal, e inicia la aplicaci�n.
La inicializaci�n est� en un bloque try para capturar alg�n error en el sistema.
*/
int main(){
    try {
        Menu* menu = new Menu(); //Inicializaci�n del men�.
        menu->iniciar(); //Iniciar el programa.
    }
    catch (std::exception e) {
        //Captura de excepci�n grave en el sistema.
        std::cerr << "Excepcion de tipo: " << e.what() << " Hubo un error en el sistema, lo sentimos." << std::endl;
    }
}
