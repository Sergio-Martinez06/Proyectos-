#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

struct Estudiante {
    int id;
    string nombre;
    float promedio;
    Estudiante* siguiente;
    Estudiante* anterior;
};

class ListaEstudiantes {
private:
    Estudiante* cabeza;
    Estudiante* actual;
    int posicionActual;

public:
    ListaEstudiantes() : cabeza(nullptr), actual(nullptr), posicionActual(0) {}

    Estudiante* obtenerCabeza() { return cabeza; }
    Estudiante* obtenerActual() { return actual; }
    int obtenerPosicionActual() { return posicionActual; }
    void establecerActual(Estudiante* nuevoActual) { actual = nuevoActual; }

    int obtenerPosicion(Estudiante* nodo) {
        if (!cabeza || !nodo) return -1;
        int pos = 1;
        Estudiante* temp = cabeza;
        do {
            if (temp == nodo) return pos;
            temp = temp->siguiente;
            pos++;
        } while (temp != cabeza);
        return -1;
    }

    bool idExiste(int id) {
        if (!cabeza) return false;
        Estudiante* temp = cabeza;
        do {
            if (temp->id == id) return true;
            temp = temp->siguiente;
        } while (temp != cabeza);
        return false;
    }

    int contarEstudiantes() {
        if (!cabeza) return 0;
        int contador = 0;
        Estudiante* temp = cabeza;
        do {
            contador++;
            temp = temp->siguiente;
        } while (temp != cabeza);
        return contador;
    }

    void agregarEstudiante(int id, string nombre, float promedio) {
        Estudiante* nuevo = new Estudiante{id, nombre, promedio, nullptr, nullptr};

        if (!cabeza) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            Estudiante* ultimo = cabeza->anterior;
            nuevo->siguiente = cabeza;
            nuevo->anterior = ultimo;
            ultimo->siguiente = nuevo;
            cabeza->anterior = nuevo;
        }

        actual = nuevo;
        posicionActual = contarEstudiantes();
        cout << "Estudiante agregado exitosamente en la posicion #" << posicionActual << ".\n";
    }

    void mostrarEstudiantes() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* temp = cabeza;
        int pos = 1;
        do {
            cout << "Posicion #" << pos++ << ": ID: " << temp->id << " | Nombre: " << temp->nombre << " | Promedio: " << temp->promedio << "\n";
            temp = temp->siguiente;
        } while (temp != cabeza);
    }

    void buscarPorID(int id) {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* temp = cabeza;
        int pos = 1;
        do {
            if (temp->id == id) {
                cout << "Estudiante encontrado en la posicion #" << pos << ": " << temp->nombre << " | Promedio: " << temp->promedio << "\n";
                return;
            }
            temp = temp->siguiente;
            pos++;
        } while (temp != cabeza);
        cout << "Estudiante no encontrado.\n";
    }

    void eliminarEstudianteActual() {
        if (!actual) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }

        Estudiante* aEliminar = actual;
        if (aEliminar->siguiente == aEliminar) {
            delete aEliminar;
            cabeza = actual = nullptr;
            posicionActual = 0;
            cout << "Ultimo estudiante eliminado. La lista esta vacia.\n";
            return;
        }

        aEliminar->anterior->siguiente = aEliminar->siguiente;
        aEliminar->siguiente->anterior = aEliminar->anterior;
        if (aEliminar == cabeza)
            cabeza = cabeza->siguiente;
        actual = aEliminar->siguiente;
        delete aEliminar;

        posicionActual = obtenerPosicion(actual);
        cout << "Estudiante eliminado. Ahora estas en la posicion #" << posicionActual
             << ": ID " << actual->id << " | " << actual->nombre << " | Promedio: " << actual->promedio << endl;
    }

    void actualizarPromedioActual() {
        if (!actual) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }

        float nuevoPromedio;
        cout << "Estas actualizando el promedio de:\n";
        cout << "ID: " << actual->id << " | Nombre: " << actual->nombre << " | Promedio actual: " << actual->promedio << endl;
        cout << "Ingrese el nuevo promedio: ";
        cin >> nuevoPromedio;

        if (nuevoPromedio < 0.0 || nuevoPromedio > 5.0) {
            cout << "Promedio invalido. Debe estar entre 0.0 y 5.0\n";
            return;
        }

        actual->promedio = nuevoPromedio;
        cout << "Promedio actualizado exitosamente.\n";
    }

    void mostrarMejorPromedio() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* mejor = cabeza;
        Estudiante* temp = cabeza->siguiente;
        do {
            if (temp->promedio > mejor->promedio) {
                mejor = temp;
            }
            temp = temp->siguiente;
        } while (temp != cabeza);
        cout << "Estudiante con mejor promedio: " << mejor->nombre << " | Promedio: " << mejor->promedio << "\n";
    }

    void insertarEnPosicion(int posicion, int id, string nombre, float promedio) {
        Estudiante* nuevo = new Estudiante{id, nombre, promedio, nullptr, nullptr};

        if (!cabeza || posicion <= 1) {
            if (!cabeza) {
                cabeza = nuevo;
                cabeza->siguiente = cabeza;
                cabeza->anterior = cabeza;
            } else {
                Estudiante* ultimo = cabeza->anterior;
                nuevo->siguiente = cabeza;
                nuevo->anterior = ultimo;
                ultimo->siguiente = nuevo;
                cabeza->anterior = nuevo;
                cabeza = nuevo;
            }
            actual = cabeza;
            posicionActual = 1;
            cout << "Estudiante insertado en la posicion 1.\n";
            return;
        }

        Estudiante* temp = cabeza;
        int pos = 1;
        while (pos < posicion - 1 && temp->siguiente != cabeza) {
            temp = temp->siguiente;
            pos++;
        }

        Estudiante* siguiente = temp->siguiente;
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
        nuevo->siguiente = siguiente;
        siguiente->anterior = nuevo;

        actual = nuevo;
        posicionActual = pos + 1;
        cout << "Estudiante insertado en la posicion " << posicionActual << ".\n";
    }

    void avanzar() {
        if (actual) {
            actual = actual->siguiente;
            posicionActual = obtenerPosicion(actual);
        }
    }

    void retroceder() {
        if (actual) {
            actual = actual->anterior;
            posicionActual = obtenerPosicion(actual);
        }
    }
};

