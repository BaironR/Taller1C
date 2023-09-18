#include <iostream>
#include "Menu.h"

int main(){
    try {

        Menu* menu = new Menu();
        menu->iniciar();
    }
    catch (std::exception e) {
        std::cerr << "Excepcion de tipo: " << e.what() << " Hubo un error en el sistema, lo sentimos" << std::endl;
    }
}
