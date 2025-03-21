#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>

using namespace std;


bool esNumeroDecimalValido(const string& input) {
    bool puntoDecimalEncontrado = false;
    
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '.') {
            if (puntoDecimalEncontrado) {  
                return false;
            }
            puntoDecimalEncontrado = true;
        } else if (!isdigit(input[i]) && input[i] != '.') {
            return false;  
        }
    }
    return true;
}


bool leerNumeroDecimal(float& numero) {
    string input;
    getline(cin, input);  


    if (!esNumeroDecimalValido(input)) {
        cout << "Error: Ingrese un número decimal válido.\n";
        return false;
    }

   
    numero = stof(input);
    return true;
}


bool leerNumeroEntero(int& numero) {
    string input;
    getline(cin, input);  


    for (char c : input) {
        if (!isdigit(c)) {
            cout << "Error: Ingrese un número entero válido.\n";
            return false;
        }
    }

 
    numero = stoi(input);
    return true;
}


struct Persona {
    string nombre;
    string telefono;


    void ingresarNombre(const string& tipo) {
        while (true) {
            cout << "Ingrese el nombre del " << tipo << ": ";
            getline(cin, nombre);
            bool valido = true;
            for (char c : nombre) {
                if (!isalpha(c) && c != ' ') {
                    valido = false;
                    break;
                }
            }
            if (valido) break;
            cout << "Error: El nombre solo puede contener letras y espacios.\n";
        }
    }

 
    void ingresarTelefono() {
        while (true) {
            cout << "Ingrese el telefono: ";
            getline(cin, telefono);
            bool valido = true;
            for (char c : telefono) {
                if (!isdigit(c)) {
                    valido = false;
                    break;
                }
            }
            if (valido) break;
            cout << "Error: El telefono debe contener solo numeros.\n";
        }
    }
};


struct Materia {
    string nombre;
    string horario;
    vector<float> notas;

    void ingresarNotas() {
        notas.resize(3); 
        for (int i = 0; i < 3; i++) {
            while (true) {
                cout << "Nota del examen " << i + 1 << ": ";  
                if (leerNumeroDecimal(notas[i]) && notas[i] >= 0 && notas[i] <= 10) {
                    break;
                } else {
                    cout << "Error: Ingrese un valor valido para la nota (entre 0 y 10).\n";
                }
            }
        }
    }

    float calcularPromedio() const {
        return (notas[0] + notas[1] + notas[2]) / 3.0;
    }
};


struct Estudiante {
    string nombre;
    int edad;
    string direccion;
    string telefono;
    Persona padre, madre;  
    vector<Materia> materias;


