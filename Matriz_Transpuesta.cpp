#include <iostream>

const int MAX_ROWS = 100;
const int MAX_COLS = 100;

void calcularTranspuesta(int matriz[MAX_ROWS][MAX_COLS], int filas, int columnas) {
    int transpuesta[MAX_COLS][MAX_ROWS];

    // Calcular la transpuesta intercambiando filas por columnas
    for (int i = 0; i < columnas; ++i) {
        for (int j = 0; j < filas; ++j) {
            transpuesta[i][j] = matriz[j][i];
        }
    }

    // Mostrar la matriz transpuesta
    std::cout << "Matriz transpuesta:\n";
    for (int i = 0; i < columnas; ++i) {
        for (int j = 0; j < filas; ++j) {
            std::cout << transpuesta[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int filas, columnas;

    std::cout << "Ingrese el numero de filas de la matriz: ";
    std::cin >> filas;

    std::cout << "Ingrese el numero de columnas de la matriz: ";
    std::cin >> columnas;

    int matriz[MAX_ROWS][MAX_COLS];

    std::cout << "Ingrese los elementos de la matriz:\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> matriz[i][j];
        }
    }

    // Calcular y mostrar la transpuesta de la matriz
    calcularTranspuesta(matriz, filas, columnas);

    return 0;
}
