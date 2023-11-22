#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

Matrix transpose(const Matrix& matrix) {
    Matrix trans(matrix[0].size(), vector<int>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            trans[j][i] = matrix[i][j];
        }
    }
    return trans;
}

bool canMultiply(const Matrix& mat1, const Matrix& mat2) {
    return mat1[0].size() == mat2.size();
}

Matrix matMult(const Matrix& mat1, const Matrix& mat2) {
    int rows1 = mat1.size();
    int cols1 = mat1[0].size();
    int cols2 = mat2[0].size();
    
    Matrix result(rows1, vector<int>(cols2, 0));
    
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    
    return result;
}

Matrix readMatrix(int rows, int cols) {
    Matrix matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Ingrese el elemento (" << i + 1 << ", " << j + 1 << "): ";
            while (!(cin >> matrix[i][j])) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada no valida. Introduce un numero valido para la posicion (" << i + 1 << ", " << j + 1 << "): ";
            }
        }
    }
    return matrix;
}

int main() {
    int rows, cols;
    cout << "Ingrese el numero de filas de la matriz A: ";
    while (!(cin >> rows) || rows <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Introduce un numero de filas valido: ";
    }

    cout << "Ingrese el numero de columnas de la matriz A: ";
    while (!(cin >> cols) || cols <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Introduce un numero de columnas valido: ";
    }

    Matrix A = readMatrix(rows, cols);

    cout << "Ingrese el numero de filas de la matriz x: ";
    while (!(cin >> rows) || rows <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Introduce un numero de filas valido: ";
    }

    cout << "Ingrese el numero de columnas de la matriz x: ";
    while (!(cin >> cols) || cols <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. Introduce un numero de columnas valido: ";
    }

    Matrix x = readMatrix(rows, cols);

    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Muestre las matrices originales ingresadas\n";
        cout << "2. Escriba la transpuesta de la matriz original ingresada\n";
        cout << "3. Calcule (Ax)^T\n";
        cout << "4. Calcule x^TA^T\n";
        cout << "5. Calcule xx^T\n";
        cout << "6. Calcule x^Tx\n";
        cout << "7. Salir\n";
        cout << "Ingrese su eleccion: ";
        
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no valida. Por favor, ingrese una opcion entre 1 y 7: ";
        }

        switch (choice) {
            case 1:
                cout << "Matriz A:\n";
                printMatrix(A);
                cout << "Matriz x:\n";
                printMatrix(x);
                break;
            case 2: {
                cout << "¿De que matriz desea obtener la transpuesta? (A/x): ";
                char matChoice;
                cin >> matChoice;
                if (matChoice == 'A' || matChoice == 'a') {
                    printMatrix(transpose(A));
                } else if (matChoice == 'x' || matChoice == 'X') {
                    printMatrix(transpose(x));
                } else {
                    cout << "Opcion no valida." << endl;
                }
                break;
            }

            case 3: {
                cout << "Paso 1: Calcule Ax\n";
                Matrix Ax = matMult(A, x);
                printMatrix(Ax);
                
                cout << "Paso 2: Transponga el resultado para obtener (Ax)^T\n";
                Matrix result = transpose(Ax);
                printMatrix(result);
                break;
            }
            case 4: {
                cout << "Paso 1: Calcule A^T\n";
                Matrix AT = transpose(A);
                printMatrix(AT);
                
                cout << "Paso 2: Calcule x^T\n";
                Matrix xT = transpose(x);
                printMatrix(xT);
                
                cout << "Paso 3: Multiplique x^T y A^T para obtener x^TA^T\n";
                Matrix result = matMult(xT, AT);
                printMatrix(result);
                break;
            }
            case 5: {
                cout << "Paso 1: Calcule x^T\n";
                Matrix xT = transpose(x);
                printMatrix(xT);
                
                cout << "Paso 2: Multiplique x y x^T para obtener xx^T\n";
                Matrix result = matMult(x, xT);
                printMatrix(result);
                break;
            }
            case 6: {
                cout << "Paso 1: Calcule x^T\n";
                Matrix xT = transpose(x);
                printMatrix(xT);
                
                cout << "Paso 2: Multiplique x^T y x para obtener x^Tx\n";
                Matrix result = matMult(xT, x);
                printMatrix(result);
                break;
            }
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
        if (choice != 7) {
            char continueChoice;
            do {
                cout << "¿Desea volver al menu? (s/n): ";
                cin >> continueChoice;
                if (continueChoice == 's' || continueChoice == 'S') {
                    system("CLS");  // Usa "clear" si estas en Linux/Unix
                } else if (continueChoice == 'n' || continueChoice == 'N') {
                    choice = 7;
                    cout << "Saliendo...\n";
                } else {
                    cout << "Opcion no valida. Por favor, ingrese 's' para si o 'n' para no.\n";
                }
            } while (continueChoice != 's' && continueChoice != 'S' && continueChoice != 'n' && continueChoice != 'N');
        }
    } while (choice != 7);

    return 0;
}