int main() {
    ListaEstudiantes lista;
    int opcion;

    do {
        int total = lista.contarEstudiantes();

        cout << "\n--- Estas en la posicion #" << lista.obtenerPosicionActual() << " ---\n";

if (lista.obtenerActual()) {
    Estudiante* est = lista.obtenerActual();
    cout << "ID: " << est->id << " | Nombre: " << est->nombre << " | Promedio: " << est->promedio << "\n";
}

        cout << "1. Agregar estudiante\n";
        if (total > 0) {
            cout << "2. Mostrar estudiantes\n";
            cout << "3. Buscar por ID\n";
            cout << "4. Eliminar estudiante actual\n";
            cout << "5. Actualizar promedio del estudiante actual\n";
            cout << "6. Mostrar mejor promedio\n";
            cout << "7. Insertar en posicion especifica\n";
            if (total > 1) {
                cout << "8. Siguiente estudiante\n";
                cout << "9. Estudiante anterior\n";
            }
        }
        cout << "10. Salir\n";
        cout << "Opcion: ";

        while (!(cin >> opcion)) {
            cout << "Error: Ingrese un numero valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion < 1 || opcion > 10 ||
            (total == 0 && opcion >= 2 && opcion <= 9) ||
            (total <= 1 && (opcion == 8 || opcion == 9))) {
            cout << "Opcion no disponible en este momento.\n";
            continue;
        }

        switch (opcion) {
            case 1: {
                int id;
                string nombre;
                float promedio;

                do {
                    cout << "ID: ";
                    while (!(cin >> id) || id <= 0 || lista.idExiste(id) || cin.peek() != '\n') {
                        cout << "Error: ID invalido o repetido. Intente nuevamente.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (id <= 0 || lista.idExiste(id));
                cin.ignore();

                do {
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    nombre.erase(0, nombre.find_first_not_of(" \t"));
                    nombre.erase(nombre.find_last_not_of(" \t") + 1);
                } while (nombre.empty());

                cout << "Promedio: ";
                while (!(cin >> promedio) || promedio < 0.0 || promedio > 5.0 || cin.peek() != '\n') {
                    cout << "Error: Promedio invalido. Intente nuevamente.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                lista.agregarEstudiante(id, nombre, promedio);
                break;
            }

            case 2:
                lista.mostrarEstudiantes();
                break;

            case 3: {
                int id;
                cout << "ID a buscar: ";
                cin >> id;
                lista.buscarPorID(id);
                break;
            }

            case 4:
                lista.eliminarEstudianteActual();
                break;

            case 5:
                lista.actualizarPromedioActual();
                break;

            case 6:
                lista.mostrarMejorPromedio();
                break;

            case 7: {
                int id, pos;
                string nombre;
                float promedio;

                cout << "ID: ";
                while (!(cin >> id) || id <= 0 || lista.idExiste(id) || cin.peek() != '\n') {
                    cout << "Error: ID invalido o repetido. Intente nuevamente.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();

                do {
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    nombre.erase(0, nombre.find_first_not_of(" \t"));
                    nombre.erase(nombre.find_last_not_of(" \t") + 1);
                } while (nombre.empty());

                cout << "Promedio: ";
                while (!(cin >> promedio) || promedio < 0.0 || promedio > 5.0 || cin.peek() != '\n') {
                    cout << "Error: Promedio invalido. Intente nuevamente.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                do {
                    cout << "Posicion (1 a " << total + 1 << "): ";
                    cin >> pos;
                    if (cin.fail() || pos < 1 || pos > total + 1) {
                        cout << "Posicion invalida.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pos = -1;
                    }
                } while (pos == -1);

                lista.insertarEnPosicion(pos, id, nombre, promedio);
                break;
            }

            case 8:
                lista.avanzar();
                break;

            case 9:
                lista.retroceder();
                break;

            case 10:
                cout << "Saliendo...\n";
                break;
        }

    } while (opcion != 10);

    return 0;
}



