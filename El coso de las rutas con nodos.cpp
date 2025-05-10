#include <iostream>
#include <stack>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <map>
#include <utility>
#include <tuple>

using namespace std;

int leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Debe ingresar un numero valido. Intente nuevamente.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr) {}
};

struct PasoRuta {
    int valor;
    string direccion;
    int nivel;
};

class ArbolBinario {
private:
    Nodo* raiz;
    int niveles;
    int nodosTotales;
    int nodosLlenados;
    map<tuple<vector<string>, int, int, string>, int> operacionesPorCamino;

    void crearNiveles(Nodo* nodo, int nivelActual) {
        if (nivelActual >= niveles) return;
        
        nodo->izquierdo = new Nodo(0);
        nodo->derecho = new Nodo(0);
        
        crearNiveles(nodo->izquierdo, nivelActual + 1);
        crearNiveles(nodo->derecho, nivelActual + 1);
    }
    
    void mostrarArbol(Nodo* nodo, int espacio) {
        if (nodo == nullptr) return;
        
        espacio += 5;
        
        mostrarArbol(nodo->derecho, espacio);
        cout << endl;
        for (int i = 5; i < espacio; i++) cout << " ";
        cout << (nodo->valor == 0 ? "[ ]" : "[" + to_string(nodo->valor) + "]") << "\n";
        mostrarArbol(nodo->izquierdo, espacio);
    }

    void liberarNodos(Nodo* nodo) {
        if (nodo) {
            liberarNodos(nodo->izquierdo);
            liberarNodos(nodo->derecho);
            delete nodo;
        }
    }

    void buscarNumeroRecursivo(Nodo* nodo, int objetivo, vector<PasoRuta>& rutaActual, 
                             vector<vector<PasoRuta>>& todasRutas, int nivel, const string& direccion = "Raiz") {
        if (nodo == nullptr) return;

        PasoRuta paso;
        paso.valor = nodo->valor;
        paso.direccion = direccion;
        paso.nivel = nivel;
        rutaActual.push_back(paso);

        if (nodo->valor == objetivo) {
            todasRutas.push_back(rutaActual);
        }

        if (nodo->izquierdo != nullptr) {
            buscarNumeroRecursivo(nodo->izquierdo, objetivo, rutaActual, todasRutas, nivel + 1, "Izquierda");
        }

        if (nodo->derecho != nullptr) {
            buscarNumeroRecursivo(nodo->derecho, objetivo, rutaActual, todasRutas, nivel + 1, "Derecha");
        }

        rutaActual.pop_back();
    }

    int seleccionarOperacion(const string& mensaje) {
        cout << "\n" << mensaje << "\n";
        cout << "1. Sumar (+)\n";
        cout << "2. Restar (-)\n";
        cout << "3. Multiplicar (*)\n";
        cout << "4. Dividir (/)\n";
        return leerOpcion("Seleccione una operacion (1-4): ", 1, 4);
    }

    double realizarOperacion(double a, double b, int operacion) {
        switch (operacion) {
            case 1: return a + b;
            case 2: return a - b;
            case 3: return a * b;
            case 4: 
                if (b == 0) {
                    cout << "Error: Division por cero. Se omitira esta operacion.\n";
                    return a;
                }
                return a / b;
            default: return a;
        }
    }

    void realizarOperacionesRuta(const vector<PasoRuta>& ruta, int ruta_num) {
        if (ruta.size() < 2) {
            cout << "Ruta demasiado corta para operar.\n";
            return;
        }

        vector<string> caminoCompleto;
        double resultado = ruta[0].valor;
        cout << "\n=== Procesando Ruta " << ruta_num << " ===\n";

        for (size_t i = 1; i < ruta.size(); ++i) {
            string direccionActual = ruta[i].direccion;
            caminoCompleto.push_back(direccionActual);
            
            int val_actual = ruta[i-1].valor;
            int val_siguiente = ruta[i].valor;
            
            auto clave = make_tuple(caminoCompleto, val_actual, val_siguiente, direccionActual);

            cout << "\nPaso " << i << " (Camino: ";
            for (const auto& dir : caminoCompleto) cout << dir[0] << " ";
            cout << ") " << val_actual << " -> " << val_siguiente << " [" << direccionActual << "]:\n";

            if (operacionesPorCamino.count(clave)) {
                int op = operacionesPorCamino[clave];
                cout << "Operacion predefinida: ";
                switch(op) {
                    case 1: cout << "Suma (+)"; break;
                    case 2: cout << "Resta (-)"; break;
                    case 3: cout << "Multiplicacion (*)"; break;
                    case 4: cout << "Division (/)"; break;
                }
                cout << endl;
                resultado = realizarOperacion(resultado, val_siguiente, op);
            } else {
                string mensaje = "Seleccione operacion para " + to_string(val_actual) + " -> " + to_string(val_siguiente) + " (" + direccionActual + "):";
                int op = seleccionarOperacion(mensaje);
                operacionesPorCamino[clave] = op;
                resultado = realizarOperacion(resultado, val_siguiente, op);
            }

            cout << "Resultado parcial: " << resultado << endl;
        }

        cout << "\n--> Resultado final de la Ruta " << ruta_num << ": " << resultado << "\n";
    }

    void procesarTodasLasRutas(const vector<vector<PasoRuta>>& todasRutas) {
        cout << "\n=== Iniciando procesamiento de todas las rutas ===\n";
        for (size_t i = 0; i < todasRutas.size(); ++i) {
            realizarOperacionesRuta(todasRutas[i], i+1);
        }
    }

public:
    ArbolBinario() : raiz(nullptr), niveles(0), nodosTotales(0), nodosLlenados(0) {}

