#include <iostream>
#include <stack>
#include <cmath>
#include <limits>
#include <cstdlib> // Para system()

using namespace std;

// Función para validar entrada de números
int leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Debe ingresar un número válido. Intente nuevamente.\n";
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

class ArbolBinario {
private:
    Nodo* raiz;
    int niveles;
    int nodosTotales;
    int nodosLlenados;
    
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
                cout << "Error: Ingrese un número entre " << min << " y " << max << "\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return opcion;
            }
        }
    }
    
    void crearArbol() {
        niveles = leerEntero("Ingrese número de niveles del árbol: ");
        while (niveles < 1) {
            cout << "Error: El árbol debe tener al menos 1 nivel.\n";
            niveles = leerEntero("Ingrese número de niveles del árbol: ");
        }
        
        nodosTotales = pow(2, niveles) - 1;
        nodosLlenados = 0;
        
        raiz = new Nodo(0);
        if (niveles > 1) {
            crearNiveles(raiz, 1);
        }
        
        cout << "Árbol creado con " << nodosTotales << " nodos totales.\n";
    }
    
    void mostrar() {
        cout << "\nESTRUCTURA DEL ÁRBOL:\n";
        mostrarArbol(raiz, 0);
        cout << endl;
    }
    
    void recorridoInteractivo() {
        if (raiz == nullptr) {
            cout << "Primero debe crear un árbol.\n";
            return;
        }
        
        stack<Nodo*> pila;
        Nodo* actual = raiz;
        
        while (true) {
            system("cls||clear");
            mostrar();
            
            cout << "\nNODO ACTUAL:\n";
            cout << "Valor: " << (actual->valor == 0 ? "VACÍO" : to_string(actual->valor)) << "\n\n";
            
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
                        cout << "¡No existe nodo izquierdo! Presione Enter para continuar...";
                        cin.get();
                    }
                    break;
                case 3:
                    if (actual->derecho != nullptr) {
                        pila.push(actual);
                        actual = actual->derecho;
                    } else {
                        cout << "¡No existe nodo derecho! Presione Enter para continuar...";
                        cin.get();
                    }
                    break;
                case 4:
                    if (!pila.empty()) {
                        actual = pila.top();
                        pila.pop();
                    } else {
                        cout << "¡Ya estás en la raíz! Presione Enter para continuar...";
                        cin.get();
                    }
                    break;
                case 5:
                    return;
            }
        }
    }
};

int main() {
    ArbolBinario arbol;
    
    while (true) {
        system("cls||clear");
        cout << "\nMENÚ PRINCIPAL\n";
        cout << "1. Crear árbol\n";
        cout << "2. Mostrar árbol\n";
        cout << "3. Recorrido interactivo\n";
        cout << "4. Salir\n";
        
        int opcion = arbol.leerOpcion("Seleccione (1-4): ", 1, 4);
        
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