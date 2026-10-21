#include <iostream>
#include <string>

// 1. CLASE NODO (GENÉRICA)
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;

    // Constructor del nodo
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

// 2. CLASE LISTA ENLAZADA SIMPLE (GENÉRICA)
template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;

public:
    // Constructor: inicializa la lista vacía
    ListaSimple() : cabeza(nullptr) {}

    // Destructor: libera la memoria dinámica asignada
    ~ListaSimple() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // Método para insertar un elemento al final de la lista
    void insertarFinal(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }

    // Método para recorrer e imprimir la lista
    void mostrar() const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            std::cout << "[" << actual->dato << "] -> ";
            actual = actual->siguiente;
        }
        std::cout << "nullptr" << std::endl;
    }
};

// 3. FUNCIÓN PRINCIPAL (DEMOSTRACIÓN)
int main() {
    std::cout << "=== SECUENCIA DE EDADES (ListaSimple<int>) ===" << std::endl;
    ListaSimple<int> listaEdades;
    listaEdades.insertarFinal(19);
    listaEdades.insertarFinal(21);
    listaEdades.insertarFinal(25);
    listaEdades.insertarFinal(18);
    listaEdades.mostrar();

    std::cout << "\n=== SECUENCIA DE PALABRAS (ListaSimple<std::string>) ===" << std::endl;
    ListaSimple<std::string> listaPalabras;
    listaPalabras.insertarFinal("Universidad");
    listaPalabras.insertarFinal("Nacional");
    listaPalabras.insertarFinal("San");
    listaPalabras.insertarFinal("Agustin");
    listaPalabras.mostrar();

    return 0;
}