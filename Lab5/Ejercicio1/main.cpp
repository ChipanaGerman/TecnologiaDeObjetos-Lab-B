#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 50);

    const int TAM = 20;
    vector<int> numeros(TAM);

    for (int i = 0; i < TAM; ++i) {
        numeros[i] = dis(gen);
    }

    cout << "Vector generado:" << endl;
    for_each(numeros.begin(), numeros.end(), [](int n) {
        cout << n << " ";
    });
    cout << "\n\n";

    // Condicion: impar y menor que 20
    auto esImparYMenorQue20 = [](int n) {
        return (n < 20) && (n % 2 != 0);
    };

    int total = count_if(numeros.begin(), numeros.end(), esImparYMenorQue20);

    cout << "Numeros impares y menores a 20:" << endl;
    for_each(numeros.begin(), numeros.end(), [&esImparYMenorQue20](int n) {
        if (esImparYMenorQue20(n)) {
            cout << n << " ";
        }
    });
    cout << "\n\n";

    cout << "Total de elementos que cumplen la condicion: " << total << endl;

    return 0;
}