    ~ArbolBinario() {
        liberarNodos(raiz);
    }

    int leerOpcion(const string& mensaje, int min, int max) {
        int opcion;
        while (true) {
            cout << mensaje;
            cin >> opcion;
            
            if (cin.fail() || opcion < min || opcion > max) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error: Ingrese un numero entre " << min << " y " << max << "\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return opcion;
            }
        }
    }

    void crearArbol() {
        niveles = leerEntero("Ingrese numero de niveles del arbol: ");
        while (niveles < 1) {
            cout << "Error: El arbol debe tener al menos 1 nivel.\n";
            niveles = leerEntero("Ingrese numero de niveles del arbol: ");
        }

        nodosTotales = pow(2, niveles) - 1;
        nodosLlenados = 0;

        raiz = new Nodo(0);
        if (niveles > 1) {
            crearNiveles(raiz, 1);
        }

        cout << "Arbol creado con " << nodosTotales << " nodos totales.\n";
    }

    void mostrar() {
        cout << "\nESTRUCTURA DEL ARBOL:\n";
        mostrarArbol(raiz, 0);
        cout << endl;
    }

    void recorridoInteractivo() {
        if (raiz == nullptr) {
            cout << "Primero debe crear un arbol.\n";
            return;
        }

        stack<Nodo*> pila;
        Nodo* actual = raiz;

        while (true) {
            system("cls||clear");
            mostrar();

            cout << "\nNODO ACTUAL:\n";
            cout << "Valor: " << (actual->valor == 0 ? "VACIO" : to_string(actual->valor)) << "\n\n";

            cout << "OPCIONES:\n";
            cout << "1. Llenar nodo actual\n";
            cout << "2. Ir al nodo izquierdo\n";
            cout << "3. Ir al nodo derecho\n";
            cout << "4. Volver al nodo padre\n";
            cout << "5. Terminar recorrido\n";

            int opcion = leerOpcion("Seleccione (1-5): ", 1, 5);

            switch (opcion) {
                case 1: {
                    int valor = leerEntero("Ingrese valor para el nodo (0 para vaciar): ");
                    if (actual->valor == 0 && valor != 0) nodosLlenados++;
                    else if (actual->valor != 0 && valor == 0) nodosLlenados--;
                    actual->valor = valor;
                    cout << "Valor actualizado. Presione Enter para continuar...";
                    cin.get();
                    break;
                }
                case 2:
                    if (actual->izquierdo != nullptr) {
                        pila.push(actual);
                        actual = actual->izquierdo;
                    } else {
                        cout << "!No existe nodo izquierdo! Presione Enter para continuar...";
                        cin.get();
                    }
                    break;
                case 3:
                    if (actual->derecho != nullptr) {
                        pila.push(actual);
                        actual = actual->derecho;
                    } else {
                        cout << "!No existe nodo derecho! Presione Enter para continuar...";
                        cin.get();
                    }
                    break;
                case 4:
                    if (!pila.empty()) {
                        actual = pila.top();
                        pila.pop();
                    } else {
                        cout << "!Ya estas en la raiz! Presione Enter para continuar...";
                        cin.get();
                    }
                    break;
                case 5:
                    return;
            }
        }
    }

    void buscarNumero() {
        if (raiz == nullptr) {
            cout << "Primero debe crear un arbol.\n";
            return;
        }

        operacionesPorCamino.clear();
        cout << "\n--- Operaciones anteriores limpiadas ---\n";

        int objetivo = leerEntero("Ingrese el numero que desea buscar: ");
        vector<vector<PasoRuta>> todasRutas;
        vector<PasoRuta> rutaActual;
        
        buscarNumeroRecursivo(raiz, objetivo, rutaActual, todasRutas, 1);

        if (todasRutas.empty()) {
            cout << "El numero " << objetivo << " no se encuentra en el arbol.\n";
            return;
        }

        cout << "\nEl numero " << objetivo << " se encontro " << todasRutas.size() << " vez/veces.\n";
        
        for (size_t i = 0; i < todasRutas.size(); ++i) {
            cout << "\nRuta " << i + 1 << ":\n";
            for (const auto& paso : todasRutas[i]) {
                cout << paso.direccion << " (" << paso.valor << ") ";
            }
            cout << "Nivel " << todasRutas[i].back().nivel << "\n";
        }

        procesarTodasLasRutas(todasRutas);
    }
};

int main() {
    ArbolBinario arbol;

    while (true) {
        system("cls||clear");
        cout << "\nMENU PRINCIPAL\n";
        cout << "1. Crear arbol\n";
        cout << "2. Mostrar arbol\n";
        cout << "3. Recorrido interactivo\n";
        cout << "4. Buscar numero en el arbol\n";
        cout << "5. Salir\n";

        int opcion = arbol.leerOpcion("Seleccione (1-5): ", 1, 5);

        switch (opcion) {
            case 1:
                arbol.crearArbol();
                break;
            case 2:
                arbol.mostrar();
                break;
            case 3:
                arbol.recorridoInteractivo();
                break;
            case 4:
                arbol.buscarNumero();
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                #ifdef _WIN32
                    system("pause");
                #endif
                return 0;
        }

        cout << "Presione Enter para continuar...";
        cin.get();
    }
}
