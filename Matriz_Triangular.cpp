#include <iostream>
#include <vector>

void mostrarMatriz(const std::vector<std::vector<double>>& matriz) {
    for (const auto& fila : matriz) {
        for (double elemento : fila) {
            std::cout << elemento << " ";
        }
        std::cout << "\n";
    }
}

void convertirAMatrizTriangular(std::vector<std::vector<double>>& matriz) {
    int n = matriz.size();

    for (int i = 0; i < n; ++i) {
        if (matriz[i][i] == 0) {
            std::cout << "La matriz ya es triangular." << std::endl;
            return;
        }

        for (int j = i + 1; j < n; ++j) {
            double factor = matriz[j][i] / matriz[i][i];

            for (int k = i; k < n; ++k) {
                matriz[j][k] -= factor * matriz[i][k];
            }

            std::cout << "Paso " << i + 1 << ": Multiplica la fila " << i + 1 << " por " << factor
                      << " y resta a la fila " << j + 1 << "." << std::endl;
            mostrarMatriz(matriz);
            std::cout << std::endl;
        }
    }
}

int main() {
    int filas, columnas;

    std::cout << "Ingrese el numero de filas de la matriz: ";
    std::cin >> filas;
    std::cout << "Ingrese el numero de columnas de la matriz: ";
    std::cin >> columnas;

    std::vector<std::vector<double>> matriz(filas, std::vector<double>(columnas));

    std::cout << "Ingrese los elementos de la matriz:" << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << "Ingrese el elemento (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> matriz[i][j];
        }
    }

    std::cout << "\nMatriz ingresada:" << std::endl;
    mostrarMatriz(matriz);
    std::cout << std::endl;

    convertirAMatrizTriangular(matriz);

    std::cout << "\nMatriz triangular resultante:" << std::endl;
    mostrarMatriz(matriz);

    return 0;
}
