#include <iostream>
#include "Menu.h"
/*
El main del taller.
Inicializa un puntero al menú principal, e inicia la aplicación.
La inicialización está en un bloque try para capturar algún error en el sistema.
*/
int main(){
    try {
        Menu* menu = new Menu(); //Inicialización del menú.
        menu->iniciar(); //Iniciar el programa.
    }
    catch (std::exception e) {
        //Captura de excepción grave en el sistema.
        std::cerr << "Excepcion de tipo: " << e.what() << " Hubo un error en el sistema, lo sentimos." << std::endl;
    }
}
