#include <iostream>
#include <vector>
#include <algorithm>  // Para std::swap

void limpiarPantalla() {
    system("cls");
}

using namespace std;

template <typename T>
void imprimirMatriz(const std::vector<std::vector<T>>& matriz) {
    for (const auto& fila : matriz) {
        for (T val : fila) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

double calcularDeterminante(std::vector<std::vector<double>>& matriz) {
    const size_t n = matriz.size();
    if (n == 1) {
        return matriz[0][0];
    }

    double determinante = 0;
    double cofactor;
    for (size_t i = 0; i < n; ++i) {
        std::vector<std::vector<double>> submatriz(n - 1, std::vector<double>(n - 1, 0.0));
        for (size_t j = 1; j < n; ++j) {
            for (size_t k = 0, col = 0; k < n; ++k) {
                if (k == i) continue;
                submatriz[j - 1][col++] = matriz[j][k];
            }
        }

        std::cout << "Submatriz para el elemento [" << 0 << "][" << i << "]:\n";
        imprimirMatriz(submatriz);

        double signo = (i % 2 == 0) ? 1.0 : -1.0;
        cofactor = signo * matriz[0][i] * calcularDeterminante(submatriz);
        determinante += cofactor;
        std::cout << "Cofactor para el elemento [" << 0 << "][" << i << "]: " << cofactor << "\n";
    }
    std::cout << "Determinante parcial: " << determinante << "\n";
    return determinante;
}

double determinante_sarrus_3x3(const std::vector<std::vector<double>>& matriz) {
    double term1 = matriz[0][0] * matriz[1][1] * matriz[2][2];
    double term2 = matriz[0][1] * matriz[1][2] * matriz[2][0];
    double term3 = matriz[0][2] * matriz[1][0] * matriz[2][1];
    double term4 = matriz[2][0] * matriz[1][1] * matriz[0][2];
    double term5 = matriz[2][1] * matriz[1][2] * matriz[0][0];
    double term6 = matriz[2][2] * matriz[1][0] * matriz[0][1];
    
    std::cout << "----------------------- Metodo de Sarrus -----------------------\n";
    std::cout << "Terminos Positivos:\n";
    std::cout << matriz[0][0] << " * " << matriz[1][1] << " * " << matriz[2][2] << " = " << term1 << "\n";
    std::cout << matriz[0][1] << " * " << matriz[1][2] << " * " << matriz[2][0] << " = " << term2 << "\n";
    std::cout << matriz[0][2] << " * " << matriz[1][0] << " * " << matriz[2][1] << " = " << term3 << "\n";
    
    std::cout << "\nTerminos Negativos:\n";
    std::cout << matriz[2][0] << " * " << matriz[1][1] << " * " << matriz[0][2] << " = -" << term4 << "\n";
    std::cout << matriz[2][1] << " * " << matriz[1][2] << " * " << matriz[0][0] << " = -" << term5 << "\n";
    std::cout << matriz[2][2] << " * " << matriz[1][0] << " * " << matriz[0][1] << " = -" << term6 << "\n";
    std::cout << "--------------------------------------------------------------------\n";

    return term1 + term2 + term3 - term4 - term5 - term6;
}

double determinante_sarrus_4x4(const std::vector<std::vector<double>>& matriz) {
    double det = 0.0;
    std::vector<std::vector<double>> submatriz(3, std::vector<double>(3));
    
    std::cout << "----------------------- Metodo de Sarrus -----------------------\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            int col = 0;
            for (int k = 0; k < 4; k++) {
                if (k == i) continue;
                submatriz[j-1][col] = matriz[j][k];
                col++;
            }
        }
        double term = matriz[0][i] * determinante_sarrus_3x3(submatriz);
        det += (i % 2 == 0) ? term : -term;

        std::cout << "Termino " << i+1 << " (" << (i % 2 == 0 ? "+" : "-") << matriz[0][i] << " * det(submatriz)) = " << term << "\n";
    }
    std::cout << "--------------------------------------------------------------------\n";
    
    return det;
}

double determinante_sarrus(const std::vector<std::vector<double>>& matriz) {
    std::cout << "\nMatriz original:\n";
    imprimirMatriz(matriz);
    std::cout << "Calculando determinante usando el metodo de Sarrus:\n";

    if (matriz.size() == 3) {
        return determinante_sarrus_3x3(matriz);
    } else if (matriz.size() == 4) {
        return determinante_sarrus_4x4(matriz);
    } else {
        std::cout << "El metodo de Sarrus extendido solo es valido para matrices 3x3 y 4x4.\n";
        return 0.0;
    }
}

double determinante_triangular_superior(std::vector<std::vector<double>>& matriz) {
    std::cout << "\nMatriz original:\n";
    imprimirMatriz(matriz);
    const size_t n = matriz.size();

    double determinante = 1.0;
    int num_swaps = 0;

    for (size_t i = 0; i < n; ++i) {
        if (matriz[i][i] == 0) {
            bool swapped = false;
            for (size_t k = i + 1; k < n; ++k) {
                if (matriz[k][i] != 0) {
                    std::swap(matriz[i], matriz[k]);
                    swapped = true;
                    num_swaps++;
                    break;
                }
            }
            if (!swapped) {
                return 0.0;
            }
        }

        for (size_t j = i + 1; j < n; ++j) {
            const double factor = matriz[j][i] / matriz[i][i];
            for (size_t k = 0; k < n; ++k) {
                matriz[j][k] -= factor * matriz[i][k];
            }
        }
        
        std::cout << "Matriz despues de la eliminacion hacia adelante del paso " << i + 1 << ":\n";
        imprimirMatriz(matriz);
        
        determinante *= matriz[i][i];
    }

    if (num_swaps % 2 != 0) {
        determinante = -determinante;
    }

    return determinante;
}

int main() {
    int n;
    int opcion;
    
    do {
        std::cout << "Ingrese el tamano de la matriz (N): ";
        std::cin >> n;
    } while (n <= 0);

    std::vector<std::vector<double>> matriz(n, std::vector<double>(n, 0.0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << "Ingrese el elemento [" << i << "][" << j << "]: ";
            std::cin >> matriz[i][j];
        }
    }

    do {
        std::cout << "\nElija el metodo para calcular el determinante:\n";
        std::cout << "1. Resolverlo por cofactores\n";
        std::cout << "2. Resolverlo por el metodo de Sarrus\n";
        std::cout << "3. Resolverlo por la triangular superior\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;
        limpiarPantalla();

        double determinante;

        switch (opcion) {
            case 1:
            {
                determinante = calcularDeterminante(matriz);
                std::cout << "El determinante de la matriz es: " << determinante << "\n";
                break;
            }
             case 2:
        {
            if (n == 3 || n == 4) {
                determinante = determinante_sarrus(matriz);
                std::cout << "El determinante de la matriz es: " << determinante << "\n";
            } else {
                std::cout << "El metodo de Sarrus extendido solo es valido para matrices 3x3 y 4x4.\n";
            }
            break;
        }
            case 3:
            {
                determinante = determinante_triangular_superior(matriz);
                std::cout << "El determinante de la matriz es: " << determinante << "\n";
                break;
            }
            case 4:
            {
                std::cout << "Saliendo...\n";
                break;
            }
            default:
            {
                std::cout << "Opcion invalida!\n";
                break;
            }
        }
    } while (opcion != 4);

    return 0;
}
