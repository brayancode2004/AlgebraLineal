#include <iostream>
#include <vector>
#include <cmath>  // Incluye esta cabecera para std::abs

using namespace std;

const double EPS = 1e-9;

double determinant(vector<vector<double> > a) {
    int n = a.size();
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(a[k][i]) > std::abs(a[maxRow][i])) {  // Usa std::abs aquí
                maxRow = k;
            }
        }

        swap(a[maxRow], a[i]);
        det *= a[i][i] * (i != maxRow ? -1 : 1);

        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i] / a[i][i];
            for (int j = i + 1; j < n; j++) {
                a[k][j] -= factor * a[i][j];
            }
        }
    }

    return det;
}

vector<vector<double> > inverseMatrix(vector<vector<double> > a) {
    int n = a.size();
    vector<vector<double> > res(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        res[i][i] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(a[k][i]) > std::abs(a[maxRow][i])) {
                maxRow = k;
            }
        }

        swap(a[maxRow], a[i]);
        swap(res[maxRow], res[i]);

        double div = a[i][i];
        for (int j = 0; j < n; j++) {
            a[i][j] /= div;
            res[i][j] /= div;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = a[k][i];
                for (int j = 0; j < n; j++) {
                    a[k][j] -= factor * a[i][j];
                    res[k][j] -= factor * res[i][j];
                }
            }
        }
    }

    return res;
}

vector<vector<double> > multiplyMatrices(const vector<vector<double> >& A, const vector<vector<double> >& B) {
    int n = A.size();
    vector<vector<double> > result(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

int main() {
    int n;
    cout << "Ingrese el numero de filas y columnas de la matriz: ";
    cin >> n;

    vector<vector<double> > mat(n, vector<double>(n));
    cout << "Ingrese los elementos de la matriz:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> mat[i][j];
        }
    }

    double det = determinant(mat);
    if (std::abs(det) < EPS) {  // Usa std::abs aquí también
        cout << "La matriz no tiene inversa." << endl;
        cout << "No existe porque el determinante es = " << det << endl;
    } else {
        vector<vector<double> > inv = inverseMatrix(mat);
        cout << "Matriz inversa:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << inv[i][j] << " ";
            }
            cout << endl;
        }

        vector<vector<double> > identity = multiplyMatrices(mat, inv);
        cout << "\nMultiplicacion de la matriz original con su inversa (debería ser la identidad):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (std::abs(identity[i][j]) < EPS) identity[i][j] = 0;  // Y aquí
                cout << identity[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}