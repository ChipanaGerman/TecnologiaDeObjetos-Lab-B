#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

/**
 * ============================================================================
 * UNIVERSIDAD NACIONAL DE SAN AGUSTÍN DE AREQUIPA
 * ESCUELA PROFESIONAL DE INGENIERÍA DE SISTEMAS
 * ASIGNATURA: TECNOLOGÍA DE OBJETOS
 * LABORATORIO 05: FUNCIONES LAMBDA E INTRODUCCIÓN A QT WIDGETS
 * ============================================================================
 * 
 * EJERCICIO 1:
 * "Contar los números impares y menores de 20 de un vector de números enteros 
 *  generados de forma aleatoria (la solución puede usar el método std::count_if)"
 * 
 * DESCRIPCIÓN:
 * El programa genera un vector de enteros pseudoaleatorios dentro de un rango 
 * definido. Utiliza la función algorítmica de la biblioteca estándar STL 
 * `std::count_if` combinada con una expresión lambda moderna de C++ para evaluar 
 * el predicado unario: (número < 20) && (número % 2 != 0).
 * ============================================================================
 */

int main() {
    std::cout << "========================================================\n";
    std::cout << "  UNSA - EPIS | TECNOLOGIA DE OBJETOS - LAB 05\n";
    std::cout << "  EJERCICIO 1: Conteo con std::count_if y Funciones Lambda\n";
    std::cout << "========================================================\n\n";

    // 1. Configuración del generador de números aleatorios (C++11/14/17 moderno)
    std::random_device rd;   // Dispositivo para obtener entropía del sistema
    std::mt19937 motor(rd()); // Motor de generación Mersenne Twister 19937
    // Rango de números aleatorios: entre 1 y 50 para tener variedad < 20 y >= 20
    std::uniform_int_distribution<int> distribucion(1, 50);

    const size_t TAMANIO_VECTOR = 25;
    std::vector<int> numeros;
    numeros.reserve(TAMANIO_VECTOR);

    // Llenado del vector con valores aleatorios
    for (size_t i = 0; i < TAMANIO_VECTOR; ++i) {
        numeros.push_back(distribucion(motor));
    }

    // 2. Mostrar el vector generado utilizando std::for_each y una expresión lambda
    std::cout << ">>> Vector de " << TAMANIO_VECTOR << " enteros aleatorios generados:\n[ ";
    std::for_each(numeros.begin(), numeros.end(), [](int val) {
        std::cout << std::setw(2) << val << " ";
    });
    std::cout << "]\n\n";

    // 3. Definición de la función Lambda como predicado unario para la condición:
    //    - Menor que 20 (num < 20)
    //    - Impar (num % 2 != 0)
    auto esImparYMenorQue20 = [](int num) -> bool {
        return (num < 20) && (num % 2 != 0);
    };

    // 4. Aplicación de std::count_if utilizando la lambda como predicado
    int totalCumplen = std::count_if(numeros.begin(), numeros.end(), esImparYMenorQue20);

    // 5. Visualización detallada de los elementos que cumplieron la condición
    std::cout << ">>> Analisis detallado de elementos que cumplen la condicion:\n";
    std::cout << "    Condicion: (numero < 20) Y (numero es impar)\n";
    std::cout << "    Valores encontrados: [ ";
    
    std::for_each(numeros.begin(), numeros.end(), [&esImparYMenorQue20](int val) {
        if (esImparYMenorQue20(val)) {
            std::cout << val << " ";
        }
    });
    std::cout << "]\n\n";

    // 6. Conteo y resumen final
    std::cout << "--------------------------------------------------------\n";
    std::cout << "  RESULTADO FINAL:\n";
    std::cout << "  Total de numeros impares y menores a 20: " << totalCumplen << "\n";
    std::cout << "--------------------------------------------------------\n\n";

    return 0;
}
