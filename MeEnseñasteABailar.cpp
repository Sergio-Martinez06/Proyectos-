#include <iostream>
#include <limits>
using namespace std;

struct Estudiante {
    int id;
    string nombre;
    float promedio;
    Estudiante* siguiente;
};

class ListaEstudiantes {
private:
    Estudiante* cabeza;
public:
    ListaEstudiantes() : cabeza(nullptr) {}

    bool idExiste(int id) {
        Estudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    void agregarEstudiante(int id, string nombre, float promedio) {
        if (nombre.empty()) {
            cout << "Error: El nombre no puede estar vacío.\n";
            return;
        }
        if (promedio < 0.0 || promedio > 5.0) {
            cout << "Error: El promedio debe estar entre 0.0 y 5.0.\n";
            return;
        }
        Estudiante* nuevo = new Estudiante{id, nombre, promedio, cabeza};
        cabeza = nuevo;
        cout << "Estudiante agregado exitosamente.\n";
    }

    void mostrarEstudiantes() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* actual = cabeza;
        while (actual) {
            cout << "ID: " << actual->id << " | Nombre: " << actual->nombre << " | Promedio: " << actual->promedio << "\n";
            actual = actual->siguiente;
        }
    }

    void buscarPorID(int id) {
        if (id <= 0) {
            cout << "Error: El ID debe ser un número positivo.\n";
            return;
        }
        Estudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) {
                cout << "Estudiante encontrado: " << actual->nombre << " | Promedio: " << actual->promedio << "\n";
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante no encontrado.\n";
    }

    void eliminarPorID(int id) {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        if (id <= 0) {
            cout << "Error: El ID debe ser un número positivo.\n";
            return;
        }
        if (cabeza->id == id) {
            Estudiante* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cout << "Estudiante eliminado.\n";
            return;
        }
        Estudiante* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id) {
            actual = actual->siguiente;
        }
        if (actual->siguiente) {
            Estudiante* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            cout << "Estudiante eliminado.\n";
        } else {
            cout << "Estudiante no encontrado.\n";
        }
    }

    void actualizarPromedio(int id, float nuevoPromedio) {
        if (id <= 0) {
            cout << "Error: El ID debe ser un número positivo.\n";
            return;
        }
        if (nuevoPromedio < 0.0 || nuevoPromedio > 5.0) {
            cout << "Error: El promedio debe estar entre 0.0 y 5.0.\n";
            return;
        }
        Estudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) {
                actual->promedio = nuevoPromedio;
                cout << "Promedio actualizado.\n";
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante no encontrado.\n";
    }

    void mostrarMejorPromedio() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* mejor = cabeza;
        Estudiante* actual = cabeza->siguiente;
        while (actual) {
            if (actual->promedio > mejor->promedio) {
                mejor = actual;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante con mejor promedio: " << mejor->nombre << " | Promedio: " << mejor->promedio << "\n";
    }
};

int main() {
    ListaEstudiantes lista;
    int opcion, id;
    string nombre;
    float promedio;
    
    do {
        cout << "\n1. Agregar estudiante\n2. Mostrar estudiantes\n3. Buscar por ID\n4. Eliminar por ID\n5. Actualizar promedio\n6. Mejor promedio\n7. Salir\nOpcion: ";
        while (!(cin >> opcion)) {
            cout << "Error: Ingrese un número válido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcion) {
            case 1:
    
    do {
        cout << "ID: ";
        while (!(cin >> id) || id <= 0 || lista.idExiste(id) || cin.peek() != '\n') {
            cout << "Error: El ID debe ser un número positivo y único. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (id <= 0 || lista.idExiste(id));
    cin.ignore();

    // Validación del nombre
    cout << "Nombre: ";
    getline(cin, nombre);
    while (nombre.find_first_not_of(" ") == string::npos) {
        cout << "Error: El nombre no puede estar vacío o contener solo espacios. Intente nuevamente.\n";
        cout << "Nombre: ";
        getline(cin, nombre);
    }

    cout << "Promedio: ";
    while (!(cin >> promedio) || promedio < 0.0 || promedio > 5.0 || cin.peek() != '\n') {
        cout << "Error: El promedio debe estar entre 0.0 y 5.0. Intente nuevamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    lista.agregarEstudiante(id, nombre, promedio);
    break;

            case 2:
                lista.mostrarEstudiantes();
                break;
            case 3:
    cout << "ID a buscar: ";
    while (!(cin >> id) || id <= 0 || cin.peek() != '\n') {
        cout << "Error: Ingrese un ID válido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    lista.buscarPorID(id);
    break;
            case 4:
                cout << "ID a eliminar: ";
    while (!(cin >> id) || id <= 0 || cin.peek() != '\n') {
        cout << "Error: Ingrese un ID válido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    lista.eliminarPorID(id);
    break;
            case 5:
                cout << "ID a actualizar: ";
    while (!(cin >> id) || id <= 0 || cin.peek() != '\n') {
        cout << "Error: Ingrese un ID válido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Nuevo promedio: ";
    while (!(cin >> promedio) || promedio < 0.0 || promedio > 5.0 || cin.peek() != '\n') {
        cout << "Error: Ingrese un promedio válido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    lista.actualizarPromedio(id, promedio);
    break;
            case 6:
                lista.mostrarMejorPromedio();
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 7);
    
    return 0;
}

