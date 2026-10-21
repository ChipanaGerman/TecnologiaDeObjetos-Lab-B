#include <iostream>
using namespace std;

// Plantilla de clase con:
// 1. Un parámetro de tipo por defecto: T = char
// 2. Un parámetro no de tipo (valor entero) por defecto: int N = 8
template <class T = char, int N = 8>
class Comun1 {
    T bloque[N]; // Arreglo estático de tamaño N del tipo T
public:
    void set(int num, T tval);
    T get(int num);
};

// Definición externa del método set
template <class T, int N>
void Comun1<T, N>::set(int num, T tval) {
    bloque[num] = tval;
}

// Definición externa del método get
template <class T, int N>
T Comun1<T, N>::get(int num) {
    return bloque[num];
}

int main() {
    // 1. Instancia especificando tipo 'int' y tamaño '5'
    Comun1<int, 5> objInt;
    
    // 2. Instancia especificando tipo 'double' y tamaño '5'
    Comun1<double, 5> objFloat;
    
    // 3. Instancia usando los parámetros POR DEFECTO (char, tamaño 8)
    Comun1<> obj;

    // Asignación de valores
    objInt.set(0, 10);
    objFloat.set(2, 3.1);

    // Impresión de valores
    std::cout << objInt.get(0) << std::endl;
    std::cout << objFloat.get(2) << std::endl;
    std::cout << obj.get(4) << std::endl; // Ojo: posición no inicializada

    return 0;
}