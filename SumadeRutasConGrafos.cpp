#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <utility>
#include <string>
using namespace std;

class Grafo {
private:
    map<int, string> valores_nodos;
    map<pair<int, int>, int> valores_aristas;
    map<int, vector<int>> lista_adyacencia;
    set<string> valores_nodos_existentes;

    void buscarRutasDFS(int actual, int destino, vector<int>& caminoActual, 
                       set<int>& nodosVisitados, vector<vector<int>>& todasLasRutas) {
        caminoActual.push_back(actual);
        nodosVisitados.insert(actual);

        if (actual == destino) {
            todasLasRutas.push_back(caminoActual);
        } else {
            for (int vecino : lista_adyacencia[actual]) {
                if (nodosVisitados.find(vecino) == nodosVisitados.end()) {
                    buscarRutasDFS(vecino, destino, caminoActual, nodosVisitados, todasLasRutas);
                }
            }
        }

        caminoActual.pop_back();
        nodosVisitados.erase(actual);
    }

    int calcularSumaRuta(const vector<int>& ruta) {
        int suma = 0;
        for (size_t i = 0; i < ruta.size() - 1; ++i) {
            int origen = ruta[i];
            int destino = ruta[i+1];
            suma += valores_aristas[make_pair(origen, destino)];
        }
        return suma;
    }

    vector<vector<int>> encontrarTodasLasRutasInterno(int origen, int destino) {
        vector<int> caminoActual;
        set<int> nodosVisitados;
        vector<vector<int>> todasLasRutas;

        buscarRutasDFS(origen, destino, caminoActual, nodosVisitados, todasLasRutas);

        return todasLasRutas;
    }

public:
    bool tieneNodos() {
        return !valores_nodos.empty();
    }

    bool existeArista(int origen, int destino) {
        return valores_aristas.count(make_pair(origen, destino));
    }

    void agregarNodos(int cantidad) {
        cout << "Ingrese los " << cantidad << " nodos (numero y valor):" << endl;
        for (int i = 1; i <= cantidad; ) {
            int numero_nodo;
            string valor_nodo;
            
            cout << "Nodo " << i << " - Numero: ";
            while (!(cin >> numero_nodo)) {
                cout << "Entrada invalida. Ingrese un numero entero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            if (valores_nodos.count(numero_nodo)) {
                cout << "Error: El nodo " << numero_nodo << " ya existe." << endl;
                continue;
            }
            
            cout << "Nodo " << i << " - Valor (texto): ";
            cin >> valor_nodo;
            
            if (valores_nodos_existentes.count(valor_nodo)) {
                cout << "Error: El valor '" << valor_nodo << "' ya esta en uso." << endl;
                continue;
            }
            
            valores_nodos[numero_nodo] = valor_nodo;
            valores_nodos_existentes.insert(valor_nodo);
            lista_adyacencia[numero_nodo] = vector<int>();
            i++;
        }
    }

