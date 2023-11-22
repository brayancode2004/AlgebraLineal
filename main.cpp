#include <iostream>
#include <cstdlib>  // Para system()

int main() {
    int opcion;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Ejecutar Programa de Matriz Determinante\n";
        std::cout << "2. Ejecutar Programa de Matriz Escalonada Reducida\n";
        std::cout << "3. Ejecutar Programa de Matriz Inversa\n";
        std::cout << "4. Ejecutar Programa de Matriz Transpuesta\n";
        std::cout << "5. Ejecutar Programa de Matriz Triangular\n";
        std::cout << "6. Ejecutar Menu de Matrices\n";
        std::cout << "7. Salir\n";
        std::cout << "Ingrese su eleccion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::system("Matriz_Determinante");
                break;
            case 2:
                std::system("Matriz_Escalonada_Reducida");
                break;
            case 3:
                std::system("Matriz_Inversa");
                break;
            case 4:
                std::system("Matriz_Transpuesta");
                break;
            case 5:
                std::system("Matriz_Triangular");
                break;
            case 6:
                std::system("Menu_de_Matrices");
                break;
            case 7:
                std::cout << "Saliendo...\n";
                return 0;
                break;
            default:
                std::cout << "Opcion no valida." << std::endl;
        }
    } while (opcion != 8);

    return 0;
}
