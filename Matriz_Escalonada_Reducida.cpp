#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Fraccion {
    int numerador;
    int denominador;
};

int mcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

Fraccion simplificar(Fraccion f) {
    int gcd = mcd(abs(f.numerador), abs(f.denominador));
    f.numerador /= gcd;
    f.denominador /= gcd;
    if (f.denominador < 0) {
        f.numerador = -f.numerador;
        f.denominador = -f.denominador;
    }
    return f;
}

Fraccion suma(Fraccion a, Fraccion b) {
    Fraccion result;
    result.numerador = a.numerador * b.denominador + b.numerador * a.denominador;
    result.denominador = a.denominador * b.denominador;
    return simplificar(result);
}

Fraccion resta(Fraccion a, Fraccion b) {
    Fraccion result;
    result.numerador = a.numerador * b.denominador - b.numerador * a.denominador;
    result.denominador = a.denominador * b.denominador;
    return simplificar(result);
}

Fraccion multiplica(Fraccion a, Fraccion b) {
    Fraccion result;
    result.numerador = a.numerador * b.numerador;
    result.denominador = a.denominador * b.denominador;
    return simplificar(result);
}

Fraccion divide(Fraccion a, Fraccion b) {
    Fraccion result;
    result.numerador = a.numerador * b.denominador;
    result.denominador = a.denominador * b.numerador;
    return simplificar(result);
}

void imprimirMatriz(const vector<vector<Fraccion>>& matrix) {
    for (const auto& fila : matrix) {
        for (int j = 0; j < fila.size(); j++) {
            Fraccion val = fila[j];
            if (j == fila.size() - 1) {
                cout << "| ";  
            }
            if (val.denominador == 1) {
                cout << val.numerador << "\t";
            } else {
                cout << val.numerador << "/" << val.denominador << "\t";
            }
        }
        cout << endl;
    }
    cout << "_____________________________________________________________" << endl;
}

bool validarEntrada() {
    if (cin.fail()) {
        cout << "Error entrada invalida. Por favor, introduce un numero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

vector<Fraccion> gaussJordan(vector<vector<Fraccion>> matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        int pivotRow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(matrix[j][i].numerador) > abs(matrix[pivotRow][i].numerador)) {
                pivotRow = j;
            }
        }
        cout << "Intercambiando fila " << i + 1 << " con fila " << pivotRow + 1 << endl;
        swap(matrix[i], matrix[pivotRow]);
        imprimirMatriz(matrix);

        Fraccion pivot = matrix[i][i];
        cout << "Dividiendo la fila " << i + 1 << " por " << pivot.numerador << "/" << pivot.denominador << " para hacer el pivote 1." << endl;
        for (int j = 0; j <= n; j++) {
            matrix[i][j] = divide(matrix[i][j], pivot);
        }
        imprimirMatriz(matrix);

        for (int j = 0; j < n; j++) {
            if (i != j) {
                Fraccion factor = matrix[j][i];
                cout << "Restando " << factor.numerador << "/" << factor.denominador << " veces la fila " << i + 1 << " de la fila " << j + 1 << "." << endl;
                for (int k = 0; k <= n; k++) {
                    matrix[j][k] = resta(matrix[j][k], multiplica(factor, matrix[i][k]));
                }
                imprimirMatriz(matrix);
            }
        }
    }
    vector<Fraccion> solution(n);
    for (int i = 0; i < n; i++) {
        solution[i] = matrix[i][n];
    }
    return solution;
}

int main() {
    int rows, cols;
    
    cout << "Ingrese el numero de filas: ";
    cin >> rows;
    while (!validarEntrada() || rows < 1) {
        cout << "Por favor, ingrese un numero valido de filas." << endl;
        cout << "Ingrese el numero de filas: ";
        cin >> rows;
    }

    cout << "Ingrese el numero de columnas (incluyendo el termino independiente): ";
    cin >> cols;
    while (!validarEntrada() || cols < 2) {
        cout << "Por favor, ingrese un numero valido de columnas (al menos 2)." << endl;
        cout << "Ingrese el numero de columnas (incluyendo el termino independiente): ";
        cin >> cols;
    }
    system("cls");

    vector<vector<Fraccion>> matrix(rows, vector<Fraccion>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int coeficiente;
            if (j < cols - 1) {
                cout << "Ingrese el coeficiente x" << j + 1 << " de la ecuacion " << i + 1 << ": ";
            } else {
                cout << "Ingrese el termino independiente de la ecuacion " << i + 1 << ": ";
            }
            cin >> coeficiente;
            while (!validarEntrada()) {
                if (j < cols - 1) {
                    cout << "Ingrese el coeficiente x" << j + 1 << " de la ecuacion " << i + 1 << ": ";
                } else {
                    cout << "Ingrese el termino independiente de la ecuacion " << i + 1 << ": ";
                }
                cin >> coeficiente;
            }
            matrix[i][j] = {coeficiente, 1};
        }
    }

    cout << "Matriz Original:" << endl;
    imprimirMatriz(matrix);

    vector<Fraccion> solution = gaussJordan(matrix);

    cout << "Solucion:" << endl;
    for (int i = 0; i < rows; i++) {
        if (solution[i].denominador == 1) {
            cout << "x" << i + 1 << " = " << solution[i].numerador << endl;
        } else {
            cout << "x" << i + 1 << " = " << solution[i].numerador << "/" << solution[i].denominador << endl;
        }
    }

    return 0;
}