    void ingresarDatos() {
        cout << "Ingrese el nombre del estudiante: ";
        getline(cin, nombre);


        while (true) {
            cout << "Ingrese la edad del estudiante: ";
            if (leerNumeroEntero(edad) && edad > 0) break;
        }

        cout << "Ingrese la direccion del estudiante: ";
        getline(cin, direccion);

        cout << "Ingrese el telefono del estudiante: ";
        while (true) {
            getline(cin, telefono);
            bool valido = true;
            for (char c : telefono) {
                if (!isdigit(c)) {
                    valido = false;
                    break;
                }
            }
            if (valido) break;
            cout << "Error: El telefono debe contener solo numeros.\n";
        }

        padre.ingresarNombre("padre");
        padre.ingresarTelefono();
        madre.ingresarNombre("madre");
        madre.ingresarTelefono();
    }


void ingresarMaterias() {
    int numMaterias;
    cout << "Ingrese el numero de materias (debe ser mayor que 0): ";

    while (true) {
        if (leerNumeroEntero(numMaterias) && numMaterias > 0) {
            break;
        } else {
            cout << "Error: El número de materias debe ser un entero mayor que 0.\n";
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer

    materias.resize(numMaterias);

    for (int i = 0; i < numMaterias; i++) {
        cout << "Ingrese el nombre de la materia " << i + 1 << ": ";
        getline(cin, materias[i].nombre);
        cout << "Ingrese el horario de la materia " << materias[i].nombre << ": ";
        getline(cin, materias[i].horario);
        materias[i].ingresarNotas();
    }
}

    void mostrarInformacion() const {
        cout << "\n--- Informacion del Estudiante ---\n";
        cout << "Nombre: " << nombre << "\nEdad: " << edad << "\nDireccion: " << direccion << "\nTelefono: " << telefono << "\n";
        cout << "--- Informacion del Padre ---\nNombre: " << padre.nombre << "\nTelefono: " << padre.telefono << "\n";
        cout << "--- Informacion de la Madre ---\nNombre: " << madre.nombre << "\nTelefono: " << madre.telefono << "\n";

        // Mostrar las materias y sus notas
        cout << "--- Materias ---\n";  
        for (const auto& materia : materias) {
            cout << "Materia: " << materia.nombre << "\nHorario: " << materia.horario << "\n";
            // Mostrar las 3 notas de la materia
            for (int i = 0; i < 3; i++) {
                cout << "Nota del examen " << i + 1 << ": " << materia.notas[i] << "\n";
            }
            cout << "Promedio: " << materia.calcularPromedio() << "\n";
        }
    }

   
    void actualizarNotas() {
        cout << "Ingrese el nombre de la materia a actualizar las notas: ";
        string materiaBuscada;
        getline(cin, materiaBuscada);

        for (auto& materia : materias) {
            if (materia.nombre == materiaBuscada) {
                cout << "Actualizando notas de la materia: " << materia.nombre << "\n";
                materia.ingresarNotas();
                return;
            }
        }

        cout << "Materia no encontrada.\n";
    }
};


void ingresarEstudiante(vector<Estudiante>& estudiantes) {
    Estudiante nuevoEstudiante;
    nuevoEstudiante.ingresarDatos();
    nuevoEstudiante.ingresarMaterias();
    estudiantes.push_back(nuevoEstudiante);
}


void mostrarEstudiantes(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    for (const auto& estudiante : estudiantes) {
        estudiante.mostrarInformacion();
    }
}


void buscarEstudiantePorNombre(const vector<Estudiante>& estudiantes) {
    string nombreBusqueda;
    cout << "Ingrese el nombre del estudiante a buscar: ";
    getline(cin, nombreBusqueda);

    for (const auto& estudiante : estudiantes) {
        if (estudiante.nombre == nombreBusqueda) {
            estudiante.mostrarInformacion();
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}

// Función para validar que la opción seleccionada no tenga espacios
bool leerOpcionMenu(int& opcion) {
    string input;
    getline(cin, input);  

    // Verificar si hay más de un número o espacios en la entrada
    if (input.find(' ') != string::npos) {
        cout << "Error: No se permiten espacios en la opción.\n";
        return false;
    }

    try {
        opcion = stoi(input);  
        return true;
    } catch (const invalid_argument&) {
        cout << "Error: Entrada no válida. Ingrese un número.\n";
        return false;
    } catch (const out_of_range&) {
        cout << "Error: El número está fuera de rango.\n";
        return false;
    }
}


int main() {
    vector<Estudiante> estudiantes;
    int opcion;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Agregar nuevo estudiante\n";
        cout << "2. Mostrar todos los estudiantes\n";

       
        if (estudiantes.empty()) {
            cout << "3. Buscar estudiante por nombre (No disponible, no hay estudiantes registrados)\n";
            cout << "4. Actualizar notas de una materia (No disponible, no hay estudiantes registrados)\n";
        } else {
            cout << "3. Buscar estudiante por nombre\n";
            cout << "4. Actualizar notas de una materia\n";
        }

        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";

   
        if (!leerOpcionMenu(opcion)) {
            continue;  
        }

        switch (opcion) {
            case 1:
                ingresarEstudiante(estudiantes);
                break;
            case 2:
                mostrarEstudiantes(estudiantes);
                break;
            case 3:
                if (estudiantes.empty()) {
                    cout << "No hay estudiantes registrados. No puedes buscar.\n";
                } else {
                    buscarEstudiantePorNombre(estudiantes);
                }
                break;
            case 4:
                if (estudiantes.empty()) {
                    cout << "No hay estudiantes registrados. No puedes actualizar notas.\n";
                } else {
                    string nombreEstudiante;
                    cout << "Ingrese el nombre del estudiante para actualizar notas: ";
                    getline(cin, nombreEstudiante);

                    bool encontrado = false;
                    for (auto& estudiante : estudiantes) {
                        if (estudiante.nombre == nombreEstudiante) {
                            estudiante.actualizarNotas();
                            encontrado = true;
                            break;
                        }
                    }

                    if (!encontrado) {
                        cout << "Estudiante no encontrado.\n";
                    }
                }
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}
