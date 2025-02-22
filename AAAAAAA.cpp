#include <iostream>
#include <limits>
using namespace std;

char matriz[10][15];

void mostrarSala() {
    for (int i = 0; i < 10; i++) {
        if (i + 1 < 10) {
            cout << " ";
        }
        cout << i + 1 << ": ";

        for (int j = 0; j < 15; j++) {
            cout << " " << (char)('A' + j) << j + 1 << "(" << matriz[i][j] << ") ";
        }
        cout << endl;
    }
}

int main() {
    char letra = 'A';
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            matriz[i][j] = 'L';
        }
    }

    int accion;
    int fila, columna;

    while (true) {
        cout << "\nQue te gustaria hacer?\n";
        cout << "1. Mostrar la matriz\n";
        cout << "2. Reservar un asiento (R)\n";
        cout << "3. Ocupar un asiento (O)\n";
        cout << "4. Cancelar una reserva\n";
        cout << "5. Salir\n";

        bool opcionValida = false;
        while (!opcionValida) {
            cout << "Elige una opcion (1-5): ";
            cin >> accion;

            if (cin.fail() || accion < 1 || accion > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Opcion invalida. Por favor, elige un numero entre 1 y 5.\n";
            } else {
                opcionValida = true;
            }
        }

        if (accion == 1) {
            mostrarSala();
        } else if (accion == 2 || accion == 3 || accion == 4) {
            cout << "Ingresa la fila (1-10) y columna (1-15) para realizar la accion: ";
            cin >> fila >> columna;

            if (cin.fail() || fila < 1 || fila > 10 || columna < 1 || columna > 15) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. Por favor, ingresa una fila entre 1 y 10 y una columna entre 1 y 15.\n";
                continue;
            }

            fila -= 1;
            columna -= 1;

            if (accion == 2) {
                if (matriz[fila][columna] == 'L') {
                    matriz[fila][columna] = 'R';
                    cout << "El asiento " << (char)('A' + columna) << columna + 1 << fila + 1 << " ha sido reservado.\n";
                } else if (matriz[fila][columna] == 'R') {
                    cout << "El asiento ya esta reservado.\n";
                } else {
                    cout << "El asiento ya esta ocupado.\n";
                }
            } else if (accion == 3) {
                if (matriz[fila][columna] == 'L' || matriz[fila][columna] == 'R') {
                    matriz[fila][columna] = 'O';
                    cout << "El asiento " << (char)('A' + columna) << columna + 1 << fila + 1 << " ha sido ocupado.\n";
                } else {
                    cout << "El asiento ya esta ocupado.\n";
                }
            } else if (accion == 4) {
                if (matriz[fila][columna] == 'R') {
                    matriz[fila][columna] = 'L';
                    cout << "La reserva del asiento " << (char)('A' + columna) << columna + 1 << fila + 1 << " ha sido cancelada.\n";
                } else if (matriz[fila][columna] == 'L') {
                    cout << "El asiento no esta reservado.\n";
                } else {
                    cout << "El asiento ya esta ocupado.\n";
                }
            }
        } else if (accion == 5) {
            break;
        }
    }

    return 0;
}