    void agregarConjuntoAristas() {
        if (!tieneNodos()) {
            cout << "Error: Primero ingrese los nodos." << endl;
            return;
        }
        
        int max_aristas = valores_nodos.size() * valores_nodos.size();
        int cantidad_aristas;
        
        cout << "\nMaximo de aristas permitidas: " << max_aristas << endl;
        cout << "Ingrese cuantas aristas desea agregar (0-" << max_aristas << "): ";
        
        while (!(cin >> cantidad_aristas) || cantidad_aristas < 0 || cantidad_aristas > max_aristas) {
            cout << "Entrada invalida. Ingrese un numero entre 0 y " << max_aristas << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        for (int i = 1; i <= cantidad_aristas; ) {
            cout << "\nArista " << i << " de " << cantidad_aristas << endl;
            cout << "Nodos disponibles: ";
            for (auto& nodo : valores_nodos) {
                cout << nodo.first << "(" << nodo.second << ") ";
            }
            
            int origen, destino, valor;
            cout << "\nIngrese origen, destino y valor (ej: 1 2 5): ";
            
            if (!(cin >> origen >> destino >> valor)) {
                cout << "Error: Entrada invalida. Debe ingresar tres numeros enteros." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            if (!valores_nodos.count(origen) || !valores_nodos.count(destino)) {
                cout << "Error: Uno o ambos nodos no existen." << endl;
                continue;
            }
            
            if (existeArista(origen, destino)) {
                cout << "Error: La arista " << origen << " -> " << destino << " ya existe." << endl;
                continue;
            }
            
            if (origen == destino) {
                cout << "Advertencia: Creando bucle en el nodo " << origen << endl;
            }
            
            lista_adyacencia[origen].push_back(destino);
            valores_aristas[make_pair(origen, destino)] = valor;
            cout << "Arista " << origen << "(" << valores_nodos[origen] << ") -> " 
                 << destino << "(" << valores_nodos[destino] << ") con valor " << valor << " agregada." << endl;
            
            if (i < cantidad_aristas) {
                char respuesta;
                cout << "Desea agregar otra arista? (s/n): ";
                cin >> respuesta;
                if (respuesta != 's' && respuesta != 'S') {
                    break;
                }
            }
            i++;
        }
    }

    void mostrarGrados() {
        if (lista_adyacencia.empty()) {
            cout << "El grafo esta vacio." << endl;
            return;
        }
        cout << "\n--- Resumen del grafo ---" << endl;
        for (auto& par : lista_adyacencia) {
            int nodo = par.first;
            cout << "Nodo " << nodo << " (" << valores_nodos[nodo] << "):" << endl;
            cout << "  - Grado de salida: " << par.second.size() << endl;
            
            int grado_entrada = 0;
            for (auto& otros : lista_adyacencia) {
                for (int dest : otros.second) {
                    if (dest == nodo) grado_entrada++;
                }
            }
            cout << "  - Grado de entrada: " << grado_entrada << endl;
        }
    }

    void mostrarAristas() {
        if (valores_aristas.empty()) {
            cout << "No hay aristas en el grafo." << endl;
            return;
        }
        cout << "\nAristas y sus valores:" << endl;
        for (auto& arista : valores_aristas) {
            cout << arista.first.first << "(" << valores_nodos[arista.first.first] << ") -> " 
                 << arista.first.second << "(" << valores_nodos[arista.first.second] << ") | Valor: " 
                 << arista.second << endl;
        }
    }

    void mostrarGrafoCompleto() {
        if (lista_adyacencia.empty()) {
            cout << "El grafo esta vacio." << endl;
            return;
        }
        
        cout << "\n--- Representacion completa del grafo ---" << endl;
        for (auto& nodo : valores_nodos) {
            int id = nodo.first;
            string valor = nodo.second;
            
            cout << "Nodo " << id << " (" << valor << "):" << endl;
            
            bool tiene_bucle = existeArista(id, id);
            if (tiene_bucle) {
                int peso_bucle = valores_aristas[make_pair(id, id)];
                cout << "  [Bucle] con peso: " << peso_bucle << endl;
            }
            
            for (int destino : lista_adyacencia[id]) {
                if (destino != id) {
                    int peso = valores_aristas[make_pair(id, destino)];
                    cout << "  -> " << destino << " (" << valores_nodos[destino] 
                         << ") [peso: " << peso << "]" << endl;
                }
            }
            
            cout << "  Aristas entrantes:" << endl;
            bool tiene_entrantes = false;
            for (auto& otro_nodo : valores_nodos) {
                int otro_id = otro_nodo.first;
                if (otro_id != id && existeArista(otro_id, id)) {
                    int peso = valores_aristas[make_pair(otro_id, id)];
                    cout << "  <- " << otro_id << " (" << valores_nodos[otro_id] 
                         << ") [peso: " << peso << "]" << endl;
                    tiene_entrantes = true;
                }
            }
            if (!tiene_entrantes) {
                cout << "  Ninguna" << endl;
            }
            
            cout << endl;
        }

        // Mostrar suma de todas las rutas posibles entre todos los nodos
        cout << "\n--- Suma de todas las rutas posibles ---" << endl;
        for (auto& origen_pair : valores_nodos) {
            for (auto& destino_pair : valores_nodos) {
                int origen = origen_pair.first;
                int destino = destino_pair.first;
                
                if (origen == destino) continue; // Opcional: saltar rutas a sí mismo
                
                vector<vector<int>> rutas = encontrarTodasLasRutasInterno(origen, destino);
                if (!rutas.empty()) {
                    cout << "Rutas desde " << origen << " (" << valores_nodos[origen] 
                         << ") hasta " << destino << " (" << valores_nodos[destino] << "):" << endl;
                    
                    for (size_t i = 0; i < rutas.size(); ++i) {
                        cout << "  Ruta " << i+1 << ": ";
                        for (size_t j = 0; j < rutas[i].size(); ++j) {
                            cout << rutas[i][j] << " (" << valores_nodos[rutas[i][j]] << ")";
                            if (j != rutas[i].size() - 1) {
                                cout << " -> ";
                            }
                        }
                        cout << " | Suma: " << calcularSumaRuta(rutas[i]) << endl;
                    }
                }
            }
        }
    }

    void encontrarTodasLasRutas(int origen, int destino) {
        if (!valores_nodos.count(origen) || !valores_nodos.count(destino)) {
            cout << "Error: Uno o ambos nodos no existen." << endl;
            return;
        }

        vector<vector<int>> todasLasRutas = encontrarTodasLasRutasInterno(origen, destino);

        cout << "\nBuscando todas las rutas desde " << origen << " (" << valores_nodos[origen] 
             << ") hasta " << destino << " (" << valores_nodos[destino] << "):" << endl;

        if (todasLasRutas.empty()) {
            cout << "No existen rutas entre los nodos especificados." << endl;
        } else {
            cout << "\nSe encontraron " << todasLasRutas.size() << " rutas posibles:" << endl;
            for (size_t i = 0; i < todasLasRutas.size(); ++i) {
                cout << "Ruta " << i+1 << ": ";
                for (size_t j = 0; j < todasLasRutas[i].size(); ++j) {
                    cout << todasLasRutas[i][j] << " (" << valores_nodos[todasLasRutas[i][j]] << ")";
                    if (j != todasLasRutas[i].size() - 1) {
                        cout << " -> ";
                    }
                }
                cout << " | Suma: " << calcularSumaRuta(todasLasRutas[i]) << endl;
            }
        }
    }
};

void mostrarMenu() {
    cout << "\n--- Menu del Grafo Dirigido ---" << endl;
    cout << "1. Ingresar todos los nodos" << endl;
    cout << "2. Agregar conjunto de aristas" << endl;
    cout << "3. Mostrar grados de entrada/salida" << endl;
    cout << "4. Mostrar aristas y valores" << endl;
    cout << "5. Mostrar representacion completa del grafo" << endl;
    cout << "6. Encontrar todas las rutas entre dos nodos" << endl;
    cout << "7. Salir" << endl;
    cout << "Seleccione una opcion (1-7): ";
}

int main() {
    Grafo g;
    int opcion;

    do {
        mostrarMenu();
        
        while (!(cin >> opcion) || opcion < 1 || opcion > 7) {
            cout << "Opcion invalida. Ingrese un numero entre 1 y 7: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (opcion) {
            case 1: {
                if (g.tieneNodos()) {
                    cout << "Error: Los nodos ya fueron ingresados." << endl;
                    break;
                }
                int cantidad;
                cout << "Ingrese la cantidad de nodos: ";
                while (!(cin >> cantidad) || cantidad <= 0) {
                    cout << "Entrada invalida. Ingrese un numero positivo: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                g.agregarNodos(cantidad);
                break;
            }
            case 2:
                g.agregarConjuntoAristas();
                break;
            case 3:
                g.mostrarGrados();
                break;
            case 4:
                g.mostrarAristas();
                break;
            case 5:
                g.mostrarGrafoCompleto();
                break;
            case 6: {
                if (!g.tieneNodos()) {
                    cout << "Error: Primero ingrese los nodos." << endl;
                    break;
                }
                int origen, destino;
                cout << "Ingrese el nodo origen: ";
                cin >> origen;
                cout << "Ingrese el nodo destino: ";
                cin >> destino;
                g.encontrarTodasLasRutas(origen, destino);
                break;
            }
            case 7:
                cout << "Saliendo del programa." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}
